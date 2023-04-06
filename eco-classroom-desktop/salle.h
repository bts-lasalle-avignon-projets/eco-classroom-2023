#ifndef SALLE_H
#define SALLE_H

/**
 * @file mesures.h
 */
#include <QString>

class Mesures;
class EtatsSalle;

/**
 * @class EcoClassroom
 * @brief Déclaration de la classe Mesures
 */
class Salle
{
  private:
    QString      nom;         //!< Nom de la salle
    unsigned int superficie;  //!< Superficie de la salle
    QString      description; //!< Description de la salle
    Mesures*
      mesures; //!<  Relation entre la classe Salle et Mesures (agrégation)
    EtatsSalle*
      etats; //!< Relation entre la classe Salle et EtatsSalle (agrégation)

  public:
    Salle();
    Salle(QString nom, unsigned int superficie, QString description);
    QString      getNom() const;
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
