/**
 * @file ecoclassroom.cpp
 * @brief Définition de la classe EcoClassroom
 */

#include "ecoclassroom.h"
#include "salle.h"

/**
 * @fn EcoClassroom::EcoClassroom
 * @brief Constructeur de la classe EcoClassroom
 * @param parent nullptr pour en faire la fenêtre principale de l'application
 */
EcoClassroom::EcoClassroom(QWidget* parent) : QMainWindow(parent)
{
    qDebug() << Q_FUNC_INFO;
    instancierWidgets();
    initialiserGUI();

    chargerSalles();
}

/**
 * @fn EcoClassroom::~EcoClassroom
 * @brief Destructeur de la classe EcoClassroom
 * @details Libère les ressources de l'application
 */
EcoClassroom::~EcoClassroom()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @fn EcoClassroom::instancierWidgets
 * @brief Instancie les différents widgets de l'application
 */
void EcoClassroom::instancierWidgets()
{
    // Le widget principal
    gui = new QWidget(this);
    // La pile de fenêtres
    fenetres                = new QStackedWidget(this);
    QWidget* fenetreAccueil = new QWidget(this);
    fenetres->addWidget(fenetreAccueil);

    // La table
    initialiserTable();

    // Les layouts
    QVBoxLayout* layoutPrincipal   = new QVBoxLayout();
    QVBoxLayout* layoutF1Principal = new QVBoxLayout();
    QHBoxLayout* layoutF1Table     = new QHBoxLayout();

    // Positionnement
    // La fenêtre accueil
    layoutF1Table->addWidget(tableWidgetSalles);
    layoutF1Principal->addLayout(layoutF1Table);
    layoutF1Principal->addStretch();
    fenetreAccueil->setLayout(layoutF1Principal);

    // La GUI
    layoutPrincipal->addWidget(fenetres);
    gui->setLayout(layoutPrincipal);
    setCentralWidget(gui);
}

/**
 * @fn EcoClassroom::initialiserTable
 * @brief Initialise le QTableWidget qui permet l'affichage de l'état des salles
 */
void EcoClassroom::initialiserTable()
{
    tableWidgetSalles = new QTableWidget(this);

    // Les colonnes
    nomColonnesTable << "Salle"
                     << "Confort thermique"
                     << "Qualité air"
                     << "Lumières"
                     << "Présence"
                     << "État fenêtres";
    tableWidgetSalles->setColumnCount(nomColonnesTable.count());
    tableWidgetSalles->setHorizontalHeaderLabels(nomColonnesTable);
    // Vide (pas de lignes donc pas d'utilisateurs dans la table)
    tableWidgetSalles->setRowCount(0);
    // Redimensionnement automatique (inutile)
    // tableWidgetSalles->resizeColumnsToContents();
    // Pas d'étiquettes numérotées sur le côté gauche
    tableWidgetSalles->verticalHeader()->setHidden(true);
    // Taille
    // tableWidgetSalles->setMinimumSize(QSize(0, 0));
    // Prend toute la largeur
    tableWidgetSalles->setMinimumWidth(gui->width());
    // Hauteur fixe ?
    // tableWidgetSalles->setMinimumHeight(gui->height());
    /*cf. setFixedSize()*/
    tableWidgetSalles->setFixedHeight(
      tableWidgetSalles->verticalHeader()->length() +
      tableWidgetSalles->horizontalHeader()->height());
    // Largeur automatique des colonnes sur toute la largeur
    QHeaderView* headerView = tableWidgetSalles->horizontalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);
    // Pas de scroll
    tableWidgetSalles->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableWidgetSalles->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

/**
 * @fn EcoClassroom::initialiserGUI
 * @brief Initialise et affiche la GUI
 */
void EcoClassroom::initialiserGUI()
{
    setFixedSize(qApp->desktop()->availableGeometry(this).width(),
                 qApp->desktop()->availableGeometry(this).height());
    // showMaximized();
    afficherFenetreAcceuil();
}

/**
 * @fn EcoClassroom::afficherFenetre(EcoClassroom::Fenetre fenetre)
 * @brief Selectionne la fenêtre à afficher
 */
void EcoClassroom::afficherFenetre(EcoClassroom::Fenetre fenetre)
{
    fenetres->setCurrentIndex(fenetre);
}

/**
 * @fn EcoClassroom::afficherFenetreAcceuil
 * @brief Affiche la fenêtre d'accueil
 */
void EcoClassroom::afficherFenetreAcceuil()
{
    afficherFenetre(EcoClassroom::Fenetre::Accueil);
}

void EcoClassroom::chargerSalles()
{
    qDebug() << Q_FUNC_INFO;
    salles.clear();

    // Exemple simple (si pas de base de données)
    salles.push_back(Salle("B11", 18, "Salle de cours"));
    salles.push_back(Salle("B20", 65, "Salle de TP"));
    salles.push_back(Salle("B21", 35, "Salle de Physiques"));
    // Exemple avec une base de données SQLite
    /*
    QVector<QStringList> sallesBDD;
    QString requete = "SELECT * FROM Salle";
    bool    retour;

    retour = baseDeDonnees->recuperer(requete, sallesBDD);
    if(retour)
    {
        qDebug() << Q_FUNC_INFO << sallesBDD;
        for(int i = 0; i < sallesBDD.size(); ++i)
            qDebug() << Q_FUNC_INFO << sallesBDD[i];
    }
    else
    {
        QMessageBox::critical(0, "Erreur BDD", "Aucune salle chargée !");
    }*/

    effacerTableSalles();

    qDebug() << Q_FUNC_INFO << "Nb salles" << salles.size();
    for(int i = 0; i < salles.size(); ++i)
    {
        afficherSalleTable(salles.at(i));
    }
}

void EcoClassroom::effacerTableau(int ligne, int colonne)
{
    Q_UNUSED(ligne)
    Q_UNUSED(colonne)
    // on réinitialise la table
    int nb = tableWidgetSalles->rowCount();
    if(nb != 0)
    {
        // on les efface
        for(int n = 0; n < nb; n++)
            tableWidgetSalles->removeRow(0);
    }
}

void EcoClassroom::effacerTableSalles()
{
    qDebug() << Q_FUNC_INFO;

    effacerTableau(0, 0);
    nbLignesSalles = 0;
}

void EcoClassroom::afficherSalleTable(Salle salle)
{
    qDebug() << Q_FUNC_INFO << "nom" << salle.getNom() << "temperature"
             << salle.getTemperature() << "humidite" << salle.getHumidite()
             << "CO2" << salle.getCO2() << "lumiere" << salle.getLumiere()
             << "fenetre" << salle.getFenetre() << "occupation"
             << salle.getOccupation();
}

/**
 * @fn EcoClassroom::signalerConfinement(const Salle& salle)
 * @brief Signale le confinement d'une salle
 */

void EcoClassroom::signalerConfinement(const Salle& salle)
{
    qInfo() << "La Salle : " << salle.getNom() << " est confinée !";
}
