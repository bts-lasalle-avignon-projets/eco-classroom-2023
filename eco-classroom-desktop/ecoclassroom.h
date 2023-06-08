/**
 * @file ecoclassroom.h
 * @brief Déclaration de la classe EcoClassroom
 */

#ifndef ECOCLASSROOM_H
#define ECOCLASSROOM_H

#include <QtWidgets>
#include <QMap>
#include <QtMqtt/QMqttTopicName>

class CommunicationMQTT;
class BaseDeDonnees;

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

/**
 * @def SIMULATION_CO2
 * @brief Pour simuler des mesures de CO2
 */
//#define SIMULATION_CO2

/**
 * @def AVEC_BDD
 * @brief Pour utiliser les données qui sont dans la Base de données
 */
#define AVEC_BDD

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
        COLONNE_SALLE_CONFORT_THERMIQUE, //!< Le confort thermique
        COLONNE_SALLE_QUALITE_AIR,       //!< La qualité de l'air
        COLONNE_SALLE_ICONE,             //!< Le confinement
        COLONNE_SALLE_FENETRES,          //!< L'état des fenétres
        COLONNE_SALLE_LUMIERES,          //!< L'état des lumières
        COLONNE_SALLE_OCCUPATION,        //!< L'état d'occupation
        NB_COLONNES_TABLEAU
    };

  public:
    EcoClassroom(QWidget* parent = nullptr);
    ~EcoClassroom();

  private:
    int                   nbLignesSalles; //!< Nombre de salles dans la table
    QMap<QString, Salle*> salles;         //!< Les salles
    CommunicationMQTT*
      communicationMQTT;          //!< Relation entre la classe EcoClassroom et
                                  //!< CommunicationMQTT (association)
    BaseDeDonnees* baseDeDonnees; //!< Base de données
    QStringList    nomColonnesTable; //!< Le nom des colonnes de la table
    // Widgets
    QWidget*          gui;               //!< Le widget central
    QStackedWidget*   fenetres;          //!< Pile de fenêtres
    QTableWidget*     tableWidgetSalles; //!< Affichage sous forme de table
    QTableWidgetItem *elementNom, *elementTHI, *elementCO2,
      *elementICONE; //!< Les élements d'une ligne de la table
    QLabel *elementLumiere, *elementFenetre,
      *elementOccupation;          //!< Les élements d'une ligne de la table
    QLabel* labelNomSalle;         //!< Le label pour le nom de la salle
    QLabel* nomSalle;              //!< Le nom de salle
    QLabel* labelSuperficieSalle;  //!< Le label pour le nom de la salle
    QLabel* superficieSalle;       //!< La superficie de la salle
    QLabel* labelDescriptionSalle; //!< Le label pour le nom de la salle
    QLabel* descriptionSalle;      //!< La description de la salle
    QLabel* labelIndiceICONE;      //!< le label pour l'indice ICONE
    QLabel* indiceICONE; //!< l'indice ICONE (confinement d'une salle due à
                         //!< l'excès de co2)
    QPushButton* boutonRetourAccueil;        //!< Bouton de retour
    QLabel*      labelIndiceQualiteAirSalle; //!< Le label pour l'indice de la
                                             //!< qualité d'air
    QLabel* indiceQualiteAirSalle; //!< L'indice de la qualité de l'air
    QSystemTrayIcon*
      notificationEcoClassroom; //!< Notification système du confinement

    void instancierWidgets();
    void initialiserTable();
    void initialiserFenetreInformations();
    void initialiserGUI();
    void installerGestionEvenements();
    void chargerSalles();
#ifdef SIMULATION_CO2
    void simulerMesureCO2();
#endif
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
    void enregistrerICONEDansBDD(Salle* salle);
    void enregistrerQualiteAirDansBDD(Salle* salle);

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
    void recevoirMessageMQTT(const QByteArray&     message,
                             const QMqttTopicName& topic);
    void traiterNouveauMessageMQTT(QString salle,
                                   QString module,
                                   QString typeDonnee,
                                   QString message);
};

#endif // ECOCLASSROOM_H
