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
 * @brief Salle::getTypeMessage
 * @param typeDonnee
 * @return
 */
Salle::TypeMessage Salle::getTypeMessage(QString typeDonnee)
{
    QVector<QString> typesMessage = { "temperature", "humidite", "co2",
                                      "lumiere",     "fenetre",  "presence" };

    for(int i = 0; i < typesMessage.size(); i++)
    {
        if(typeDonnee == typesMessage[i])
            return Salle::TypeMessage(i);
    }
    return Salle::TypeMessage::INCONNU;
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
 * @fn Salle::getIndiceQualiteAir() const
 * @brief Méthode qui récupère l'indice de la Qualité de l'Air grâce a
 * l'attribut Co2 de l'objet Salle
 * @return int
 */
int Salle::getIndiceQualiteAir() const
{
    return indiceQualiteAir;
}

/**
 * @fn Salle::getIndiceICONE
 * @brief méthode qui calcule l'indice ICONE(indice de confinement) et qui le
 * retourne
 * @return
 */
int Salle::getIndiceICONE() const
{
    return indiceICONE;
}

void Salle::calculerIndiceICONE()
{
    indiceICONE = mesures->calculerIndiceICONE();
    qDebug() << Q_FUNC_INFO << "indiceICONE" << indiceICONE;
}

/**
 * @brief Salle::getTHI
 * @return les différents niveaux après le calcul du THI
 */
QString Salle::getTHI() const
{
    switch(indiceConfortTHI)
    {
        case IndiceTHI::Inconnu:
            return THI_INCONNU;
            break;
        case IndiceTHI::Froid:
            return FROID;
            break;
        case IndiceTHI::Frais:
            return FRAIS;
            break;
        case IndiceTHI::LegerementFrais:
            return LEGEREMENT_FRAIS;
            break;
        case IndiceTHI::Neutre:
            return NEUTRE;
            break;
        case IndiceTHI::LegerementTiede:
            return LEGEREMENT_TIEDE;

            break;
        case IndiceTHI::Tiede:
            return TIEDE;
            break;
        case IndiceTHI::Chaud:
            return CHAUD;
            break;
        default:
            return THI_INCONNU;
            break;
    }
}

/**
 * @fn Salle::getLumiere()
 * @brief Getter qui récupère l'etat de la lumiere
 */
bool Salle::getLumiere() const
{
    if(etats != nullptr)
        return etats->getLumiere();
    return false;
}

/**
 * @fn Salle::getFenetre()
 * @brief Getter qui récupère l'etat de la fenetre
 */
bool Salle::getFenetre() const
{
    if(etats != nullptr)
        return etats->getFenetre();
    return false;
}

/**
 * @fn Salle::getOccupation()
 * @brief Getter qui récupère l'etat de l'occupation de la salle
 */
bool Salle::getOccupation() const
{
    if(etats != nullptr)
        return etats->getOccupation();
    return false;
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
 * @brief Salle::setTemperature
 * @param temperature
 */
void Salle::setTemperature(unsigned int temperature)
{
    mesures->setTemperature(temperature);
}

/**
 * @brief Salle::setHumidite
 * @param humidite
 */
void Salle::setHumidite(unsigned int humidite)
{
    mesures->setHumidite(humidite);
}

/**
 * @brief Setter qui attribut une valeur a l'attribut Co2 de l'objet Salle
 * @param co2
 */
void Salle::setCO2(unsigned int co2)
{
    mesures->setCO2(co2);
}

/**
 * @fn Salle::setOccupation()
 * @brief Setter qui attribut une valeur a l'attribut occupation de l'objet
 * Salle
 */
void Salle::setOccupation(bool occupation) const
{
    etats->setOccupation(occupation);
}

/**
 * @fn Salle::setOccupation()
 * @brief Setter qui attribut une valeur a l'attribut lumiere de l'objet Salle
 */
void Salle::setLumiere(bool lumiere) const
{
    etats->setLumiere(lumiere);
}

/**
 * @fn Salle::setOccupation()
 * @brief Setter qui attribut une valeur a l'attribut fenetre de l'objet Salle
 */
void Salle::setFenetre(bool fenetre) const
{
    etats->setFenetre(fenetre);
}

void Salle::setIndiceTHI(int indiceTHI)
{
    this->indiceConfortTHI = indiceTHI;
}

void Salle::setIndiceQualiteAir(int indiceQualiteAir)
{
    this->indiceQualiteAir = indiceQualiteAir;
}

void Salle::setIndiceICONE(int indiceICONE)
{
    this->indiceICONE = indiceICONE;
}

void Salle::determinerIndiceQualiteAir()
{
    unsigned int valeurCO2 = getCO2();
    if(valeurCO2 <= SEUIL_HAUT_QUALITE_AIR_EXCELLENTE)
        indiceQualiteAir = IndiceQualiteAir::Excellente;
    else if(valeurCO2 >= SEUIL_BAS_QUALITE_AIR_TRES_BIEN &&
            valeurCO2 <= SEUIL_HAUT_QUALITE_AIR_TRES_BIEN)
        indiceQualiteAir = IndiceQualiteAir::Tres_Bien;
    else if(valeurCO2 >= SEUIL_BAS_QUALITE_AIR_MODERE &&
            valeurCO2 <= SEUIL_HAUT_QUALITE_AIR_MODERE)
        indiceQualiteAir = IndiceQualiteAir::Modere;
    else if(valeurCO2 >= SEUIL_BAS_QUALITE_AIR_MAUVAIS &&
            valeurCO2 <= SEUIL_HAUT_QUALITE_AIR_MAUVAIS)
        indiceQualiteAir = IndiceQualiteAir::Mauvais;
    else if(valeurCO2 >= SEUIL_BAS_QUALITE_AIR_TRES_MAUVAIS &&
            valeurCO2 <= SEUIL_HAUT_QUALITE_AIR_TRES_MAUVAIS)
        indiceQualiteAir = IndiceQualiteAir::Tres_Mauvais;
    else
        indiceQualiteAir = IndiceQualiteAir::Severe;
}

void Salle::determinerIndiceTHI()
{
    double thom = mesures->calculerTHI();
    qDebug() << Q_FUNC_INFO << "thom" << thom;
    if(thom < SEUIL_THOM_FROID)
    {
        indiceConfortTHI = IndiceTHI::Froid;
    }
    else if(thom >= SEUIL_THOM_FROID && thom < SEUIL_THOM_FRAIS)
    {
        indiceConfortTHI = IndiceTHI::Frais;
    }
    else if(thom >= SEUIL_THOM_FRAIS && thom < SEUIL_THOM_LEGEREMENT_FRAIS)
    {
        indiceConfortTHI = IndiceTHI::LegerementFrais;
    }
    else if(thom >= SEUIL_THOM_LEGEREMENT_FRAIS && thom < SEUIL_THOM_NEUTRE)
    {
        indiceConfortTHI = IndiceTHI::Neutre;
    }
    else if(thom >= SEUIL_THOM_NEUTRE && thom < SEUIL_THOM_LEGEREMENT_TIEDE)
    {
        indiceConfortTHI = IndiceTHI::Tiede;
    }
    else if(thom >= SEUIL_THOM_LEGEREMENT_TIEDE && thom < SEUIL_THOM_TIEDE)
    {
        indiceConfortTHI = IndiceTHI::LegerementTiede;
    }
    else if(thom >= SEUIL_THOM_TIEDE)
    {
        indiceConfortTHI = IndiceTHI::Chaud;
    }
    else
        indiceConfortTHI = IndiceTHI::Inconnu;
    qDebug() << Q_FUNC_INFO << "indiceConfortTHI" << indiceConfortTHI
             << getTHI();
}

int Salle::getIndiceTHI() const
{
    return indiceConfortTHI;
}
