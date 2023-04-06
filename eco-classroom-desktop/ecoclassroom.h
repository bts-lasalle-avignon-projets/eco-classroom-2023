/**
 * @file ecoclassroom.h
 * @brief Déclaration de la classe EcoClassroom
 */

#ifndef ECOCLASSROOM_H
#define ECOCLASSROOM_H

#include <QtWidgets>
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

  public:
    EcoClassroom(QWidget* parent = nullptr);
    ~EcoClassroom();
    void afficherSalleTable(Salle salle);

  private:
    QStringList     nomColonnesTable;  //!< Le nom des colonnes de la table
    QWidget*        gui;               //!< Le widget central
    QStackedWidget* fenetres;          //!< Pile de fenêtres
    QTableWidget*   tableWidgetSalles; //!< Affichage sous forme de table
    int             nbLignesSalles;    //!< Nombre de salles dans la table
    QList<Salle>    salles;            //!< Les salles

    void instancierWidgets();
    void initialiserTable();
    void initialiserGUI();
    void chargerSalles();
    void effacerTableau(int ligne, int colonne);
    void effacerTableSalles();

  public slots:
    void afficherFenetre(EcoClassroom::Fenetre fenetre);
    void afficherFenetreAcceuil();
};

#endif // ECOCLASSROOM_H
