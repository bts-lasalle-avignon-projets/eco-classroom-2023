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
    if(salle == nullptr || salle->data(0).toString().isEmpty())
        return;
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
    QVBoxLayout* layoutPrincipal = new QVBoxLayout();
    // La fenêtre accueil
    QVBoxLayout* layoutF1Principal = new QVBoxLayout();
    QHBoxLayout* layoutF1Table     = new QHBoxLayout();
    // La fenêtre d'informations sur une salle
    QVBoxLayout* layoutF2Principal    = new QVBoxLayout();
    QGridLayout* layoutF2Informations = new QGridLayout();
    QHBoxLayout* layoutF2Boutons      = new QHBoxLayout();

    // Positionnement
    // La fenêtre accueil
    layoutF1Table->addWidget(tableWidgetSalles);
    layoutF1Principal->addLayout(layoutF1Table);
    layoutF1Principal->addStretch();
    fenetreAccueil->setLayout(layoutF1Principal);
    // La fenêtre d'informations sur une salle
    layoutF2Informations->addWidget(labelNomSalle, 0, 0);
    layoutF2Informations->addWidget(nomSalle, 0, 1);
    layoutF2Informations->addWidget(labelSuperficieSalle, 1, 0);
    layoutF2Informations->addWidget(superficieSalle, 1, 1);
    layoutF2Informations->addWidget(labelDescriptionSalle, 2, 0);
    layoutF2Informations->addWidget(descriptionSalle, 2, 1);
    layoutF2Informations->addWidget(labelIndiceQAirSalle, 3, 0);
    layoutF2Informations->addWidget(indiceQualiteAirSalle, 3, 1);
    layoutF2Informations->addWidget(labelIndiceICONE, 4, 0);
    layoutF2Informations->addWidget(indiceICONE, 4, 1);
    layoutF2Boutons->addStretch();
    layoutF2Boutons->addWidget(boutonRetourAccueil);
    layoutF2Principal->addLayout(layoutF2Informations);
    layoutF2Principal->addLayout(layoutF2Boutons);
    layoutF2Principal->addStretch();
    fenetreInformations->setLayout(layoutF2Principal);

    notificationEcoClassroom = new QSystemTrayIcon(this);
    notificationEcoClassroom->show();

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
                     << "Indice ICONE"
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
    // initialisation widgets dans la fênetre information
    labelNomSalle         = new QLabel(this);
    labelSuperficieSalle  = new QLabel(this);
    labelDescriptionSalle = new QLabel(this);
    labelIndiceQAirSalle  = new QLabel(this);
    labelIndiceICONE      = new QLabel(this);

    // affichage du widget
    labelNomSalle->setText("Nom :");
    nomSalle = new QLabel(this);

    labelSuperficieSalle->setText("Superficie :");
    superficieSalle = new QLabel(this);

    labelDescriptionSalle->setText("Description :");
    descriptionSalle = new QLabel(this);

    labelIndiceQAirSalle->setText("Indice Qualité de l'air :");
    indiceQualiteAirSalle = new QLabel(this);

    labelIndiceICONE->setText("Indice ICONE :");
    indiceICONE = new QLabel(this);

    // bouton pour quitter la fênetre
    boutonRetourAccueil = new QPushButton("Ok", this);
}

/**
 * @fn EcoClassroom::initialiserGUI
 * @brief Initialise et affiche la GUI
 */
void EcoClassroom::initialiserGUI()
{
    /*setFixedSize(qApp->desktop()->availableGeometry(this).width(),
                 qApp->desktop()->availableGeometry(this).height());*/
    showMaximized();
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
    // Tests CO2
    salles["B11"]->setCO2(605);
    salles["B20"]->setCO2(1259);
    salles["B21"]->setCO2(825);
    salles["B22"]->setCO2(1355);

    // Tests CO2 ICONE SIMULATION
    salles["B11"]->setCO2(905);
    salles["B11"]->setCO2(1705);
    salles["B11"]->setCO2(1605);
    salles["B11"]->setCO2(1005);
    salles["B11"]->setCO2(1605);
    salles["B11"]->setCO2(2005);

    salles["B11"]->getIndiceICONE();
    salles["B20"]->getIndiceICONE();
    salles["B21"]->getIndiceICONE();
    salles["B22"]->getIndiceICONE();
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
 * @fn EcoClassroom::creerElementsTexteCellule
 * @param salle
 */
void EcoClassroom::creerElementsTexteCellule(const Salle& salle)
{
    elementNom   = new QTableWidgetItem(salle.getNom());
    elementTHI   = new QTableWidgetItem(QString("Inconnu"));
    elementCO2   = new QTableWidgetItem(QString(salle.getQualiteAir()));
    elementICONE = new QTableWidgetItem(QString(salle.afficherNiveauICONE()));

    personnaliserElementsTexte();
}

/**
 * @brief EcoClassroom::creerElementsImageCellule
 * @param salle
 */
void EcoClassroom::creerElementsImageCellule(const Salle& salle)
{
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

    personnaliserElementsImage();
}

/**
 * @fn EcoClassroom::personnaliserElementsTexte
 */
void EcoClassroom::personnaliserElementsTexte()
{
    elementNom->setFlags(Qt::ItemIsEnabled);
    elementNom->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    elementTHI->setFlags(Qt::ItemIsEnabled);
    elementTHI->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    elementCO2->setFlags(Qt::ItemIsEnabled);
    elementCO2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    elementICONE->setFlags(Qt::ItemIsEnabled);
    elementICONE->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

/**
 * @fn personnaliserElementsImage
 */
void EcoClassroom::personnaliserElementsImage()
{
    elementLumiere->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    elementFenetre->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    elementOccupation->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

/**
 * @fn EcoClassroom::insererElementsCellule
 */
void EcoClassroom::insererElementsCellule()
{
    int nb = tableWidgetSalles->rowCount();
    ++nb;
    tableWidgetSalles->setRowCount(nb);

    tableWidgetSalles->setItem(nb - 1, COLONNE_SALLE_NOM, elementNom);
    tableWidgetSalles->setItem(nb - 1,
                               COLONNE_SALLE_CONFORT_THERMIQUE,
                               elementTHI);
    tableWidgetSalles->setItem(nb - 1, COLONNE_SALLE_QUALITE_AIR, elementCO2);
    tableWidgetSalles->setItem(nb - 1, COLONNE_SALLE_ICONE, elementICONE);
    tableWidgetSalles->setCellWidget(nb - 1,
                                     COLONNE_SALLE_LUMIERES,
                                     elementLumiere);
    tableWidgetSalles->setCellWidget(nb - 1,
                                     COLONNE_SALLE_FENETRES,
                                     elementFenetre);
    tableWidgetSalles->setCellWidget(nb - 1,
                                     COLONNE_SALLE_OCCUPATION,
                                     elementOccupation);
}

/**
 * @fn EcoClassroom::redimensionnerHauteurTable
 */
void EcoClassroom::redimensionnerHauteurTable()
{
    // redimensionner la hauteur de la table
    tableWidgetSalles->setFixedHeight(
      tableWidgetSalles->verticalHeader()->length() +
      tableWidgetSalles->horizontalHeader()->height());
}

/**
 * @fn EcoClassroom::afficherSalleTable
 * @brief Affiche une salle dans le tableau
 * @param salle La salle à afficher dans le tableau
 */
void EcoClassroom::afficherSalleTable(const Salle& salle)
{
    qDebug() << Q_FUNC_INFO << "nom" << salle.getNom() << "temperature"
             << salle.getTemperature() << "humidite" << salle.getHumidite()
             << "CO2" << salle.getCO2() << "Indice ICONE"
             << salle.afficherNiveauICONE() << "lumiere" << salle.getLumiere()
             << "fenetre" << salle.getFenetre() << "occupation"
             << salle.getOccupation();

    // créer des élements de cellule
    creerElementsTexteCellule(salle);
    creerElementsImageCellule(salle);

    // insérer les éléments de cellule
    insererElementsCellule();

    // vérifier les données à afficher
    alerterDepassementSeuilCO2(salle);

    // redimensionner la hauteur de la table
    redimensionnerHauteurTable();
}

/**
 * @fn EcoClassroom::afficherInformationsSalle(const Salle& salle)
 * @brief Affiche les informations d'une salle
 */
void EcoClassroom::afficherInformationsSalle(const Salle& salle)
{
    qInfo() << " Nom : " << salle.getNom() << "\n"
            << "Superficie : " << salle.getSuperficie() << "\n"
            << "Description : " << salle.getDescription() << "\n"
            << "Qualité de l'air : "
            << salle.getQualiteAir() + " " + salle.getCO2();
    nomSalle->setText(salle.getNom());
    superficieSalle->setText(QString::number(salle.getSuperficie()) +
                             " m<sup>2</sup>");
    descriptionSalle->setText(salle.getDescription());
    indiceQualiteAirSalle->setText(salle.getQualiteAir() + " (" +
                                   QString::number(salle.getCO2()) + "ppm) ");
    indiceICONE->setText(salle.afficherNiveauICONE());
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

/**
 * @fn EcoClassroom::alerterDepassementSeuil
 * @brief Vérifie et alerte d'un dépassement de seuil de CO2 dans une salle
 */
void EcoClassroom::alerterDepassementSeuilCO2(const Salle& salle)
{
    qDebug() << Q_FUNC_INFO << salle.getNom() << "CO2" << salle.getCO2();
    // Test du dépassement seuil CO2
    if(salle.getCO2() >= SEUIL_ALERTE_CO2)
    {
        // Fond de la cellule en rouge
        coloriserFondCellule(elementCO2, QColor(255, 0, 0));
        // ou :
        /*coloriserFondCellule(tableWidgetSalles,
                             nb - 1,
                             COLONNE_SALLE_QUALITE_AIR,
                             QString("#ff0000"));*/
        notifierSignalementConfinement(TITRE_NOTIFICATION_CO2,
                                       "Confinement de la salle " +
                                         salle.getNom());
    }
    else
    {
        // Fond de la cellule normal
        coloriserFondCellule(elementCO2, QColor(0, 150, 0));
    }
}

/**
 * @fn EcoClassroom::notifierSignalementConfinement
 * @brief Signale le confinement d'une salle grâce à une notification système
 */
void EcoClassroom::notifierSignalementConfinement(const QString& titre,
                                                  const QString& message)
{
    qDebug() << Q_FUNC_INFO << "titre" << titre << "message" << message;
    QSystemTrayIcon::MessageIcon iconeNotification =
      QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Critical);
    notificationEcoClassroom->showMessage(titre,
                                          message,
                                          iconeNotification,
                                          DUREE_NOTIFICATION);
}

/**
 * @fn EcoClassroom::coloriserFondCellule
 * @brief Colorie le fond d'une cellule d'un QTableWidget
 */
void EcoClassroom::coloriserFondCellule(QTableWidgetItem* cellule,
                                        const QColor&     couleur)
{
    cellule->setBackground(couleur);
}

/**
 * @fn EcoClassroom::coloriserFondCellule
 * @brief Colorie le fond d'une cellule d'un QTableWidget
 */
void EcoClassroom::coloriserFondCellule(QTableWidgetItem* cellule,
                                        const QString&    couleur)
{
    QColor _couleur;
    _couleur.setNamedColor(couleur);
    coloriserFondCellule(cellule, _couleur);
}

/**
 * @fn EcoClassroom::coloriserFondCellule
 * @brief Colorie le fond d'une cellule d'un QTableWidget
 */
void EcoClassroom::coloriserFondCellule(QTableWidget* tableWidgetSalles,
                                        int           ligne,
                                        int           colonne,
                                        const QColor& couleur)
{
    tableWidgetSalles->item(ligne, colonne)->setBackground(couleur);
}

/**
 * @fn EcoClassroom::coloriserFondCellule
 * @brief Colorie le fond d'une cellule d'un QTableWidget
 */
void EcoClassroom::coloriserFondCellule(QTableWidget*  tableWidgetSalles,
                                        int            ligne,
                                        int            colonne,
                                        const QString& couleur)
{
    QColor _couleur;
    _couleur.setNamedColor(couleur);
    coloriserFondCellule(tableWidgetSalles, ligne, colonne, _couleur);
}
