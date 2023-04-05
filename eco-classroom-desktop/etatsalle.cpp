#include "etatsalle.h"

EtatsSalle::EtatsSalle() : lumiere(false), fenetre(true), occupation(false)
{
}

EtatsSalle::~EtatsSalle()
{
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
