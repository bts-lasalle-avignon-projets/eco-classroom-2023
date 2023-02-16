#ifndef MQTT_H
#define MQTT_H

#include "WiFi.h"
#include "PubSubClient.h"

#define DEBUG_MQTT
#define NB_TENTATIVES_MQTT_MAX 3
#define ATTENTE_CONNEXION_MQTT 2000

extern const char* mqttServer;
extern const int   mqttPort;
// extern const char* mqttUser;
// extern const char* mqttPassword;
// extern const char* topic;

extern WiFiClient   espClient;
extern PubSubClient client;

bool connecterMQTT();
bool estConnecteMQTT();
void recevoirMessageMQTT(char* topic, byte* payload, unsigned int length);
void envoyerMessageMQTT(String messageLoRa);
bool publier(const char* topic, const char* message);
void souscrire(const char* topic);

#endif
