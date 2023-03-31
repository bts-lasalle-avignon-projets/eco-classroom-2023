#include "salle.h"

Salle::Salle() : nom(""), superficie(0), description("")
{
}

Salle::Salle(QString nom, unsigned int superficie, QString description) :
    nom(nom), superficie(superficie), description(description)
{
}

void Salle::afficherSallesTables(Salle salles)
{
}

unsigned int Salle::getTemperature()
{
    return temperature;
}

unsigned int Salle::getHumidite()
{
    return humidite;
}

unsigned int Salle::getCO2()
{
    return CO2;
}
