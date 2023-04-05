package com.lasalle.eco_classroom_mobile;

/**
 * @class Salle
 * @brief Le concept de Salle
 */
public class Salle
{
    private String  nom;              //!< le nom de la salle
    private String  description;      //!< le type de salle
    private double  superficie;       //!< la superficie en m2
    private int     qualiteAir;       //!< la qualité de l'air de la salle
    private int     confortThermique; //!< le confort de la salle
    private boolean etatFenetre;      //!< l'état des fenêtres de la salle
    private boolean etatLumiere;      //!< l'état des lumières de la salle
    private boolean estOccupe;        //!<

    /**
     * @brief Constructeur par défaut
     */
    public Salle()
    {
        this.nom              = "";
        this.description      = "";
        this.superficie       = 0.0;
        this.qualiteAir       = -1;
        this.confortThermique = 100;
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