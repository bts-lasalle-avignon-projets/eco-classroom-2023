#ifndef MYWIFI_H
#define MYWIFI_H

#include "WiFi.h"

#define DEBUG_WIFI
#define NB_TENTATIVES_WIFI_MAX 3
#define ATTENTE_CONNEXION_WIFI 1000

extern WiFiClient espClient;

bool initialiserWiFi(const char* ssid, const char* password);
bool estESPConnecte();
bool estWiFiConnecte();

#endif
