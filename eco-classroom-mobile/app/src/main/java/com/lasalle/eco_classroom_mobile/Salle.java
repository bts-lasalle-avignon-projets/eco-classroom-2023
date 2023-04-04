package com.lasalle.eco_classroom_mobile;

/**
 * @class Salle
 * @brief Le concept de Salle
 */
public class Salle
{
    private String nom;
    private String description;
    private double superficie;

    /**
     * @brief Constructeur par défaut
     */
    public Salle()
    {
        this.nom         = ""; //!< le nom de la salle
        this.description = ""; //!< le type de salle
        this.superficie  = 0.0; //!< la superficie en m2
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
}