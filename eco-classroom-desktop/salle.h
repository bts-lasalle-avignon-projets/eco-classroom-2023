#ifndef SALLE_H
#define SALLE_H
#include "mesures.h"
#include "etatsalle.h"

#include <QString>
#include <QTableWidgetItem>
#include <QLabel>

class Salle
{
  private:
    QString      nom;
    unsigned int superficie;
    QString      description;
    unsigned int temperature;
    unsigned int humidite;
    unsigned int CO2;
    Mesures*     mesures;
    EtatsSalle*  etats;
    void         afficherSallesTables(Salle salles);

  public:
    Salle();
    Salle(QString nom, unsigned int superficie, QString description);
    unsigned int getTemperature();
    unsigned int getHumidite();
    unsigned int getCO2();
};

#endif // SALLE_H
