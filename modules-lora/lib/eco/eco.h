#ifndef ECO_H
#define ECO_H

#include "Arduino.h"

#define DEBUG_ECO

/**
 * @def PERIODE
 * @brief La période d'envoi en ms des messages LoRa pour une salle
 */
#define PERIODE 5000 // en ms

/**
 * @def NB_SALLES
 * @brief Le nombre simulé de salles
 */
#define NB_SALLES 4

/**
 * @enum TypeMesure
 * @brief Les differents types de mesure
 */
enum TypeMesure
{
    Inconnu = -1,
    Temperature,
    Humidite,
    Confort,
    Luminosite,
    CO2,
    Air,
    Fenetres,
    Lumieres,
    Occupation,
    NB_TYPES_MESURE
};

/**
 * @struct Message
 * @brief Un message contenant une donnée d'une salle
 */
struct Message
{
    char salle[4];   //!< nom de la salle XYY
    char mesure[12]; //!< type de mesure : "temperature", "humidite", "confort",
                     //   "luminosite", "co2", "air", "fenetres", "lumieres",
                     //   "occupation"
    String valeur;   //!<  valeur de la mesure
};

extern uint16_t luminosite;
extern uint8_t  humidite;
extern float    temperature;
extern uint16_t co2;
extern int      indiceNiveauConfort;
extern int      indiceQualiteAir;
extern bool     etatLumieres;
extern bool     etatFenetres;
extern bool     etatOccupation;

String simulerMesure(char prefixeSalle = 'C');
String getMesure(TypeMesure typeMesure);
String getTemperature();
String getHumidite();
String getLuminosite();
String getCO2();
String getEtatFenetres();
String getEtatLumieres();
String getEtatOccupation();
String getIndiceNiveauConfort();
String getIndiceQualiteAir();
bool   runEvery(unsigned long interval);

#endif
