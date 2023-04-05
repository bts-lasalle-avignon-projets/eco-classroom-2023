#include "etatsalle.h"
#include <QDebug>

EtatsSalle::EtatsSalle() : lumiere(false), fenetre(false), occupation(false)
{
    qDebug() << Q_FUNC_INFO;
}

EtatsSalle::EtatsSalle(bool lumiere, bool fenetre, bool occupation) :
    lumiere(lumiere), fenetre(fenetre), occupation(occupation)
{
    qDebug() << Q_FUNC_INFO;
}

EtatsSalle::~EtatsSalle()
{
    qDebug() << Q_FUNC_INFO;
}

bool EtatsSalle::getLumiere() const
{
    return lumiere;
}

bool EtatsSalle::getFenetre() const
{
    return fenetre;
}

bool EtatsSalle::getOccupation() const
{
    return occupation;
}

void EtatsSalle::setLumiere(bool lumiere)
{
    this->lumiere = lumiere;
}

void EtatsSalle::setFenetre(bool fenetre)
{
    this->fenetre = fenetre;
}

void EtatsSalle::setOccupation(bool occupation)
{
    this->occupation = occupation;
}
