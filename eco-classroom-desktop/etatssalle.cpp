/**
 * @file etatsalle.cpp
 * @brief Définition de la classe EtatsSalle
 */
#include "etatssalle.h"

#include <QDebug>

/**
 * @fn EtatsSalle::EtatsSalle
 * @brief Constructeur par defaut de la classe EtatsSalle
 * @param lumiere l'état de la lumière dans la salle
 * @param fenetre l'état d'ouverture des fenêtres de la salle
 * @param occupation l'état d'occupation de la salle
 */
EtatsSalle::EtatsSalle() : lumiere(false), fenetre(false), occupation(false)
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @fn EtatsSalle::EtatsSalle
 * @brief Constructeur d'initialisation de la classe EtatsSalle
 * @param lumiere l'état de la lumière dans la salle (true : allumée)
 * @param fenetre l'état d'ouverture des fenêtres de la salle (true : ouverte)
 * @param occupation l'état d'occupation de la salle (true : occupée)
 */
EtatsSalle::EtatsSalle(bool lumiere, bool fenetre, bool occupation) :
    lumiere(lumiere), fenetre(fenetre), occupation(occupation)
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @fn EtatsSalle::~EtatsSalle
 * @brief Destructeur de la clase EtatsSalle
 */
EtatsSalle::~EtatsSalle()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @fn EtatsSalle::getLumiere
 * @brief Getter de l'attribut lumiere
 * @return bool l'état de la lumière dans la salle (true : allumée)
 */
bool EtatsSalle::getLumiere() const
{
    return lumiere;
}

/**
 * @fn EtatsSalle::getFenetre
 * @brief Getter de l'attribut fenetre
 * @return bool l'état d'une fenetre dans la salle (true : ouverte)
 */
bool EtatsSalle::getFenetre() const
{
    return fenetre;
}

/**
 * @fn EtatsSalle::getOccupation
 * @brief Getter de l'attribut occupation
 * @return bool l'état de l'occupation dans la salle (true : Occupé)
 */
bool EtatsSalle::getOccupation() const
{
    return occupation;
}

/**
 * @fn EtatsSalle::setLumiere
 * @brief Setter de l'attribut lumiere
 * @param lumiere l'état de la lumière dans la salle (true : allumée)
 */
void EtatsSalle::setLumiere(bool lumiere)
{
    this->lumiere = lumiere;
}

/**
 * @fn EtatsSalle::setFenetre
 * @brief Setter de l'attribut fenetre
 * @param fenetre l'état d'ouverture des fenêtres dans la salle (true : ouverte)
 */
void EtatsSalle::setFenetre(bool fenetre)
{
    this->fenetre = fenetre;
}

/**
 * @fn EtatsSalle::setOccupation
 * @brief Setter de l'attribut occupation
 * @param occupation l'état d'occupation de la salle (true : occupée)
 */
void EtatsSalle::setOccupation(bool occupation)
{
    this->occupation = occupation;
}
