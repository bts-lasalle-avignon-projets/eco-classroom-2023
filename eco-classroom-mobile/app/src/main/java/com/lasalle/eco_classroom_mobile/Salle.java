package com.lasalle.eco_classroom_mobile;

/**
 * @class Salle
 * @brief Le concept de Salle
 */
public class Salle
{
    private String  nom;              //!< le nom
    private String  description;      //!< le type
    private double  superficie;       //!< la superficie en m2
    private int     qualiteAir;       //!< la qualité de l'air
    private int     confortThermique; //!< l'indice de confort thermique
    private boolean etatFenetre;      //!< l'état des fenêtres (ouvertes/fermées)
    private boolean etatLumiere;      //!< l'état des lumières (allumées/éteintes)
    private boolean estOccupe;        //!< indique l'occupation (oui/non)

    /**
     * @brief Constructeur par défaut
     */
    public Salle()
    {
        this.nom              = "";
        this.description      = "";
        this.superficie       = 0.0;
        this.qualiteAir       = 0;
        this.confortThermique = -4;
        this.etatFenetre      = false;
        this.etatLumiere      = false;
        this.estOccupe        = false;
    }

    /**
     * @brief Constructeur d'initialisation
     */
    public Salle(String nom, double superficie, String description)
    {
        this.nom         = nom;
        this.description = description;
        this.superficie  = superficie;
    }

    /**
     * @brief Accesseur de l'attribut nom
     */
    public String getNom()
    {
        return this.nom;
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
    public int getconfortThermique()
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
}