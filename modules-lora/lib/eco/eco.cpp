#include "eco.h"

String typesMesure[NB_TYPES_MESURE] = {
    String("temperature"), String("humidite"), String("confort"),
    String("luminosite"),  String("co2"),      String("air"),
    String("fenetres"),    String("lumieres"), String("occupation")
}; //!< les types de mesure

String salles[NB_SALLES] = { String("11"),
                             String("20"),
                             String("21"),
                             String("22") }; //!< les noms des salles

uint16_t luminosite;  //!< valeur de l'éclairement lumineux en lux
uint8_t  humidite;    //!< valeur de l'humidité en %
float    temperature; //!< valeur de la température en degré Celcius
uint16_t co2;         //!< valeur de co2 en ppm
int      indiceNiveauConfort = -1;    //!< l'indice de confort
int      indiceQualiteAir    = 0;     //!< l'indice de qualité d'air
bool     etatLumieres        = false; //!< état des lumières
bool     etatFenetres        = false; //!< état des fenêtres
bool     etatOccupation      = false; //!< état d'occupation

/**
 * @brief Simule une mesure pour une salle
 * @return String le message à envoyer en LoRa
 */
String simulerMesure(char prefixeSalle)
{
    if(runEvery(PERIODE))
    {
        // sélectionne une salle aléatoirement
        String salle = String(prefixeSalle) + salles[random(0, NB_SALLES)];

        // sélectionne un type de mesure
        TypeMesure typeMesure = (TypeMesure)random(0, long(NB_TYPES_MESURE));
        String     nomMesure  = typesMesure[typeMesure];

        String message =
          salle + String("/") + nomMesure + String("/") + getMesure(typeMesure);

        return message;
    }
    return String("");
}

/**
 * @brief Retourne une mesure simulée
 * @return String
 */
String getMesure(TypeMesure typeMesure)
{
    switch(typeMesure)
    {
        case Temperature:
            return getTemperature();
        case Humidite:
            return getHumidite();
            break;
        case Confort:
            return getIndiceNiveauConfort();
            break;
        case Luminosite:
            return getLuminosite();
            break;
        case CO2:
            return getCO2();
            break;
        case Air:
            return getIndiceQualiteAir();
            break;
        case Fenetres:
            return getEtatFenetres();
            break;
        case Lumieres:
            return getEtatLumieres();
            break;
        case Occupation:
            return getEtatOccupation();
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
 * @brief Retourne la température simulée en °C
 * @return String
 */
String getTemperature()
{
    float delta = (float(random(0, 200)) / 10.);
    temperature = 15.0 + delta;
    return String(temperature, 1);
}

/**
 * @brief Retourne l'humidité simulée en %
 * @return String
 */
String getHumidite()
{
    humidite = random(30, 80);
    return String(humidite);
}

/**
 * @brief Retourne la luminosité simulée en lux
 * @return String
 */
String getLuminosite()
{
    luminosite = random(10, 1000);
    return String(luminosite);
}

/**
 * @brief Retourne le niveau de CO2 simulé en ppm
 * @return String
 */
String getCO2()
{
    // Bon : jusqu’à 1000 ppm
    // Mauvais : niveaux supérieurs à 2000 ppm
    // Plage 450 - 2450
    int taus = random(0, 5); // 1 fois sur 5
    if(taus == 1)
        co2 = 400 + random(0, 2000);
    else
        co2 = 400 + random(0, 800);
    return String(co2);
}

/**
 * @brief Retourne l'état des fenêtres simulé
 * @return String
 */
String getEtatFenetres()
{
    int taus = random(0, 5); // 1 fois sur 5
    if(taus == 1)
        etatFenetres = true;
    else
        etatFenetres = false;
    return String(etatFenetres);
}

/**
 * @brief Retourne l'état des lumières simulé
 * @return String
 */
String getEtatLumieres()
{
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
    return String(etatLumieres);
}

/**
 * @brief Retourne l'état d'occupation simulé d'une salle
 * @return String
 */
String getEtatOccupation()
{
    int taus = random(0, 5); // 1 fois sur 5
    if(taus == 1)
        etatOccupation = true;
    else
        etatOccupation = false;
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

bool runEvery(unsigned long interval)
{
    static unsigned long previousMillis = 0;
    unsigned long        currentMillis  = millis();

    if(currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;
        return true;
    }

    return false;
}
