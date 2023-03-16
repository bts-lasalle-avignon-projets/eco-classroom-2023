#ifndef MESURES_H
#define MESURES_H


class Mesures
{
private:
    double temperature;
    unsigned int humidite;
    unsigned int CO2;
    unsigned int luminosite;

public:
    Mesures();
    ~Mesures();
    void calculerTHI();
    void calculerIADI();
    void calculerICONE();
    double getTemperature();
    unsigned int getHumidite();
    unsigned int getCO2();
    unsigned int getLuminosite();
};

#endif // MESURES_H
