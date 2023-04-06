#ifndef SALLE_H
#define SALLE_H

#include <QString>

class Mesures;
class EtatsSalle;

class Salle
{
  private:
    QString      nom;
    unsigned int superficie;
    QString      description;
    Mesures*     mesures;
    EtatsSalle*  etats;

  public:
    Salle();
    Salle(QString nom, unsigned int superficie, QString description);
    QString      getNom() const;
    unsigned int getSuperficie() const;
    QString      getDescription() const;
    void         afficherInformationsSalle(const Salle& salle);
    unsigned int getTemperature() const;
    unsigned int getHumidite() const;
    unsigned int getCO2() const;
    bool         getLumiere() const;
    bool         getFenetre() const;
    bool         getOccupation() const;
    void         calculerTHI();
    void         calculerIADI();
    void         calculerICONE();
};

#endif // SALLE_H
