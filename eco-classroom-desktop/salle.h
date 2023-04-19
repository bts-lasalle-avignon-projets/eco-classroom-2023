/**
 * @file mesures.h
 * @brief Déclaration de la classe Mesures
 */

#ifndef SALLE_H
#define SALLE_H

#include <QString>

#define SEUIL_ALERTE_CO2 1300

class Mesures;
class EtatsSalle;

/**
 * @class EcoClassroom
 * @brief Classe permettant de gérer une salle
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
    unsigned int getSuperficie() const;
    QString      getDescription() const;
    void         setNom(QString nom);
    void         setSuperficie(unsigned int superficie);
    void         setDescription(QString description);
    unsigned int getTemperature() const;
    unsigned int getHumidite() const;
    unsigned int getCO2() const;
    void         setCO2(unsigned int co2);
    bool         getLumiere() const;
    bool         getFenetre() const;
    bool         getOccupation() const;
    void         calculerTHI();
    void         calculerIADI();
    void         calculerICONE();
};

#endif // SALLE_H
