#ifndef ECOCLASSROOM_H
#define ECOCLASSROOM_H
#include "salle.h"

/**
 * @file ecoclassroom.h
 * @brief Déclaration de la classe EcoClassroom
 */

#include <QtWidgets>

/**
 * @class EcoClassroom
 * @brief Déclaration de la classe EcoClassroom
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
    void afficherSallesTable(QStringList salle);
    void afficherUneSalle();
    void afficherMesures();
    void afficherEtats();
    void afficherTHI();
    void afficherIADI();
    void afficherICONE();
    void filtrerSalles();
    void afficherDetailsSalles();
    void afficherGraphiques();

  private:
    QStringList     nomColonnesTable;  //!< Le nom des colonnes de la table
    QWidget*        gui;               //!< Le widget central
    QStackedWidget* fenetres;          //!< Pile de fenêtres
    QTableWidget*   tableWidgetSalles; //!< Affichage sous forme de table
    int             nbLignesSalles;
    QList<Salle>    salles;

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
