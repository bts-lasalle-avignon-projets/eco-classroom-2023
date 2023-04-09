/**
 *
 * @file src/main.cpp
 * @brief Simulateur eco-classroom 2023
 * @author Thierry Vaira
 * @version 0.1
 */

/**
 * @def FREQUENCY_868
 * @brief Fréquence par défaut des modules E32-900T30D
 */
#define FREQUENCY_868

#include "Arduino.h"
// #include "Preferences.h"
#include "LoRa_E32.h"
#include "lora.h"

/**
 * @def DEBUG
 * @brief Débugage sur la liaison série
 */
#define DEBUG

// Définir le type de module : NODE ou GATEWAY
// NODE : changer le préfixe de salle et l'adresse du module
// GATEWAY : configurer le SSID et le broker MQTT, et l'adresse du module
// #define NODE
#define GATEWAY

/**
 * @def LORA_MODULE
 * @brief NODE ou GATEWAY
 */
#ifdef NODE
#define LORA_MODULE 1
#elif defined(GATEWAY)
#define LORA_MODULE 2
#else
#error "Il faut choisir un mode de fonctionnement pour le module !"
#endif

#if LORA_MODULE == 1
#include "eco.h"
#elif LORA_MODULE == 2
#include "mywifi.h"
#include "mqtt.h"
#else
#error "Il faut choisir un mode de fonctionnement pour le module !"
#endif

// Configuration
#if LORA_MODULE == 1
char prefixeSalle       = 'B';
byte adresseModuleH     = 0x00; //!< adresse haute du module
byte adresseModuleL     = 0x02; //!< adresse basse du module
byte canalTransmission  = 0x02; //!< canal de la passerelle
byte adressePasserelleH = 0x00; //!< adresse haute de la passerelle
byte adressePasserelleL = 0xFF; //!< adresse basse de la passerelle

#elif LORA_MODULE == 2
const char* ssid              = "xxxx";
const char* password          = "yyyy";
const char* mqttServer        = "192.168.52.7";
byte        adresseModuleH    = 0x00; //!< adresse haute du module
byte        adresseModuleL    = 0xFF; //!< adresse basse du module
byte        canalTransmission = 0x02; //!< canal de la passerelle
#endif

/**
 * @def LORA_ON
 * @brief Active la transmission LoRa
 */
#define LORA_ON

/* E32 ----- esp32
 *
 * M0  ----- D21
 * M1  ----- D19
 * TX  ----- RX2 (PullUP 4,7KΩ)
 * RX  ----- TX2 (PullUP 4,7KΩ)
 * AUX ----- D18 (PullUP 4,7KΩ)
 * VCC ----- 5V (ou 3.3v)
 * GND ----- GND
 */

/**
 * @def M0_PIN
 * @brief Broche ESP32 controlant M0
 */
#define M0_PIN 21
/**
 * @def M1_PIN
 * @brief Broche ESP32 controlant M1
 */
#define M1_PIN 19
/**
 * @def AUX_PIN
 * @brief Broche ESP32 controlant AUX
 */
#define AUX_PIN 18

// Preferences preferences; //!< pour le stockage interne
LoRa_E32 loraE32(&Serial2, AUX_PIN, M0_PIN, M1_PIN); //!< l'interface LoRa
String   message;                                    //!< une message LoRa

/**
 * @brief Initialise les ressources
 *
 * @fn setup()
 */
void setup()
{
    Serial.begin(115200);
    while(!Serial)
        ;

#ifdef DEBUG
    Serial.println("Simulateur eco-classroom 2023");
#endif

    delay(500);

#ifdef LORA_ON
    initialiserLora();

    configurer(adresseModuleL,
               adresseModuleH,
               canalTransmission,
               FT_FIXED_TRANSMISSION);

    afficherParametres();
    // selectionnerMode(MODE_0_NORMAL);
    // selectionnerMode(MODE_2_POWER_SAVING);
#endif

#if LORA_MODULE == 1
#ifdef DEBUG
    Serial.println("LoRa Node");
#endif
#elif LORA_MODULE == 2
#ifdef DEBUG
    Serial.println("LoRa Gateway");
    Serial.print("   ssid : ");
    Serial.print(ssid);
    Serial.println("");
    Serial.print("   serveur mqqt : ");
    Serial.print(mqttServer);
    Serial.println("");
#endif
    if(initialiserWiFi(ssid, password))
    {
#ifdef DEBUG
        Serial.println("Wifi ok");
#endif
        if(connecterMQTT())
        {
#ifdef DEBUG
            Serial.println("Broker MQTT ok");
#endif
        }
        else
        {
#ifdef DEBUG
            Serial.println("Erreur Broker MQTT !");
#endif
        }
    }
    else
    {
#ifdef DEBUG
        Serial.println("Erreur Wifi !");
#endif
    }
#endif

    // initialise le générateur pseudo-aléatoire
    randomSeed(analogRead(34));
}

/**
 * @brief Boucle principale
 *
 * @fn loop()
 */
void loop()
{
    static int compteur = 0;

#if LORA_MODULE == 1
    message = simulerMesure(prefixeSalle);
    if(!message.isEmpty())
    {
#ifdef LORA_ON
#ifdef DEBUG
        Serial.print("Message LoRa envoyé : ");
        Serial.println(message);
#endif
        // envoyerMessage(message);
        envoyerMessage(adressePasserelleH,
                       adressePasserelleL,
                       canalTransmission,
                       message);
#endif

        ++compteur;
#ifdef DEBUG
        Serial.print("Compteur messages : ");
        Serial.println(compteur);
        Serial.println("");
#endif
    }
#elif LORA_MODULE == 2

    if(recevoirMessage(message))
    {
        envoyerMessageMQTT(message);
    }
#endif
}
