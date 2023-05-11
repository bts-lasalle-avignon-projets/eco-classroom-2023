/**
 * @file mesures.cpp
 * @brief Définition de la classe Mesures
 */
#include "mesures.h"
#include <QDebug>
#include <tgmath.h>

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
    if(co2.size() > 0)
    {
        qDebug() << Q_FUNC_INFO << "co2" << co2.back();
        // la dernière mesure
        return co2.back();
    }
    else
        return 0;
}

/**
 * @fn Mesures::setTemperature
 * @brief Setter de l'attribut temperature
 * @param temperature mesure de la temperature dans la salle
 */
void Mesures::setTemperature(double temperature)
{
    this->temperature = temperature;
}

/**
 * @fn Mesures::setHumidite
 * @brief Setter de l'attribut humidite
 * @param humidite mesure de l'humidite dans la salle
 */
void Mesures::setHumidite(unsigned int humidite)
{
    this->humidite = humidite;
}

/**
 * @fn Mesures::setCO2
 * @brief Setter de l'attribut co2
 * @param co2 mesure du co2 dans la salle
 */
void Mesures::setCO2(unsigned int mesureCo2)
{
    co2.push_back(mesureCo2);
}

/**
 * @fn Mesures::calculerIndiceICONE
 * @brief calcule l'indice ICONE
 * @return
 */
int Mesures::calculerIndiceICONE()
{
    double proportionSeuilN1 = calculerProportionSeuilN1();
    double proportionSeuilN2 = calculerProportionSeuilN2();
    int indiceBrute = calculerIndiceBrute(proportionSeuilN1, proportionSeuilN2);
    int indiceICONE = determinerIndiceICONE(indiceBrute);
    qDebug() << Q_FUNC_INFO << "indiceICONE" << indiceICONE;
    return indiceICONE;
}

/**
 * @fn Mesures::calculerProportionSeuilN1
 * @brief calcule la proportion de valeurs de Co2 comprises entre 1000 et 17000
 * ppm
 * @return
 */
double Mesures::calculerProportionSeuilN1()
{
    int nbValeursSeuilN1 = 0;
    for(int i = 0; i < co2.size(); i++)
    {
        if((co2[i] >= 1000) && (co2[i] <= 1700))
        {
            nbValeursSeuilN1++;
        }
    }
    qDebug() << Q_FUNC_INFO << "nbValeursSeuilN1" << nbValeursSeuilN1;
    return double(nbValeursSeuilN1) / double(co2.size());
}

/**
 * @fn Mesures::calculerProportionSeuilN2
 * @brief calcule la proportion de valeurs de Co2 supérieurs à 1700 ppm
 * @return
 */
double Mesures::calculerProportionSeuilN2()
{
    int nbValeursSeuilN2 = 0;
    qDebug() << "co2";
    for(int i = 0; i < co2.size(); i++)
    {
        if(co2[i] >= 1700)
        {
            nbValeursSeuilN2++;
        }
        qDebug() << co2[i];
    }
    qDebug() << "nbValeursSeuilN2" << nbValeursSeuilN2;
    return double(nbValeursSeuilN2) / double(co2.size());
}

/**
 * @fn Mesures::calculerIndiceBrute
 * @param proportionSeuilN1
 * @param proportionSeuilN2
 * @brief calcule l'indice Brute permettant de calculer l'indice ICONE
 * @return
 */
int Mesures::calculerIndiceBrute(double proportionSeuilN1,
                                 double proportionSeuilN2)
{
    qDebug() << "proportionSeuilN1" << proportionSeuilN1;
    qDebug() << "proportionSeuilN2" << proportionSeuilN2;
    double calculIndiceBrute = 0.;
    calculIndiceBrute =
      ((2.5 / log10(2)) *
       (log10(1 + proportionSeuilN1 + (3 * proportionSeuilN2))));
    qDebug() << "calculIndiceBrute" << calculIndiceBrute;
    int indiceBrute = nearbyint(calculIndiceBrute);
    qDebug() << "indiceBrute" << indiceBrute;
    return indiceBrute;
}

/**
 * @fn Mesures::determinerIndiceICONE
 * @param indiceBrute
 * @brief determine l'indice ICONE par rapport à l'indice Brute
 * @return
 */
int Mesures::determinerIndiceICONE(int indiceBrute)
{
    if(indiceBrute < 0.5)
        return CONFINEMENT_NUL;
    else if((indiceBrute >= 0.5) && indiceBrute < 1.5)
        return CONFINEMENT_FAIBLE;
    else if((indiceBrute >= 1.5) && indiceBrute < 2.5)
        return CONFINEMENT_MOYEN;
    else if((indiceBrute >= 2.5) && indiceBrute < 3.5)
        return CONFINEMENT_ELEVE;
    else if((indiceBrute >= 3.5) && indiceBrute < 4.5)
        return CONFINEMENT_TRES_ELEVE;
    else if(indiceBrute >= 4.5)
        return CONFINEMENT_EXTREME;
    else
        return -1;
}
