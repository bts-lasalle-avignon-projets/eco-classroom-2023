/**
 * @file mesures.h
 * @brief Déclaration de la classe Mesures
 */

#ifndef SALLE_H
#define SALLE_H

#include <QString>

#define SEUIL_ALERTE_CO2 1300

#define SEUIL_QAIR_INEXISTANTE     0
#define SEUIL_BAS_QAIR_EXCELLENTE  1
#define SEUIL_HAUT_QAIR_EXCELLENTE 200
#define SEUIL_BAS_QAIR_BONNE       201
#define SEUIL_HAUT_QAIR_BONNE      400
#define SEUIL_BAS_QAIR_MOYENNE     401
#define SEUIL_HAUT_QAIR_MOYENNE    799
#define SEUIL_BAS_QAIR_NULLE       800
#define SEUIL_HAUT_QAIR_NULLE      999
#define SEUIL_BAS_QAIR_MEDIOCRE    1000
#define SEUIL_HAUT_QAIR_MEDIOCRE   1299
#define SEUIL_BAS_QAIR_SEVERE      1300
#define SEUIL_HAUT_QAIR_SEVERE     2500

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
    /*
     *
     * @enum IndiceQualiteAir
     * @brief Définit les différentes colonne du tableau

    enum IndiceQualiteAir
    {
        Inexistante,
        Excellente,
        Bonne,
        Moyenne,
        Nulle,
        Mediocre,
        Severe
    };
    */

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
    QString      getQualiteAir() const;

    void setCO2(unsigned int co2);
    bool getLumiere() const;
    bool getFenetre() const;
    bool getOccupation() const;
    void calculerTHI();
    void calculerIADI();
    void calculerICONE();
};

#endif // SALLE_H
