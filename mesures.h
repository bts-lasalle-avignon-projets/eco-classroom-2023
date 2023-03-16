#ifndef MESURES_H
#define MESURES_H


class Mesures
{
private:
    int temperature;
    int humidite;
    int CO2;
    int luminosite;
public:
    Mesures();
    ~Mesures();
    int calculTHI();
    int calculIADI();
    int calculICONE();
    int getTemperature();
    int getHumidite();
    int getCO2();
    int getLuminosite();
};

#endif // MESURES_H
