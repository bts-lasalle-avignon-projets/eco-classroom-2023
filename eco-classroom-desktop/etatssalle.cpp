<<<<<<< HEAD:eco-classroom-desktop/etatssalle.cpp
#include "etatssalle.h"
=======
/**
 * @file etatsalle.cpp
 * @brief Définition de la classe EtatsSalle
 */

#include "etatsalle.h"
>>>>>>> 89131f2eb499b7830a36b46c1ac1a86225fb4f19:eco-classroom-desktop/etatsalle.cpp
#include <QDebug>

/**
 * @fn EtatsSalle::EtatsSalle
 * @brief Constructeur par defaut de la classe EtatsSalle
 * @param attributs initialisés à false par défaut
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
 * @details Libère les ressources de l'application
 */
EtatsSalle::~EtatsSalle()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @fn EtatsSalle::getLumiere
 * @brief Getter de l'attribut lumiere
<<<<<<< HEAD:eco-classroom-desktop/etatssalle.cpp
 * @return Retourne l'attribut lumiere
=======
 * @return bool l'état de la lumière dans la salle (true : allumée)
>>>>>>> 89131f2eb499b7830a36b46c1ac1a86225fb4f19:eco-classroom-desktop/etatsalle.cpp
 */
bool EtatsSalle::getLumiere() const
{
    return lumiere;
}

/**
 * @fn EtatsSalle::getFenetre
 * @brief Getter de l'attribut fenetre
 * @return Retourne l'attribut fenetre
 */
bool EtatsSalle::getFenetre() const
{
    return fenetre;
}

/**
 * @fn EtatsSalle::getOccupation
 * @brief Getter de l'attribut occupation
 * @return Retourne l'attribut occupation
 */
bool EtatsSalle::getOccupation() const
{
    return occupation;
}

/**
 * @fn EtatsSalle::setLumiere
 * @brief Setter de l'attribut lumiere
 */
void EtatsSalle::setLumiere(bool lumiere)
{
    this->lumiere = lumiere;
}

/**
 * @fn EtatsSalle::setFenetre
 * @brief Setter de l'attribut fenetre
 */
void EtatsSalle::setFenetre(bool fenetre)
{
    this->fenetre = fenetre;
}

/**
 * @fn EtatsSalle::setOccupation
 * @brief Setter de l'attribut occupation
 */
void EtatsSalle::setOccupation(bool occupation)
{
    this->occupation = occupation;
}