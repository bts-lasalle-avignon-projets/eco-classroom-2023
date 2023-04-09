#include "mywifi.h"
#include "Arduino.h"

WiFiClient espClient;

bool initialiserWiFi(const char* ssid, const char* password)
{
    int nbTentatives = 0;

    WiFi.begin(ssid, password);

#ifdef DEBUG_WIFI
    Serial.println("Connexion WiFi ...");
#endif
    while(WiFi.status() != WL_CONNECTED)
    {
        if(nbTentatives < NB_TENTATIVES_WIFI_MAX)
        {
            delay(ATTENTE_CONNEXION_WIFI);
            nbTentatives++;
        }
        else
            return false;
    }

#ifdef DEBUG_WIFI
    Serial.println("Connecté au réseau WiFi !");
#endif
    return true;
}

bool estESPConnecte()
{
    return espClient.connected();
}

bool estWiFiConnecte()
{
    return (WiFi.status() == WL_CONNECTED);
}
