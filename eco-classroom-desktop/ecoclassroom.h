/**
 * @file ecoclassroom.h
 * @brief Déclaration de la classe EcoClassroom
 */

#ifndef ECOCLASSROOM_H
#define ECOCLASSROOM_H

#include <QtWidgets>
#include <QMap>

/**
 * @def DUREE_NOTIFICATION
 * @brief constante qui permet d'identifier la durée d'une notification système
 * qui s'affiche à l'écran
 */
#define DUREE_NOTIFICATION 5000 // en ms

/**
 * @def TITRE_NOTIFICATION_CO2
 * @brief Le titre de la notification système qui s'affiche à l'écran
 */
#define TITRE_NOTIFICATION_CO2 "ALERTE CO2 !"

class Salle;

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
        InformationSalle,
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
    int                   nbLignesSalles;   //!< Nombre de salles dans la table
    QMap<QString, Salle*> salles;           //!< Les salles
    QStringList           nomColonnesTable; //!< Le nom des colonnes de la table
    // Widgets
    QWidget*          gui;               //!< Le widget central
    QStackedWidget*   fenetres;          //!< Pile de fenêtres
    QTableWidget*     tableWidgetSalles; //!< Affichage sous forme de table
    QTableWidgetItem *elementNom, *elementTHI,
      *elementCO2; //!< Les élements d'une ligne de la table
    QLabel *elementLumiere, *elementFenetre,
      *elementOccupation;       //!< Les élements d'une ligne de la table
    QLabel*      labelNomSalle; //!< Le label pour le nom de la salle
    QLabel*      nomSalle;      //!< Le nom de salle
    QLabel*      labelSuperficieSalle;  //!< Le label pour le nom de la salle
    QLabel*      superficieSalle;       //!< La superficie de la salle
    QLabel*      labelDescriptionSalle; //!< Le label pour le nom de la salle
    QLabel*      descriptionSalle;      //!< La description de la salle
    QPushButton* boutonRetourAccueil;   //!< Bouton de retour
    QSystemTrayIcon*
      notificationEcoClassroom; //!< Notification système du confinement

    void instancierWidgets();
    void initialiserTable();
    void initialiserFenetreInformations();
    void initialiserGUI();
    void installerGestionEvenements();
    void chargerSalles();
    void creerElementsTexteCellule(const Salle& salle);
    void creerElementsImageCellule(const Salle& salle);
    void personnaliserElementsTexte();
    void personnaliserElementsImage();
    void insererElementsCellule();
    void redimensionnerHauteurTable();
    void afficherSalleTable(const Salle& salle);
    void afficherInformationsSalle(const Salle& salle);
    void effacerTableauSalles();
    void effacerSalles();
    void alerterDepassementSeuilCO2(const Salle& salle);
    void notifierSignalementConfinement(const QString& titre,
                                        const QString& message);

    // Pour le QTableWidget
    void coloriserFondCellule(QTableWidgetItem* cellule, const QColor& couleur);
    void coloriserFondCellule(QTableWidgetItem* cellule,
                              const QString&    couleur);
    void coloriserFondCellule(QTableWidget* tableWidgetSalles,
                              int           ligne,
                              int           colonne,
                              const QColor& couleur);
    void coloriserFondCellule(QTableWidget*  tableWidgetSalles,
                              int            ligne,
                              int            colonne,
                              const QString& couleur);

  public slots:
    void afficherFenetre(EcoClassroom::Fenetre fenetre);
    void afficherFenetreAcceuil();
    void afficherFenetreInformations();
    void selectionnerSalle(int ligne, int colonne);
};

#endif // ECOCLASSROOM_H
