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

#define CONFINEMENT_NUL        0
#define CONFINEMENT_FAIBLE     1
#define CONFINEMENT_MOYEN      2
#define CONFINEMENT_ELEVE      3
#define CONFINEMENT_TRES_ELEVE 4
#define CONFINEMENT_EXTREME    5

#define SEUIL_THOM_FROID            -1.7
#define SEUIL_THOM_FRAIS            13.
#define SEUIL_THOM_LEGEREMENT_FRAIS 15.
#define SEUIL_THOM_NEUTRE           20.
#define SEUIL_THOM_LEGEREMENT_TIEDE 26.5
#define SEUIL_THOM_TIEDE            30.

#define THI_INCONNU      "Inconnu"
#define FROID            "Froid"
#define FRAIS            "Frais"
#define LEGEREMENT_FRAIS "Légèrement frais"
#define NEUTRE           "Neutre"
#define LEGEREMENT_TIEDE "Légèrement tiède"
#define TIEDE            "Tiède"
#define CHAUD            "Chaud"

class Mesures;
class EtatsSalle;

/**
 * @class EcoClassroom
 * @brief Classe permettant de gérer une salle
 */
class Salle
{
  public:
    /**
     * @enum TypeMessage
     * @brief Les diffents type de données pouvant être reçu
     */
    enum TypeMessage
    {
        INCONNU = -1,
        TEMPERATURE,
        HUMIDITE,
        CO2,
        LUMIERE,
        FENETRE,
        OCCUPATION
    };
    /**
     * @enum ChampsTopic
     * @brief Les différents champs d'un topic MQTT
     */
    enum ChampsTopic
    {
        RACINE,
        SALLE,
        MODULE,
        TYPE_DONNEE
    };
    /**
     * @enum TableSalle
     * @brief Les différents champs de la table Salle
     */
    enum TableSalle
    {
        CHAMP_NOM = 1,
        CHAMP_DESCRIPTION,
        CHAMP_SUPERFICIE
    };
    /**
     * @enum IndiceQualiteAir
     * @brief Définit les différentes colonne du tableau
     */
    enum IndiceQualiteAir
    {
        Excellente = 1,
        Tres_Bien,
        Modere,
        Mauvais,
        Tres_Mauvais,
        Severe
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
    Salle();
    Salle(QString nom, unsigned int superficie, QString description);
    int          getIndiceQualiteAir() const;
    QString      afficherNiveauQualiteAir(int indiceQualiteAir) const;
    int          getIndiceICONE();
    static Salle::TypeMessage getTypeMessage(QString typeDonnee);
    QString                   getNom() const;
    unsigned int              getSuperficie() const;
    QString                   getDescription() const;
    unsigned int              getTemperature() const;
    unsigned int              getHumidite() const;
    unsigned int              getCO2() const;
    QString                   afficherNiveauICONE() const;
    QString                   getTHI();
    bool                      getLumiere() const;
    bool                      getFenetre() const;
    bool                      getOccupation() const;
    void                      setNom(QString nom);
    void                      setSuperficie(unsigned int superficie);
    void                      setDescription(QString description);
    void                      setTemperature(unsigned int temperature);
    void                      setHumidite(unsigned int humidite);
    void                      setCO2(unsigned int co2);
    void                      setOccupation(bool occupation) const;
    void                      setLumiere(bool lumiere) const;
    void                      setFenetre(bool fenetre) const;
};

#endif // SALLE_H
