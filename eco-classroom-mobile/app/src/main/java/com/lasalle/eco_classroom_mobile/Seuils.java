/**
 * @file Salle.java
 * @brief Le concept de Salle
 * @author Mercklen Jérémy
 */

package com.lasalle.eco_classroom_mobile;

import android.util.Log;

/**
 * @class Seuils
 * @brief Les Seuils pour une Salle
 */
public class Seuils
{
    /**
     * Constantes
     */
    private static final String TAG = "_Seuils_"; //!< TAG pour les logs (cf. Logcat)
    // Les seuils par défaut
    public static final int TEMPERATURE_MIN    = 14;   // !< la température minimum
    public static final int TEMPERATURE_MAX    = 30;   // !< la température maximum
    public static final int LUMINOSITE_MIN     = 300;  // !< la luminosité minimum
    public static final int ECLAIREMENT_MOYEN  = 500;  // !< l'éclairement moyen
    public static final int HUMIDITE_MIN       = 45;   // !< le taux d'humidité minimum
    public static final int HUMIDITE_MAX       = 55;   // !< le taux d'humidité maximum
    public static final int CO2_MAX            = 1300; // !< la concentration maximum de CO2
    public static final int INDICE_CONFINEMENT = 5;    // !< l'indice quand il faut confiner

    /**
     * Attributs
     */
    private double temperatureMin;    //<! le seuil de température minimum
    private double temperatureMax;    //<! le seuil de température maximum
    private int    luminositeMin;     //<! le seuil de luminosité minimum
    private int    eclairementMoyen;  //<! l'éclairement moyen
    private int    humiditeMin;       //<! le seuil d'humidité minimum
    private int    humiditeMax;       //<! le seuil d'humidité maximum
    private int    co2Max;            //<! le seuil de CO2 maximum
    private int    indiceConfinement; //<! l'indice de confinement

    /**
     * @brief Constructeur par défaut
     */
    public Seuils()
    {
        this.temperatureMin    = TEMPERATURE_MIN;
        this.temperatureMax    = TEMPERATURE_MAX;
        this.luminositeMin     = LUMINOSITE_MIN;
        this.eclairementMoyen  = ECLAIREMENT_MOYEN;
        this.humiditeMin       = HUMIDITE_MIN;
        this.humiditeMax       = HUMIDITE_MAX;
        this.co2Max            = CO2_MAX;
        this.indiceConfinement = INDICE_CONFINEMENT;
    }

    /**
     * @brief Constructeur d'initialisation
     */
    public Seuils(double temperatureMin,
                  double temperatureMax,
                  int    luminositeMin,
                  int    eclairementMoyen,
                  int    humiditeMin,
                  int    humiditeMax,
                  int    co2Max,
                  int    indiceConfinement)
    {
        Log.d(TAG,
              "Seuils(" + temperatureMin + ", " + temperatureMax + ", " + luminositeMin + ", " +
                eclairementMoyen + ", " + humiditeMin + ", " + humiditeMax + ", " + co2Max + ", " +
                indiceConfinement + ")");
        this.temperatureMin    = temperatureMin;
        this.temperatureMax    = temperatureMax;
        this.luminositeMin     = luminositeMin;
        this.eclairementMoyen  = eclairementMoyen;
        this.humiditeMin       = humiditeMin;
        this.humiditeMax       = humiditeMax;
        this.co2Max            = co2Max;
        this.indiceConfinement = indiceConfinement;
    }

    /**
     * @brief Accesseur de l'attribut temperatureMin
     * @return double La température minimum
     */
    public double getTemperatureMin()
    {
        return temperatureMin;
    }

    /**
     * @brief Accesseur de l'attribut temperatureMax
     * @return double La température maximum
     */
    public double getTemperatureMax()
    {
        return temperatureMax;
    }

    /**
     * @brief Accesseur de l'attribut luminositeMin
     * @return double La luminosité minimum
     */
    public int getLuminositeMin()
    {
        return luminositeMin;
    }

    /**
     * @brief Accesseur de l'attribut eclairementMoyen
     * @return double L'éclairement moyen
     */
    public int getEclairementMoyen()
    {
        return eclairementMoyen;
    }

    /**
     * @brief Accesseur de l'attribut humiditeMin
     * @return double L'humidité minimum
     */
    public int getHumiditeMin()
    {
        return humiditeMin;
    }

    /**
     * @brief Accesseur de l'attribut humiditéMax
     * @return double L'humidité maximum
     */
    public int getHumiditeMax()
    {
        return humiditeMax;
    }

    /**
     * @brief Accesseur de l'attribut co2Max
     * @return int Le CO2 maximum
     */
    public int getCo2Max()
    {
        return co2Max;
    }

    /**
     * @brief Accesseur de l'attribut indiceConfinement
     * @return int L'indice de confinement
     */
    public int getIndiceConfinement()
    {
        return indiceConfinement;
    }
}
