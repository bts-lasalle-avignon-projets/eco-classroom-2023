#include "mqtt.h"
#include "Arduino.h"

const int mqttPort = 1883;
// const char* mqttUser = "yourMQTTuser";
// const char* mqttPassword = "yourMQTTpassword";
String topicPrincipal = "salles"; //!< nom racine du topic MQTT
String topic;

PubSubClient client(espClient);

bool connecterMQTT()
{
    int nbTentatives = 0;
    client.setServer(mqttServer, mqttPort);
    client.setCallback(recevoirMessageMQTT);

    while(!client.connected())
    {
#ifdef DEBUG_MQTT
        Serial.println("Connexion au broker ...");
#endif

        if(client.connect(""))
        {
#ifdef DEBUG_MQTT
            Serial.println("Connecté au broker !");
#endif
            return true;
        }
        else
        {
#ifdef DEBUG_MQTT
            Serial.print("Erreur : ");
            Serial.print(client.state());
            Serial.println("");
#endif
            if(nbTentatives < NB_TENTATIVES_MQTT_MAX)
            {
                delay(ATTENTE_CONNEXION_MQTT);
                nbTentatives++;
            }
            else
                return false;
        }
    }
    return false;
}

bool estConnecteMQTT()
{
    return client.connected();
}

void recevoirMessageMQTT(char* topic, byte* payload, unsigned int length)
{
#ifdef DEBUG_MQTT
    Serial.print("Message [");
    Serial.print(topic);
    Serial.print("] ");
#endif
    for(int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void envoyerMessageMQTT(String messageLoRa)
{
    String sousTopic;
    int    position = messageLoRa.lastIndexOf("/");
    if(position != -1)
    {
        sousTopic = messageLoRa.substring(0, position);
        messageLoRa.remove(0, position + 1);
    }
    else
    {
#ifdef DEBUG_MQTT
        Serial.println("Erreur topic !");
        Serial.println("");
#endif
        return;
    }

    String messageMQTT = messageLoRa;
    if(sousTopic.length() > 0)
    {
        topic = topicPrincipal + String("/") + sousTopic;
#ifdef DEBUG_MQTT
        Serial.print("Topic : ");
        Serial.println(topic);
        Serial.print("Message MQTT : ");
        Serial.println(messageMQTT);
        Serial.println("");
#endif
        if(estConnecteMQTT())
        {
            publier(topic.c_str(), messageMQTT.c_str());
        }
    }
    else
    {
#ifdef DEBUG_MQTT
        Serial.println("Topic manquant !");
        Serial.println("");
#endif
        return;
    }
}

bool publier(const char* topic, const char* message)
{
    return client.publish(topic, message);
}

void souscrire(const char* topic)
{
    client.subscribe(topic);
}
