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
    installerGestionEvenements();
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

// Méthodes publiques

// Slots

/**
 * @fn EcoClassroom::afficherFenetre
 * @brief Selectionne la fenêtre à afficher
 * @param[in] fenetre la fenêtre à afficher
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

/**
 * @fn EcoClassroom::afficherFenetreInformations
 * @brief Affiche la fenêtre d'informations
 */
void EcoClassroom::afficherFenetreInformations()
{
    afficherFenetre(EcoClassroom::Fenetre::InformationSalle);
}

/**
 * @fn EcoClassroom::selectionnerSalle
 * @brief Sélectionne la salle à afficher
 * @param ligne le numéro de ligne dans le tableau
 * @param colonne le numéro de colonne dans le tableau (non utilisé)
 */
void EcoClassroom::selectionnerSalle(int ligne, int colonne)
{
    Q_UNUSED(colonne)
    QTableWidgetItem* salle;
    salle = tableWidgetSalles->item(ligne, COLONNE_SALLE_NOM);
    // qDebug() << Q_FUNC_INFO << salle->data(0).toString();
    qDebug() << Q_FUNC_INFO << "Salle"
             << salles[salle->data(0).toString()]->getNom();
    afficherInformationsSalle(*salles[salle->data(0).toString()]);
}

// Méthodes privées

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
    QWidget* fenetreInformations = new QWidget(this);
    fenetres->addWidget(fenetreInformations);

    initialiserTable();
    initialiserFenetreInformations();

    // Les layouts
    QVBoxLayout* layoutPrincipal      = new QVBoxLayout();
    QVBoxLayout* layoutF1Principal    = new QVBoxLayout();
    QHBoxLayout* layoutF1Table        = new QHBoxLayout();
    QVBoxLayout* layoutF2Principal    = new QVBoxLayout();
    QHBoxLayout* layoutF2Informations = new QHBoxLayout();
    QHBoxLayout* layoutF2Boutons      = new QHBoxLayout();

    // Positionnement
    // La fenêtre accueil
    layoutF1Table->addWidget(tableWidgetSalles);
    layoutF1Principal->addLayout(layoutF1Table);
    layoutF1Principal->addStretch();
    fenetreAccueil->setLayout(layoutF1Principal);
    // La fenêtre d'informations sur une salle
    layoutF2Informations->addWidget(labelNomSalle);
    layoutF2Informations->addWidget(nomSalle);
    layoutF2Informations->addStretch();
    layoutF2Boutons->addStretch();
    layoutF2Boutons->addWidget(boutonRetourAccueil);
    layoutF2Principal->addLayout(layoutF2Informations);
    layoutF2Principal->addLayout(layoutF2Boutons);
    layoutF2Principal->addStretch();
    fenetreInformations->setLayout(layoutF2Principal);

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
                     << "Occupée"
                     << "Fenêtres";
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
 * @fn EcoClassroom::initialiserFenetreInformations
 * @brief Initialise les widgets de la fenêtre Informations
 */
void EcoClassroom::initialiserFenetreInformations()
{
    labelNomSalle = new QLabel(this);
    labelNomSalle->setText("Nom :");
    nomSalle            = new QLabel(this);
    boutonRetourAccueil = new QPushButton("Ok", this);
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
 * @fn EcoClassroom::installerGestionEvenements
 * @brief Installe les gestionnaire d'évènements (signal/slot)
 */
void EcoClassroom::installerGestionEvenements()
{
    connect(tableWidgetSalles,
            SIGNAL(cellClicked(int, int)),
            this,
            SLOT(selectionnerSalle(int, int)));
    connect(boutonRetourAccueil,
            SIGNAL(clicked(bool)),
            this,
            SLOT(afficherFenetreAcceuil()));
}

/**
 * @fn EcoClassroom::chargerSalles
 * @brief Charger les salles
 */
void EcoClassroom::chargerSalles()
{
    qDebug() << Q_FUNC_INFO;
    salles.clear();

    // Pour les tests
    // Exemple simple (si pas de base de données)
    salles["B11"] = new Salle("B11", 18, "Salle de TD");
    salles["B20"] = new Salle("B20", 65, "Atelier");
    salles["B21"] = new Salle("B21", 35, "Salle de TP");
    salles["B22"] = new Salle("B22", 80, "Salle de cours");

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

    effacerSalles();

    qDebug() << Q_FUNC_INFO << "Nb salles" << salles.size();
    QMapIterator<QString, Salle*> salle(salles);
    while(salle.hasNext())
    {
        salle.next();
        qDebug() << Q_FUNC_INFO << "Salle" << salle.key();
        afficherSalleTable(*salle.value());
    }
}

/**
 * @fn EcoClassroom::afficherSalleTable
 * @brief Affiche une salle dans le tableau
 * @param salle La salle à afficher dans le tableau
 */
void EcoClassroom::afficherSalleTable(Salle salle)
{
    qDebug() << Q_FUNC_INFO << "nom" << salle.getNom() << "temperature"
             << salle.getTemperature() << "humidite" << salle.getHumidite()
             << "CO2" << salle.getCO2() << "lumiere" << salle.getLumiere()
             << "fenetre" << salle.getFenetre() << "occupation"
             << salle.getOccupation();

    // créer des élements de cellule
    QTableWidgetItem *elementNom, *elementTHI, *elementCO2;
    QLabel *          elementLumiere, *elementFenetre, *elementOccupation;

    elementNom     = new QTableWidgetItem(salle.getNom());
    elementTHI     = new QTableWidgetItem(QString("Inconnu"));
    elementCO2     = new QTableWidgetItem(QString::number(0));
    elementLumiere = new QLabel(this);
    if(salle.getLumiere())
        elementLumiere->setPixmap(QPixmap(":/images/led-rouge"));
    else
        elementLumiere->setPixmap(QPixmap(":/images/led-verte"));
    elementFenetre = new QLabel(this);
    if(salle.getFenetre())
        elementFenetre->setPixmap(QPixmap(":/images/led-rouge"));
    else
        elementFenetre->setPixmap(QPixmap(":/images/led-verte"));
    elementOccupation = new QLabel(this);
    if(salle.getOccupation())
        elementOccupation->setPixmap(QPixmap(":/images/led-rouge"));
    else
        elementOccupation->setPixmap(QPixmap(":/images/led-verte"));

    // personnaliser les éléments
    elementNom->setFlags(Qt::ItemIsEnabled);
    elementNom->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    elementTHI->setFlags(Qt::ItemIsEnabled);
    elementTHI->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    elementCO2->setFlags(Qt::ItemIsEnabled);
    elementCO2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    elementLumiere->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    elementFenetre->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    elementOccupation->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    // ajouter une ligne
    int nb = tableWidgetSalles->rowCount();
    ++nb;
    tableWidgetSalles->setRowCount(nb);

    // insérer les éléments de cellule
    tableWidgetSalles->setItem(nb - 1, COLONNE_SALLE_NOM, elementNom);
    tableWidgetSalles->setItem(nb - 1,
                               COLONNE_SALLE_CONFORT_THERMIQUE,
                               elementTHI);
    tableWidgetSalles->setItem(nb - 1, COLONNE_SALLE_QUALITE_AIR, elementCO2);
    tableWidgetSalles->setCellWidget(nb - 1,
                                     COLONNE_SALLE_LUMIERES,
                                     elementLumiere);
    tableWidgetSalles->setCellWidget(nb - 1,
                                     COLONNE_SALLE_FENETRES,
                                     elementFenetre);
    tableWidgetSalles->setCellWidget(nb - 1,
                                     COLONNE_SALLE_OCCUPATION,
                                     elementOccupation);

    // redimensionner la hauteur de la table
    tableWidgetSalles->setFixedHeight(
      tableWidgetSalles->verticalHeader()->length() +
      tableWidgetSalles->horizontalHeader()->height());
}

/**
 * @fn EcoClassroom::afficherInformationsSalle(const Salle& salle)
 * @brief Affiche les informations d'une salle
 */
void EcoClassroom::afficherInformationsSalle(const Salle& salle)
{
    qInfo() << " Nom : " << salle.getNom() << "\n"
            << "Superficie : " << salle.getSuperficie() << "\n"
            << "Description : " << salle.getDescription();
    nomSalle->setText(salle.getNom());
    afficherFenetreInformations();
}

/**
 * @fn EcoClassroom::effacerTableauSalles
 * @brief Effacer le tableau des salles
 */
void EcoClassroom::effacerTableauSalles()
{
    // on réinitialise la tableau
    int nb = tableWidgetSalles->rowCount();
    if(nb != 0)
    {
        // on les efface
        for(int n = 0; n < nb; n++)
            tableWidgetSalles->removeRow(0);
    }
}

/**
 * @fn EcoClassroom::effacerSalles
 * @brief Effacer les salles
 */
void EcoClassroom::effacerSalles()
{
    qDebug() << Q_FUNC_INFO;

    effacerTableauSalles();
    nbLignesSalles = 0;
}
