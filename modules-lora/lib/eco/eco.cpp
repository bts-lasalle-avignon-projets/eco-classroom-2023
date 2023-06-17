#include "eco.h"

String typesMesure[NB_TYPES_MESURE]       = { String("temperature"),
                                              String("humidite"),
                                              String(
                                          "co2") }; //!< les types de mesure
String typesDetection[NB_TYPES_DETECTION] = {
    String("fenetre"),
    String("lumiere"),
    String("presence")
}; //!< les types de détection
String salles[NB_SALLES] = { String("11"),
                             String("20"),
                             String("21"),
                             String("22") }; //!< les noms des salles

float mesuresTemperature[NB_SALLES][NB_MESURES] = {
    { 24,   24,   24.2, 24.1, 24.2, 24.4, 24.5, 24.4, 24.6, 24.7,
      24.5, 24.5, 24.6, 24.7, 24.7, 24.8, 24.9, 25.1, 25.2, 25.4,
      24.1, 24,   24.2, 24.3, 24.3, 24.5, 24.6, 24.8, 24.8, 24.9 },
    { 24.1, 24,   24.2, 24.3, 24.3, 24.5, 24.6, 24.8, 24.8, 24.9,
      24.3, 24.4, 24.4, 24.5, 24.5, 24.7, 24.8, 24.9, 25,   25.2,
      24.3, 24.4, 24.4, 24.5, 24.5, 24.7, 24.8, 24.9, 25,   25.2 },
    { 24.3, 24.4, 24.4, 24.5, 24.5, 24.7, 24.8, 24.9, 25,   25.2,
      24,   24,   24.2, 24.1, 24.2, 24.4, 24.5, 24.4, 24.6, 24.7,
      24,   24,   24.2, 24.1, 24.2, 24.4, 24.5, 24.4, 24.6, 24.7 },
    { 24.5, 24.5, 24.6, 24.7, 24.7, 24.8, 24.9, 25.1, 25.2, 25.4,
      24.5, 24.5, 24.6, 24.7, 24.7, 24.8, 24.9, 25.1, 25.2, 25.4,
      24.5, 24.5, 24.6, 24.7, 24.7, 24.8, 24.9, 25.1, 25.2, 25.4 }
};

uint8_t mesuresHumidite[NB_SALLES][NB_MESURES] = {
    { 54, 54, 55, 54, 55, 56, 57, 58, 59, 60, 59, 58, 57, 56, 55,
      54, 55, 54, 54, 44, 44, 45, 44, 45, 46, 47, 48, 49, 50, 51 },
    { 44, 44, 45, 44, 45, 46, 47, 48, 49, 48, 47, 46, 45, 44, 43,
      42, 41, 40, 39, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48 },
    { 45, 44, 45, 46, 47, 48, 49, 51, 51, 52, 54, 54, 55, 54, 55,
      56, 57, 58, 59, 60, 60, 61, 62, 63, 64, 65, 66, 67, 68, 70 },
    { 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 65, 66, 67, 68, 65,
      66, 67, 68, 65, 66, 67, 68, 65, 66, 67, 68, 65, 66, 67, 66 }
};

uint16_t
  mesuresCO2[NB_SALLES][NB_MESURES] = {
      { 312,  455,  380,  658,  889,  905,  1100, 1540, 1422, 1669,
        1702, 1698, 1805, 1850, 1630, 1496, 1355, 1255, 1104, 1040,
        922,  669,  702,  698,  512,  555,  480,  404,  489,  458 },
      { 312,  455, 380,  658,  889,  905, 999, 997, 822, 969,
        1002, 698, 1005, 1050, 1130, 896, 855, 755, 804, 840,
        622,  669, 702,  698,  512,  555, 480, 458, 489, 999 },
      { 312, 455, 380, 658, 889, 905, 900, 940, 922, 969,
        702, 698, 805, 850, 630, 496, 355, 255, 504, 540,
        922, 669, 702, 698, 512, 555, 480, 458, 489, 540 },
      { 1312, 1455, 1380, 1658, 1589, 1905, 1701, 1740, 1722, 1769,
        1702, 1798, 1805, 1850, 1730, 1896, 1355, 1755, 1704, 1940,
        1922, 1869, 1702, 1698, 1712, 1755, 1780, 1758, 1789, 1705 }
  };

int etatsFenetre[NB_SALLES][NB_MESURES] = {
    { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
      0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
      0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 }
};

int etatsPresence[NB_SALLES][NB_MESURES] = {
    { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
      0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
      0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 }
};

int etatsLumiere[NB_SALLES][NB_MESURES] = {
    { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
      1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
    { 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 }
};

uint16_t    luminosite;  //!< valeur de l'éclairement lumineux en lux
uint8_t     humidite;    //!< valeur de l'humidité en %
float       temperature; //!< valeur de la température en degré Celcius
uint16_t    co2;         //!< valeur de co2 en ppm
int         indiceNiveauConfort = -1;    //!< l'indice de confort
int         indiceQualiteAir    = 0;     //!< l'indice de qualité d'air
bool        etatLumieres        = false; //!< état des lumières
bool        etatFenetres        = false; //!< état des fenêtres
bool        etatOccupation      = false; //!< état d'occupation
int         numeroMesure        = 0;
extern char prefixeSalle;

/**
 * @brief Simule une mesure pour une salle
 * @return String le message à envoyer en LoRa
 */
String simulerMesure(char       prefixeSalle,
                     String     numeroSalle,
                     TypeMesure typeMesure)
{
    String salle     = String(prefixeSalle) + numeroSalle;
    String nomMesure = typesMesure[typeMesure];
    String message   = salle + String("/sonde/") + nomMesure + String("/") +
                     getMesure(salle, typeMesure);

    return message;
}

/**
 * @brief Simule une détection pour une salle
 * @return String le message à envoyer en LoRa
 */
String simulerDetection(char          prefixeSalle,
                        String        numeroSalle,
                        TypeDetection typeDetection)
{
    String salle        = String(prefixeSalle) + numeroSalle;
    String nomDetection = typesDetection[typeDetection];
    String message      = salle + String("/detection/") + nomDetection +
                     String("/") + getDetection(salle, typeDetection);

    return message;
}

/**
 * @brief Retourne une mesure simulée
 * @return String
 */
String getMesure(String nomSalle, TypeMesure typeMesure)
{
    Salle salle = getSalle(nomSalle);
    switch(typeMesure)
    {
        case Temperature:
            return getTemperature(salle);
        case Humidite:
            return getHumidite(salle);
            break;
        case CO2:
            return getCO2(salle);
            break;
        default:
#ifdef DEBUG_ECO
            Serial.println("Erreur type de mesure inconnu !");
#endif
            return String();
            break;
    }
}

/**
 * @brief Retourne une détection simulée
 * @return String
 */
String getDetection(String nomSalle, TypeDetection typeDetection)
{
    Salle salle = getSalle(nomSalle);
    switch(typeDetection)
    {
        case Fenetres:
            return getEtatFenetres(salle);
            break;
        case Lumieres:
            return getEtatLumieres(salle);
            break;
        case Occupation:
            return getEtatOccupation(salle);
            break;
        default:
#ifdef DEBUG_ECO
            Serial.println("Erreur type de détection inconnu !");
#endif
            return String();
            break;
    }
}

/**
 * @brief Retourne la température simulée en °C
 * @return String
 */
String getTemperature(Salle salle)
{
#ifdef SIMULATION_ALEATOIRE
    float delta = (float(random(0, 200)) / 10.);
    temperature = 15.0 + delta;
#else
    temperature    = mesuresTemperature[salle][numeroMesure];
#endif
    return String(temperature, 1);
}

/**
 * @brief Retourne l'humidité simulée en %
 * @return String
 */
String getHumidite(Salle salle)
{
#ifdef SIMULATION_ALEATOIRE
    humidite = random(30, 80);
#else
    humidite       = mesuresHumidite[salle][numeroMesure];
#endif
    return String(humidite);
}

/**
 * @brief Retourne la luminosité simulée en lux
 * @return String
 */
String getLuminosite(Salle salle)
{
#ifdef SIMULATION_ALEATOIRE
    luminosite = random(10, 1000);
#endif
    return String(luminosite);
}

/**
 * @brief Retourne le niveau de CO2 simulé en ppm
 * @return String
 */
String getCO2(Salle salle)
{
#ifdef SIMULATION_ALEATOIRE
    // Bon : jusqu’à 1000 ppm
    // Mauvais : niveaux supérieurs à 2000 ppm
    // Plage 450 - 2450
    int taus = random(0, 5); // 1 fois sur 5
    if(taus == 1)
        co2 = 400 + random(0, 2000);
    else
        co2 = 400 + random(0, 800);
#else
    co2            = mesuresCO2[salle][numeroMesure];
#endif
    return String(co2);
}

/**
 * @brief Retourne l'état des fenêtres simulé
 * @return String
 */
String getEtatFenetres(Salle salle)
{
#ifdef SIMULATION_ALEATOIRE
    int taus = random(0, 5); // 1 fois sur 5
    if(taus == 1)
        etatFenetres = true;
    else
        etatFenetres = false;
#else
    etatFenetres   = etatsFenetre[salle][numeroMesure];
#endif
    return String(etatFenetres);
}

/**
 * @brief Retourne l'état des lumières simulé
 * @return String
 */
String getEtatLumieres(Salle salle)
{
#ifdef SIMULATION_ALEATOIRE
    int taus = random(0, 5); // 1 fois sur 5
    if(taus == 1)
    {
        etatLumieres   = true;
        etatOccupation = true;
    }
    else
    {
        etatLumieres = false;
    }
#else
    etatLumieres   = etatsLumiere[salle][numeroMesure];
#endif
    return String(etatLumieres);
}

/**
 * @brief Retourne l'état d'occupation simulé d'une salle
 * @return String
 */
String getEtatOccupation(Salle salle)
{
#ifdef SIMULATION_ALEATOIRE
    int taus = random(0, 5); // 1 fois sur 5
    if(taus == 1)
        etatOccupation = true;
    else
        etatOccupation = false;
#else
    etatOccupation = etatsPresence[salle][numeroMesure];
#endif
    return String(etatOccupation);
}

/**
 * @brief Retourne le niveau de confort simulé
 * @return String le niveau de confort simulé
 */
String getIndiceNiveauConfort()
{
    if(temperature >= 24.0)
    {
        indiceNiveauConfort = 2;
    }
    else if(temperature >= 21.0)
    {
        indiceNiveauConfort = 1;
    }
    else if(temperature >= 19.0)
    {
        indiceNiveauConfort = 0;
    }
    else
    {
        if(temperature <= 16.0)
        {
            indiceNiveauConfort = -2;
        }
        else
        {
            indiceNiveauConfort = -1;
        }
    }

    if(humidite >= 60 && temperature >= 26.0)
    {
        indiceNiveauConfort = 3;
    }
    if(humidite <= 40 && temperature <= 22.0)
    {
        indiceNiveauConfort = -3;
    }

    return String(indiceNiveauConfort);
}

/**
 * @brief Retourne l'indice de qualité d'air simulé
 * @return String l'indice de qualité d'air simulé
 */
String getIndiceQualiteAir()
{
    // Bon : jusqu’à 1000 ppm
    // Mauvais : niveaux supérieurs à 2000 ppm
    if(co2 >= 2200)
        indiceQualiteAir = 6;
    else if(co2 >= 2000)
        indiceQualiteAir = 5;
    else if(co2 >= 1600)
        indiceQualiteAir = 4; // médiocre
    else if(co2 >= 1000)
        indiceQualiteAir = 3; // moyen
    else
    {
        if(co2 <= 800)
            indiceQualiteAir = 1;
        else
            indiceQualiteAir = 2; // bon
    }

    return String(indiceQualiteAir);
}

/** @brief Retourne l'enum de la salle
 * @return String
 */
Salle getSalle(String nomSalle)
{
    String salle;
    for(int i = 0; i < NB_SALLES; ++i)
    {
        salle = String(prefixeSalle) + salles[i];
        if(salle == nomSalle)
            return Salle(i);
    }
    return Salle::Inconnue;
}