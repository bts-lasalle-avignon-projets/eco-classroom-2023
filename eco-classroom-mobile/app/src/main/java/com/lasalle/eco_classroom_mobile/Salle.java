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

    /**
     * Attributs
     */
    private String  nom;              //!< le nom
    private String  description;      //!< le type
    private double  superficie;       //!< la superficie en m²
    private double  temperature;      //!< la température en °C
    private int     humidite;         //!< le taux d'humidité
    private int     co2;              //!< le taux de co2 en ppm
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
     */
    public String getNom()
    {
        return this.nom;
    }

    /**
     * @brief Accesseur de l'attribut description
     */
    public String getDescription()
    {
        return this.description;
    }

    /**
     * @brief Accesseur de l'attribut superficie
     */
    public double getSuperficie()
    {
        return this.superficie;
    }

    /**
     * @brief Accesseur de l'attribut temperature
     */
    public double getTemperature()
    {
        return this.temperature;
    }

    /**
     * @brief Accesseur de l'attribut humidite
     */
    public int getHumidite()
    {
        return this.humidite;
    }

    /**
     * @brief Accesseur de l'attribut co2
     */
    public int getCo2()
    {
        return this.co2;
    }

    /**
     * @brief Accesseur de l'attribut qualiteAir
     */
    public int getQualiteAir()
    {
        return this.qualiteAir;
    }

    /**
     * @brief Accesseur de l'attribut confortThermique
     */
    public int getConfortThermique()
    {
        return this.confortThermique;
    }

    /**
     * @brief Accesseur de l'attribut etatFenetre
     */
    public boolean getEtatFenetre()
    {
        return this.etatFenetre;
    }

    /**
     * @brief Accesseur de l'attribut etatLumiere
     */
    public boolean getEtatLumiere()
    {
        return this.etatLumiere;
    }

    /**
     * @brief Accesseur de l'attribut estOccupe
     */
    public boolean getEstOccupe()
    {
        return this.estOccupe;
    }

    /**
     * @brief Accesseur de l'attribut seuils
     */
    public Seuils getSeuils()
    {
        return this.seuils;
    }

    /**
     * @brief Mutateur de l'attribut nom
     */
    public void setNom(String nom)
    {
        this.nom = nom;
    }

    /**
     * @brief Mutateur de l'attribut description
     */
    public void setDescription(String description)
    {
        this.description = description;
    }

    /**
     * @brief Mutateur de l'attribut superficie
     */
    public void setSuperficie(double superficie)
    {
        this.superficie = superficie;
    }

    /**
     * @brief Mutateur de l'attribut superficie
     */
    public void setTemperature(double temperature)
    {
        this.temperature = temperature;
    }

    /**
     * @brief Mutateur de l'attribut humidite
     */
    public void setHumidite(int humidite)
    {
        if(humidite >= TAUX_HUMIDITE_MIN && humidite <= TAUX_HUMIDITE_MAX)
            this.humidite = humidite;
    }

    /**
     * @brief Mutateur de l'attribut co2
     */
    public void setCo2(int co2)
    {
        if(co2 <= CONCENTRATION_CO2_MIN)
            this.co2 = co2;
    }

    /**
     * @brief Mutateur de l'attribut qualiteAir
     */
    public void setQualiteAir(int qualiteAir)
    {
        if(qualiteAir >= INDICE_QUALITE_AIR_MIN && qualiteAir <= INDICE_QUALITE_AIR_MAX)
            this.qualiteAir = qualiteAir;
    }

    /**
     * @brief Mutateur de l'attribut confortThermique
     */
    public void setConfortThermique(int confortThermique)
    {
        if(confortThermique >= INDICE_CONFORT_THERMIQUE_MIN &&
           confortThermique <= INDICE_CONFORT_THERMIQUE_MAX)
            this.confortThermique = confortThermique;
    }

    /**
     * @brief Mutateur de l'attribut etatFenetre
     */
    public void setEtatFenetre(boolean etatFenetre)
    {
        this.etatFenetre = etatFenetre;
    }

    /**
     * @brief Mutateur de l'attribut etatLumiere
     */
    public void setEtatLumiere(boolean etatLumiere)
    {
        this.etatLumiere = etatLumiere;
    }

    /**
     * @brief Mutateur de l'attribut estOccupe
     */
    public void setEstOccupe(Boolean estOccupe)
    {
        this.estOccupe = estOccupe;
    }
}