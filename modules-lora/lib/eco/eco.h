#ifndef ECO_H
#define ECO_H

#include "Arduino.h"

#define DEBUG_ECO

// #define SIMULATION_ALEATOIRE

/**
 * @def PERIODE
 * @brief La période d'envoi en ms des messages LoRa pour une salle (1s = 1
 * minute)
 */
#define PERIODE 4000 // en ms

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
    MesureInconnue = -1,
    Temperature,
    Humidite,
    CO2,
    NB_TYPES_MESURE
};

/**
 * @enum TypeDetection
 * @brief Les differents types de détection
 */
enum TypeDetection
{
    DetectionInconnu = -1,
    Fenetres,
    Lumieres,
    Occupation,
    NB_TYPES_DETECTION
};

/**
 * @enum Salle
 * @brief Les differents salles
 */
enum Salle
{
    Inconnue = -1,
    B_11,
    B_20,
    B_21,
    B_22,
    NB_SALLES_ECO
};

#define NB_MESURES 30

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

String simulerMesure(char       prefixeSalle,
                     String     numeroSalle,
                     TypeMesure typeMesure);
String simulerDetection(char          prefixeSalle,
                        String        numeroSalle,
                        TypeDetection typeDetection);
String getMesure(String nomSalle, TypeMesure typeMesure);
String getDetection(String nomSalle, TypeDetection typeDetection);
String getTemperature(Salle salle);
String getHumidite(Salle salle);
String getLuminosite(Salle salle);
String getCO2(Salle salle);
String getEtatFenetres(Salle salle);
String getEtatLumieres(Salle salle);
String getEtatOccupation(Salle salle);
String getIndiceNiveauConfort();
String getIndiceQualiteAir();
Salle  getSalle(String nomSalle);

#endif
