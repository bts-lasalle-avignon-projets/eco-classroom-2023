#include "lora.h"
#include "mqtt.h"

bool initialiserLora()
{
    return loraE32.begin();
}

void configurer(byte               ADDL,
                byte               ADDH,
                byte               channel,
                FIDEX_TRANSMISSION typeTransmission,
                bool               maintien)
{
    ResponseStructContainer c             = loraE32.getConfiguration();
    Configuration           configuration = *(Configuration*)c.data;

    configuration.ADDL                     = ADDL;
    configuration.ADDH                     = ADDH;
    configuration.CHAN                     = channel;
    configuration.SPED.airDataRate         = 2; // bit 0-2 : 2.4kbps
    configuration.SPED.uartBaudRate        = 3; // bit 3-5 : 9600bps
    configuration.SPED.uartParity          = 0; // bit 6-7 : 8N1
    configuration.OPTION.fixedTransmission = typeTransmission;
    // conserver les paramètres au redémarrage ?
    if(maintien)
        loraE32.setConfiguration(configuration, WRITE_CFG_PWR_DWN_SAVE);
    else
        loraE32.setConfiguration(configuration, WRITE_CFG_PWR_DWN_LOSE);
    c.close();
}

void selectionnerMode(MODE_TYPE mode)
{
    // MODE_0_NORMAL, MODE_1_WAKE_UP, MODE_2_POWER_SAVING, MODE_3_SLEEP et
    // MODE_3_PROGRAM
    loraE32.setMode(mode);
}

int traiterMessage()
{
    String message;
    int    nbMessages = 0;
    if(loraE32.available())
    {
        message.clear();
        ResponseContainer rs = loraE32.receiveMessage();
        message              = rs.data;
        nbMessages           = count(message, "B");
#ifdef DEBUG_LORA
        // Serial.print("Etat : ");
        // Serial.println(rs.status.getResponseDescription());
        Serial.print("Reception : ");
        Serial.println(message);
        Serial.print("Nb messages : ");
        Serial.println(nbMessages);
#endif
        String messageMQTT;
        for(int i = 0; i < nbMessages; ++i)
        {
            messageMQTT = String("B") + getMessage(message, 'B', i + 1);
            envoyerMessageMQTT(messageMQTT);
        }
    }
    return nbMessages;
}

bool envoyerMessage(String message)
{
    ResponseStatus rs = loraE32.sendMessage(message);
#ifdef DEBUG_LORA
    Serial.print("Etat : ");
    Serial.println(rs.getResponseDescription());
#endif
    if(rs.code == E32_SUCCESS)
        return true;
    else
        return false;
}

bool envoyerMessage(byte ADDH, byte ADDL, byte CHANNEL, String message)
{
    ResponseStatus rs = loraE32.sendFixedMessage(ADDH, ADDL, CHANNEL, message);
    // loraE32.sendBroadcastFixedMessage(CHANNEL, message);
    /*
    #ifdef DEBUG_LORA
        Serial.print("Etat : ");
        Serial.println(rs.getResponseDescription());
    #endif
    */
    if(rs.code == E32_SUCCESS)
        return true;
    else
        return false;
}

void afficherParametres()
{
    ResponseStructContainer c             = loraE32.getConfiguration();
    Configuration           configuration = *(Configuration*)c.data;
    afficherParametres(configuration);
    c.close();
}

void afficherParametres(struct Configuration configuration)
{
    Serial.println("----------------------------------------");
    Serial.print(F("HEAD : "));
    Serial.println(configuration.HEAD, HEX);
    Serial.println(F(" "));
    Serial.print(F("ADDH    : "));
    Serial.println(configuration.ADDH, BIN);
    Serial.print(F("ADDL    : "));
    Serial.println(configuration.ADDL, BIN);
    Serial.print(F("CHANNEL : "));
    Serial.print(configuration.CHAN, DEC);
    Serial.print(" -> ");
    Serial.println(configuration.getChannelDescription());
    Serial.println(F(" "));
    Serial.print(F("FormatUART         : "));
    Serial.print(configuration.SPED.uartParity, BIN);
    Serial.print(" -> ");
    Serial.println(configuration.SPED.getUARTParityDescription());
    Serial.print(F("SpeedUART          : "));
    Serial.print(configuration.SPED.uartBaudRate, BIN);
    Serial.print(" -> ");
    Serial.println(configuration.SPED.getUARTBaudRate());
    Serial.print(F("SpeedAirDataRate   : "));
    Serial.print(configuration.SPED.airDataRate, BIN);
    Serial.print(" -> ");
    Serial.println(configuration.SPED.getAirDataRate());

    Serial.print(F("OptionTransmission : "));
    Serial.print(configuration.OPTION.fixedTransmission, BIN);
    Serial.print(" -> ");
    Serial.println(configuration.OPTION.getFixedTransmissionDescription());
    Serial.print(F("OptionPullup       : "));
    Serial.print(configuration.OPTION.ioDriveMode, BIN);
    Serial.print(" -> ");
    Serial.println(configuration.OPTION.getIODroveModeDescription());
    Serial.print(F("OptionWakeup       : "));
    Serial.print(configuration.OPTION.wirelessWakeupTime, BIN);
    Serial.print(" -> ");
    Serial.println(configuration.OPTION.getWirelessWakeUPTimeDescription());
    Serial.print(F("OptionFEC          : "));
    Serial.print(configuration.OPTION.fec, BIN);
    Serial.print(" -> ");
    Serial.println(configuration.OPTION.getFECDescription());
    Serial.print(F("OptionPower        : "));
    Serial.print(configuration.OPTION.transmissionPower, BIN);
    Serial.print(" -> ");
    Serial.println(configuration.OPTION.getTransmissionPowerDescription());
    Serial.println("----------------------------------------");
}

String extraireMessage(String& message, char delimiteur, unsigned int numero)
{
    String       champ;
    unsigned int compteurCaractere  = 0;
    unsigned int compteurDelimiteur = 0;

    for(unsigned int i = 0; i < message.length(); i++)
    {
        if(message[i] == delimiteur)
        {
            compteurDelimiteur++;
        }
        else if(compteurDelimiteur == numero)
        {
            champ += message[i];
            compteurCaractere++;
        }
    }

    return champ;
}

String getMessage(String message, char separateur, int index)
{
    int found      = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex   = message.length() - 1;

    for(int i = 0; i <= maxIndex && found <= index; i++)
    {
        if(message.charAt(i) == separateur || i == maxIndex)
        {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }

    return found > index ? message.substring(strIndex[0], strIndex[1]) : "";
}

int count(const String& str, const String& sub)
{
    if(sub.length() == 0)
        return 0;
    int count = 0;
    for(int offset = str.indexOf(sub); offset != -1;
        offset     = str.indexOf(sub, offset + sub.length()))
    {
        ++count;
    }
    return count;
}
