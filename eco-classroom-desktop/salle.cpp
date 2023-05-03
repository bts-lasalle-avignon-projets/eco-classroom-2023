/**
 * @file salle.cpp
 * @brief Définition de la classe Salle
 */
#include "salle.h"
#include "mesures.h"
#include "etatssalle.h"
#include <QDebug>

/**
 * @fn Salle::Salle
 * @brief Constructeur par défaut de la classe Salle
 * @param nom données d'information sur le nom de la salle
 * @param superficie données d'information sur la superficie de la salle
 * @param description données d'information sur la descrption de la salle
 * @param mesures construction d'un objet mesures de la classe Mesures
 * @param etats construction d'un objet etats de la classe EtatsSalle
 */
Salle::Salle() :
    nom(""), superficie(0), description(""), mesures(new Mesures),
    etats(new EtatsSalle)
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @fn Salle::Salle
 * @brief Constructeur de la classe Salle
 */
Salle::Salle(QString nom, unsigned int superficie, QString description) :
    nom(nom), superficie(superficie), description(description),
    mesures(new Mesures), etats(new EtatsSalle)
{
    qDebug() << Q_FUNC_INFO << "nom" << nom << "superficie" << superficie
             << "description" << description;
}

/**
 * @brief Getter de l'attribut nom
 * @return string le nom de la salle
 */
QString Salle::getNom() const
{
    return nom;
}

/**
 * @brief Getter de l'attribut superficie
 * @return unsigned int la superficie de la salle
 */
unsigned int Salle::getSuperficie() const
{
    return superficie;
}

/**
 * @brief Getter de l'attribut description
 * @return string la description de la salle
 */
QString Salle::getDescription() const
{
    return description;
}

/**
 * @brief Setter de l'attribut nom
 * @param nom
 */
void Salle::setNom(QString nom)
{
    this->nom = nom;
}

/**
 * @brief Setter de l'attribut superficie
 * @param superficie
 */
void Salle::setSuperficie(unsigned int superficie)
{
    this->superficie = superficie;
}

/**
 * @brief Setter de l'attribut description
 * @param description
 */
void Salle::setDescription(QString description)
{
    this->description = description;
}

/**
 * @brief Getter qui récupère la temperature
 */
unsigned int Salle::getTemperature() const
{
    if(mesures != nullptr)
        return mesures->getTemperature();
    return 0;
}

/**
 * @brief Getter qui récupère l'humidite
 */
unsigned int Salle::getHumidite() const
{
    if(mesures != nullptr)
        return mesures->getHumidite();
    return 0;
}

/**
 * @brief Getter qui récupère le CO2
 */
unsigned int Salle::getCO2() const
{
    if(mesures != nullptr)
        return mesures->getCO2();
    return 0;
}

/**
 * @brief Getter qui évalue la qualité d'air grâce a l'attribut Co2 de l'objet
 * Salle
 */
QString Salle::getQualiteAir() const
{
    if(getCO2() > SEUIL_BAS_QAIR_EXCELLENTE &&
       getCO2() < SEUIL_HAUT_QAIR_EXCELLENTE)
    {
        return "Excellente";
    }

    else if(getCO2() > SEUIL_BAS_QAIR_BONNE && getCO2() < SEUIL_HAUT_QAIR_BONNE)
    {
        return "Bonne";
    }

    else if(getCO2() > SEUIL_BAS_QAIR_MOYENNE &&
            getCO2() < SEUIL_HAUT_QAIR_MOYENNE)
    {
        return "Moyenne";
    }

    else if(getCO2() > SEUIL_BAS_QAIR_NULLE && getCO2() < SEUIL_HAUT_QAIR_NULLE)
    {
        return "Nulle";
    }

    else if(getCO2() > SEUIL_BAS_QAIR_MEDIOCRE &&
            getCO2() < SEUIL_HAUT_QAIR_MEDIOCRE)
    {
        return "Mediocre";
    }

    else if(getCO2() > SEUIL_BAS_QAIR_SEVERE &&
            getCO2() < SEUIL_HAUT_QAIR_SEVERE)
    {
        return "Severe";
    }

    else
        return "Inexistante";
}

/**
 * @brief Setter qui attribut une valeur a l'attribut Co2 de l'objet Salle
 * @param co2
 */
void Salle::setCO2(unsigned int co2)
{
    mesures->setCO2(co2);
    qDebug() << Q_FUNC_INFO << "co2 : " << co2;
}

/**
 * @brief Getter qui récupère l'etat de la lumiere
 */
bool Salle::getLumiere() const
{
    if(etats != nullptr)
        return etats->getLumiere();
    return false;
}

/**
 * @brief Getter qui récupère l'etat de la fenetre
 */
bool Salle::getFenetre() const
{
    if(etats != nullptr)
        return etats->getFenetre();
    return false;
}

/**
 * @brief Getter qui récupère l'etat de l'occupation de la salle
 */
bool Salle::getOccupation() const
{
    if(etats != nullptr)
        return etats->getOccupation();
    return false;
}
