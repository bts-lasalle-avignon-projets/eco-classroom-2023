#include "mesures.h"

Mesures::Mesures() : temperature(0.), humidite(0), co2(0), luminosite(0)
{
}

Mesures::~Mesures()
{
}

double Mesures::getTemperature() const
{
    return temperature;
}

unsigned int Mesures::getHumidite() const
{
    return humidite;
}

unsigned int Mesures::getCO2() const
{
    return co2;
}

unsigned int Mesures::getLuminosite() const
{
    return luminosite;
}

void Mesures::setTemperature(double temperature)
{
    this->temperature = temperature;
}

void Mesures::setHumidite(unsigned int humidite)
{
    this->humidite = humidite;
}

void Mesures::setCO2(unsigned int co2)
{
    this->co2 = co2;
}

void Mesures::setLuminosite(unsigned int luminosite)
{
    this->luminosite = luminosite;
}
