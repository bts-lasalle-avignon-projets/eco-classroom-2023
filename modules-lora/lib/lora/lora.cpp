#include "lora.h"

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

bool recevoirMessage(String& message)
{
    if(loraE32.available())
    {
        message.clear();
        ResponseContainer rs = loraE32.receiveMessage();
        message              = rs.data;
#ifdef DEBUG_LORA
        Serial.print("Etat : ");
        Serial.println(rs.status.getResponseDescription());
        Serial.print("Message : ");
        Serial.println(message);
#endif
        return true;
    }
    return false;
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
#ifdef DEBUG_LORA
    Serial.print("Etat : ");
    Serial.println(rs.getResponseDescription());
#endif
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
