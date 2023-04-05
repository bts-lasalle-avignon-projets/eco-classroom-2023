#ifndef MESURES_H
#define MESURES_H

class Mesures
{
  private:
    double       temperature; //!< Temperature dans la salle
    unsigned int humidite;    //!< Humidite dans la salle
    unsigned int co2;         //!< Taux de CO2 dans la salle

  public:
    Mesures();
    ~Mesures();

    double       getTemperature() const;
    unsigned int getHumidite() const;
    unsigned int getCO2() const;
    void         setTemperature(double temperature);
    void         setHumidite(unsigned int humidite);
    void         setCO2(unsigned int co2);
};

#endif // MESURES_H
