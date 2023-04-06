/**
 * @file mesures.cpp
 * @brief Définition de la classe Mesures
 */
#include "mesures.h"
#include <QDebug>

/**
 * @fn Mesures::Mesures
 * @brief Constructeur de la classe Mesures
 * @param temperature mesure de la temperature dans la salle
 * @param humidite mesure de l'humidite dans la salle
 * @param co2 mesure du co2 dans la salle
 */
Mesures::Mesures() : temperature(0.), humidite(0), co2(0)
{
}

/**
 * @fn Mesures::~Mesures
 * @brief Destructeur de la classe Mesures
 * @details Libère les ressources de l'application
 */
Mesures::~Mesures()
{
}

/**
 * @fn Mesures::getTemperature
 * @brief Getter de l'attribut temperature
 * @return int la valeur de la temperature (C°)
 */
double Mesures::getTemperature() const
{
    return temperature;
}

/**
 * @fn Mesures::getHumidite
 * @brief Getter de l'attribut humidite
 * @return int la valeur de l'humidité (%)
 */
unsigned int Mesures::getHumidite() const
{
    return humidite;
}

/**
 * @fn Mesures::getCO2
 * @brief Getter de l'attribut co2
 * @return int la valeur du co2 (ppm)
 */
unsigned int Mesures::getCO2() const
{
    return co2;
}

/**
 * @fn Mesures::setTemperature
 * @brief Setter de l'attribut temperature
 */
void Mesures::setTemperature(double temperature)
{
    this->temperature = temperature;
}

/**
 * @fn Mesures::setHumidite
 * @brief Setter de l'attribut humidite
 */
void Mesures::setHumidite(unsigned int humidite)
{
    this->humidite = humidite;
}

/**
 * @fn Mesures::setCO2
 * @brief Setter de l'attribut co2
 */
void Mesures::setCO2(unsigned int co2)
{
    this->co2 = co2;
}
