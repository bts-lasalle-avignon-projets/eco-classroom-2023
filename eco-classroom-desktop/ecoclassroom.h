/**
 * @file ecoclassroom.h
 * @brief Déclaration de la classe EcoClassroom
 */

#ifndef ECOCLASSROOM_H
#define ECOCLASSROOM_H

#include <QtWidgets>
#include <QMap>
#include "salle.h"

/**
 * @class EcoClassroom
 * @brief Classe permettant de faire l'IHM du projet Eco classroom
 * @details La GUI de l'application
 */
class EcoClassroom : public QMainWindow
{
    Q_OBJECT

    /**
     * @enum Fenetre
     * @brief Les différentes fenêtres de l'application
     */
    enum Fenetre
    {
        Accueil,
        NbFenetres
    };

    /**
     * @enum ColonneTableau
     * @brief Définit les différentes colonne du tableau
     */
    enum ColonneTableau
    {
        COLONNE_SALLE_NOM,               //!< Le nom de la salle
        COLONNE_SALLE_CONFORT_THERMIQUE, //!<
        COLONNE_SALLE_QUALITE_AIR,       //!<
        COLONNE_SALLE_FENETRES,          //!< L'état des fenétres
        COLONNE_SALLE_LUMIERES,          //!< L'état des lumières
        COLONNE_SALLE_OCCUPATION,        //!< L'état d'occupation
        NB_COLONNES_TABLEAU
    };

  public:
    EcoClassroom(QWidget* parent = nullptr);
    ~EcoClassroom();

  private:
    QStringList           nomColonnesTable; //!< Le nom des colonnes de la table
    QWidget*              gui;              //!< Le widget central
    QStackedWidget*       fenetres;         //!< Pile de fenêtres
    QTableWidget*         tableWidgetSalles; //!< Affichage sous forme de table
    int                   nbLignesSalles;    //!< Nombre de salles dans la table
    QMap<QString, Salle*> salles;            //!< Les salles

    void instancierWidgets();
    void initialiserTable();
    void initialiserGUI();
    void installerGestionEvenements();
    void chargerSalles();
    void afficherSalleTable(Salle salle);
    void effacerTableauSalles();
    void effacerSalles();

  public slots:
    void afficherFenetre(EcoClassroom::Fenetre fenetre);
    void afficherFenetreAcceuil();
    void selectionnerSalle(int ligne, int colonne);
};

#endif // ECOCLASSROOM_H
