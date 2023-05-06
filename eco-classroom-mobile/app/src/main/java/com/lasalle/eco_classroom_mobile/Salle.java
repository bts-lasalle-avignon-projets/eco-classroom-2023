/**
 * @file Salle.java
 * @brief Le concept de Salle
 * @author Mercklen Jérémy
 */

package com.lasalle.eco_classroom_mobile;

import android.util.Log;

/**
 * @class Salle
 * @brief Le concept de Salle
 */
public class Salle
{
    /**
     * Constantes
     */
    private static final String TAG               = "_Salle_"; //!< TAG pour les logs (cf. Logcat)
    public static final int     TAUX_HUMIDITE_MIN = 0;         // !< le taux d'humidité minimum
    public static final int     TAUX_HUMIDITE_MAX = 100;       // !< le taux d'humidité maximum
    public static final int     CONCENTRATION_CO2_MIN = 0;     // !< la concentration minimum de CO2
    public static final int INDICE_QUALITE_AIR_MIN = 1; //!< l'indice de qualité de l'air minimum
    public static final int INDICE_QUALITE_AIR_MAX = 6; //!< l'indice de qualité de l'air maximum
    public static final int INDICE_CONFORT_THERMIQUE_MIN =
      -3; //!< l'indice de confort thermique minimum
    public static final int INDICE_CONFORT_THERMIQUE_MAX =
      3; //!< l'indice de confort thermique maximum
    public static final double SUPERFICIE_PAR_DEFAUT  = 0.0; //!< la superficie par défaut en m²
    public static final double TEMPERATURE_PAR_DEFAUT = 0.0; //!< la temperature par défaut en °C
    public static final int    HUMIDITE_PAR_DEFAUT    = 0;   //!< le taux d'humidité par défaut
    public static final int    CO2_PAR_DEFAUT         = 0;   //!< le CO2 par défaut en ppm
    public static final int    QUALITE_AIR_PAR_DEFAUT = 0;   //!< la qualité de l'air par défaut
    public static final int CONFORT_THERMIQUE_PAR_DEFAUT = -4; //!< le confort thermique par défaut

    /**
     * Attributs
     */
    private String  nom;              //!< le nom
    private String  description;      //!< le type
    private double  superficie;       //!< la superficie en m²
    private double  temperature;      //!< la température en °C
    private int     humidite;         //!< le taux d'humidité
    private int     co2;              //!< le CO2 en ppm
    private int     qualiteAir;       //!< la qualité de l'air
    private int     confortThermique; //!< l'indice de confort thermique
    private boolean etatFenetre;      //!< l'état des fenêtres (ouvertes/fermées)
    private boolean etatLumiere;      //!< l'état des lumières (allumées/éteintes)
    private boolean estOccupe;        //!< indique l'occupation (oui/non)
    private Seuils  seuils;           //!< les seuils pour cette salle

    /**
     * @brief Constructeur par défaut
     */
    public Salle()
    {
        this.nom              = "";
        this.description      = "";
        this.superficie       = 0.0;
        this.temperature      = 0.0;
        this.humidite         = 0;
        this.co2              = 0;
        this.qualiteAir       = 0;
        this.confortThermique = -4;
        this.etatFenetre      = false;
        this.etatLumiere      = false;
        this.estOccupe        = false;
        this.seuils           = new Seuils();
    }

    /**
     * @brief Constructeur d'initialisation
     * @param nom Le nom de la salle
     * @param superficie La superficie de la salle en m²
     * @param description Le type de salle
     */
    public Salle(String nom, double superficie, String description)
    {
        Log.d(TAG, "Salle(" + nom + ", " + superficie + ", " + description + ")");
        this.nom              = nom;
        this.description      = description;
        this.superficie       = superficie;
        this.temperature      = 0.0;
        this.humidite         = 0;
        this.co2              = 0;
        this.qualiteAir       = 0;
        this.confortThermique = -4;
        this.etatFenetre      = false;
        this.etatLumiere      = false;
        this.estOccupe        = false;
        this.seuils           = new Seuils();
    }

    /**
     * @brief Constructeur d'initialisation
     * @param nom Le nom de la salle
     * @param superficie La superficie de la salle en m²
     * @param description Le type de salle
     * @param seuils Indique les seuils à ne pas dépasser pour cette salle
     */
    public Salle(String nom, double superficie, String description, Seuils seuils)
    {
        Log.d(TAG, "Salle(" + nom + ", " + superficie + ", " + description + ")");
        this.nom              = nom;
        this.description      = description;
        this.superficie       = superficie;
        this.temperature      = 0.0;
        this.humidite         = 0;
        this.co2              = 0;
        this.qualiteAir       = 0;
        this.confortThermique = -4;
        this.etatFenetre      = false;
        this.etatLumiere      = false;
        this.estOccupe        = false;
        this.seuils           = seuils;
    }

    /**
     * @brief Accesseur de l'attribut nom
     * @return String Le nom de la salle
     */
    public String getNom()
    {
        return this.nom;
    }

    /**
     * @brief Accesseur de l'attribut description
     * @return String Le type de salle
     */
    public String getDescription()
    {
        return this.description;
    }

    /**
     * @brief Accesseur de l'attribut superficie
     * @return double La superficie de la salle en m²
     */
    public double getSuperficie()
    {
        return this.superficie;
    }

    /**
     * @brief Accesseur de l'attribut temperature
     * @return double La température de la salle en °C
     */
    public double getTemperature()
    {
        return this.temperature;
    }

    /**
     * @brief Accesseur de l'attribut humidite
     * @return int Le taux d'humidité
     */
    public int getHumidite()
    {
        return this.humidite;
    }

    /**
     * @brief Accesseur de l'attribut co2
     * @return int Le CO2 en ppm
     */
    public int getCo2()
    {
        return this.co2;
    }

    /**
     * @brief Accesseur de l'attribut qualiteAir
     * @return int La qualité de l'air
     */
    public int getQualiteAir()
    {
        return this.qualiteAir;
    }

    /**
     * @brief Accesseur de l'attribut confortThermique
     * @return int Le confort thermique
     */
    public int getConfortThermique()
    {
        return this.confortThermique;
    }

    /**
     * @brief Accesseur de l'attribut etatFenetre
     * @return boolean L'état des fenêtres (ouvertes/fermées)
     */
    public boolean getEtatFenetre()
    {
        return this.etatFenetre;
    }

    /**
     * @brief Accesseur de l'attribut etatLumiere
     * @return boolean L'état de la lumières (allumées/éteintes)
     */
    public boolean getEtatLumiere()
    {
        return this.etatLumiere;
    }

    /**
     * @brief Accesseur de l'attribut estOccupe
     * @return boolean Indique l'occupation (oui/non)
     */
    public boolean getEstOccupe()
    {
        return this.estOccupe;
    }

    /**
     * @brief Accesseur de l'attribut seuils
     * @return Seuils Les seuils à ne pas dépasser dans la salle
     */
    public Seuils getSeuils()
    {
        return this.seuils;
    }

    /**
     * @brief Mutateur de l'attribut nom
     * @param nom Le nouveau nom
     */
    public void setNom(String nom)
    {
        this.nom = nom;
    }

    /**
     * @brief Mutateur de l'attribut description
     * @param description La nouvelle description
     */
    public void setDescription(String description)
    {
        this.description = description;
    }

    /**
     * @brief Mutateur de l'attribut superficie
     * @param superficie La nouvelle superficie en m²
     */
    public void setSuperficie(double superficie)
    {
        this.superficie = superficie;
    }

    /**
     * @brief Mutateur de l'attribut temperature
     * @param temperature La nouvelle température en °C
     */
    public void setTemperature(double temperature)
    {
        this.temperature = temperature;
    }

    /**
     * @brief Mutateur de l'attribut humidite
     * @param humidite Le nouveau taux d'humidité
     */
    public void setHumidite(int humidite)
    {
        if(humidite >= TAUX_HUMIDITE_MIN && humidite <= TAUX_HUMIDITE_MAX)
            this.humidite = humidite;
    }

    /**
     * @brief Mutateur de l'attribut co2
     * @param co2 Le nouveau CO2 en ppm
     */
    public void setCo2(int co2)
    {
        if(co2 <= CONCENTRATION_CO2_MIN)
            this.co2 = co2;
    }

    /**
     * @brief Mutateur de l'attribut qualiteAir
     * @param qualiteAir La nouvelle qualité de l'air
     */
    public void setQualiteAir(int qualiteAir)
    {
        if(qualiteAir >= INDICE_QUALITE_AIR_MIN && qualiteAir <= INDICE_QUALITE_AIR_MAX)
            this.qualiteAir = qualiteAir;
    }

    /**
     * @brief Mutateur de l'attribut confortThermique
     * @param confortThermique Le nouveau confort thermique
     */
    public void setConfortThermique(int confortThermique)
    {
        if(confortThermique >= INDICE_CONFORT_THERMIQUE_MIN &&
           confortThermique <= INDICE_CONFORT_THERMIQUE_MAX)
            this.confortThermique = confortThermique;
    }

    /**
     * @brief Mutateur de l'attribut etatFenetre
     * @param etatFenetre Le nouvel état des fenêtres (ouvertes/fermées)
     */
    public void setEtatFenetre(boolean etatFenetre)
    {
        this.etatFenetre = etatFenetre;
    }

    /**
     * @brief Mutateur de l'attribut etatLumiere
     * @param etatLumiere Le nouvel état des lumières (allumées/éteintes)
     */
    public void setEtatLumiere(boolean etatLumiere)
    {
        this.etatLumiere = etatLumiere;
    }

    /**
     * @brief Mutateur de l'attribut estOccupe
     * @param estOccupe Le nouvel état d'occupation (oui/non)
     */
    public void setEstOccupe(Boolean estOccupe)
    {
        this.estOccupe = estOccupe;
    }

    /**
     * @brief Mutateur de l'attribut seuils
     * @param seuils Les nouveaux seuils à ne pas dépasser
     */
    public void setSeuils(Seuils seuils)
    {
        this.seuils = seuils;
    }

    /**
     * @brief Méthode permettant de verifier si le seuil de temperature de la salle est dépassé
     * @return boolean le seuil de température est dépassé (oui/non)
     */
    public boolean estSeuilTemperatureDepasse()
    {
        if(getTemperature() < getSeuils().getTemperatureMin() ||
           getTemperature() > getSeuils().getTemperatureMax())
            return true;
        return false;
    }

    /**
     * @brief Méthode permettant de verifier si le seuil d'humidité de la salle est dépassé
     * @return boolean le seuil d'humidité est dépassé (oui/non)
     */
    public boolean estSeuilHumiditeDepasse()
    {
        if(getHumidite() < getSeuils().getHumiditeMin() ||
           getHumidite() > getSeuils().getHumiditeMax())
            return true;
        return false;
    }

    /**
     * @brief Méthode permettant de verifier si le seuil de CO2 de la salle est dépassé
     * @return boolean le seuil de CO2 est dépassé (oui/non)
     */
    public boolean estSeuilCo2Depasse()
    {
        if(getCo2() >= getSeuils().getCo2Max())
            return true;
        return false;
    }
}