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
 * @fn Salle::~Salle
 * @brief Destructeur de la classe Salle
 */
Salle::Salle(QString nom, unsigned int superficie, QString description) :
    nom(nom), superficie(superficie), description(description),
    mesures(new Mesures), etats(new EtatsSalle)
{
    qDebug() << Q_FUNC_INFO << "nom" << nom << "superficie" << superficie
             << "description" << description;
}

/**
 * @fn Salle::getNom
 * @brief Getter de l'attribut nom
 * @return string le nom de la salle
 */
QString Salle::getNom() const
{
    return nom;
}

/**
 * @fn Salle::getTemperature
 * @brief Getter qui récupère la temperature si mesures est différent de nullptr
 */
unsigned int Salle::getTemperature() const
{
    if(mesures != nullptr)
        return mesures->getTemperature();
    return 0;
}

/**
 * @fn Salle::getHumidite
 * @brief Getter qui récupère l'humidite si mesures est différent de nullptr
 */
unsigned int Salle::getHumidite() const
{
    if(mesures != nullptr)
        return mesures->getHumidite();
    return 0;
}

/**
 * @fn Salle::getCO2
 * @brief Getter qui récupère le CO2 si mesures est différent de nullptr
 */
unsigned int Salle::getCO2() const
{
    if(mesures != nullptr)
        return mesures->getCO2();
    return 0;
}

/**
 * @fn Salle::getLumiere
 * @brief Getter qui récupère l'etat de la lumiere si mesures est différent de
 * nullptr
 */
bool Salle::getLumiere() const
{
    if(etats != nullptr)
        return etats->getLumiere();
    return false;
}

/**
 * @fn Salle::getFenetre
 * @brief Getter qui récupère l'etat de la fenetre si mesures est différent de
 * nullptr
 */
bool Salle::getFenetre() const
{
    if(etats != nullptr)
        return etats->getFenetre();
    return false;
}

/**
 * @fn Salle::getOccupation
 * @brief Getter qui récupère l'etat de l'occupation de la salle si mesures est
 * différent de nullptr
 */
bool Salle::getOccupation() const
{
    if(etats != nullptr)
        return etats->getOccupation();
    return false;
}
