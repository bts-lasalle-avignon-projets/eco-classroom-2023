/**
 * @file mesures.h
 * @brief Déclaration de la classe Mesures
 */

#ifndef SALLE_H
#define SALLE_H

#include <QString>

/**
 * @def RACINE_TOPIC
 * @brief La racine des topics
 */
#define RACINE_TOPIC "salles"

#define SEUIL_ALERTE_CO2 1300

// Constantes utilisées pour evaluer la qualité de l'air
#define SEUIL_BAS_QUALITE_AIR_EXCELLENTE    0
#define SEUIL_HAUT_QUALITE_AIR_EXCELLENTE   400
#define SEUIL_BAS_QUALITE_AIR_TRES_BIEN     401
#define SEUIL_HAUT_QUALITE_AIR_TRES_BIEN    1000
#define SEUIL_BAS_QUALITE_AIR_MODERE        1001
#define SEUIL_HAUT_QUALITE_AIR_MODERE       1500
#define SEUIL_BAS_QUALITE_AIR_MAUVAIS       1501
#define SEUIL_HAUT_QUALITE_AIR_MAUVAIS      2000
#define SEUIL_BAS_QUALITE_AIR_TRES_MAUVAIS  2001
#define SEUIL_HAUT_QUALITE_AIR_TRES_MAUVAIS 5000
#define SEUIL_BAS_QUALITE_AIR_SEVERE        5001

#define EXCELLENTE   "Excellente"
#define TRES_BIEN    "Très Bien"
#define MODERE       "Modéré"
#define MAUVAIS      "Mauvais"
#define TRES_MAUVAIS "Très Mauvais"
#define SEVERE       "Sévère"

#define CONFINEMENT_NUL        0
#define CONFINEMENT_FAIBLE     1
#define CONFINEMENT_MOYEN      2
#define CONFINEMENT_ELEVE      3
#define CONFINEMENT_TRES_ELEVE 4
#define CONFINEMENT_EXTREME    5

class Mesures;
class EtatsSalle;

/**
 * @class EcoClassroom
 * @brief Classe permettant de gérer une salle
 */
class Salle
{
  public:
    enum ChampsTopic
    {
        RACINE,
        SALLE,
        MODULE,
        TYPE_DONNEE
    };

  private:
    QString      nom;         //!< Nom de la salle
    unsigned int superficie;  //!< Superficie de la salle
    QString      description; //!< Description de la salle
    int          indiceICONE; //!< indice Confinement de la salle
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
        Excellente,
        Tres_Bien,
        Modere,
        Mauvais,
        Tres_Mauvais,
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
    void         setCO2(unsigned int co2);
    int          getIndiceICONE();
    QString      afficherNiveauICONE() const;
    bool         getLumiere() const;
    bool         getFenetre() const;
    bool         getOccupation() const;
    void         calculerTHI();
    void         calculerIADI();
};

#endif // SALLE_H
