#ifndef MESURES_H
#define MESURES_H

class Mesures
{
  private:
    double       temperature;
    unsigned int humidite;
    unsigned int co2;
    unsigned int luminosite;

  public:
    Mesures();
    ~Mesures();

    double       getTemperature() const;
    unsigned int getHumidite() const;
    unsigned int getCO2() const;
    unsigned int getLuminosite() const;
    void         setTemperature(double temperature);
    void         setHumidite(unsigned int humidite);
    void         setCO2(unsigned int co2);
    void         setLuminosite(unsigned int luminosite);
};

#endif // MESURES_H
