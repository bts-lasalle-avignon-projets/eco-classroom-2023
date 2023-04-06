#include "salle.h"
#include "mesures.h"
#include "etatsalle.h"
#include <QDebug>

Salle::Salle() :
    nom(""), superficie(0), description(""), mesures(new Mesures),
    etats(new EtatsSalle)
{
    qDebug() << Q_FUNC_INFO;
}

Salle::Salle(QString nom, unsigned int superficie, QString description) :
    nom(nom), superficie(superficie), description(description),
    mesures(new Mesures), etats(new EtatsSalle)
{
    qDebug() << Q_FUNC_INFO << "nom" << nom << "superficie" << superficie
             << "description" << description;
}
/**
 * @fn EcoClassroom::getNom
 * @brief Retourne l'attribut nom sous forme de QString
 */
QString Salle::getNom() const
{
    return nom;
}

/**
 * @fn EcoClassroom::getSuperficie
 * @brief Retourne l'attribut superficie sous forme d'un entier positif
 */
unsigned int Salle::getSuperficie() const
{
    return superficie;
}

/**
 * @fn EcoClassroom::getDescription
 * @brief Retourne l'attribut description sous forme de QString
 */
QString Salle::getDescription() const
{
    return description;
}

void Salle::afficherInformationsSalle(const Salle& salle)
{
    qInfo() << "Nom : " << salle.getNom() << "\n"
            << "Superficie : " << salle.getSuperficie() << "\n"
            << "Description : " << salle.getDescription() << "\n";
}

unsigned int Salle::getTemperature() const
{
    if(mesures != nullptr)
        return mesures->getTemperature();
    return 0;
}

unsigned int Salle::getHumidite() const
{
    if(mesures != nullptr)
        return mesures->getHumidite();
    return 0;
}

unsigned int Salle::getCO2() const
{
    if(mesures != nullptr)
        return mesures->getCO2();
    return 0;
}

bool Salle::getLumiere() const
{
    if(etats != nullptr)
        return etats->getLumiere();
    return false;
}

bool Salle::getFenetre() const
{
    if(etats != nullptr)
        return etats->getFenetre();
    return false;
}

bool Salle::getOccupation() const
{
    if(etats != nullptr)
        return etats->getOccupation();
    return false;
}

void Salle::calculerTHI()
{
}

void Salle::calculerIADI()
{
}

void Salle::calculerICONE()
{
}
