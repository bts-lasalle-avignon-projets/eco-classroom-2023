/**
 * @file ecoclassroom.cpp
 * @brief Définition de la classe EcoClassroom
 */
#include "ecoclassroom.h"
#include "salle.h"
#include "communicationmqtt.h"
#include "basededonnees.h"

/**
 * @fn EcoClassroom::EcoClassroom
 * @brief Constructeur de la classe EcoClassroom
 * @param parent nullptr pour en faire la fenêtre principale de l'application
 */
EcoClassroom::EcoClassroom(QWidget* parent) :
    QMainWindow(parent), nbLignesSalles(0),
    communicationMQTT(new CommunicationMQTT(this)),
    baseDeDonnees(BaseDeDonnees::getInstance())
{
    qDebug() << Q_FUNC_INFO;
    baseDeDonnees->connecter();
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
    BaseDeDonnees::detruireInstance();
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
    layoutF2Informations->addWidget(labelIndiceQualiteAirSalle, 3, 0);
    layoutF2Informations->addWidget(indiceQualiteAirSalle, 3, 1);
    layoutF2Informations->addWidget(labelIndiceICONE, 4, 0);
    layoutF2Informations->addWidget(indiceICONE, 4, 1);
    layoutF2Informations->addWidget(labelTemperatureSalle, 5, 0);
    layoutF2Informations->addWidget(temperatureSalle, 5, 1);
    layoutF2Informations->addWidget(labelHumiditeSalle, 6, 0);
    layoutF2Informations->addWidget(humiditeSalle, 6, 1);
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
    labelNomSalle              = new QLabel(this);
    labelSuperficieSalle       = new QLabel(this);
    labelDescriptionSalle      = new QLabel(this);
    labelIndiceQualiteAirSalle = new QLabel(this);
    labelIndiceICONE           = new QLabel(this);
    labelTemperatureSalle      = new QLabel(this);
    labelHumiditeSalle         = new QLabel(this);

    // affichage du widget
    labelNomSalle->setText("Nom :");
    nomSalle = new QLabel(this);

    labelSuperficieSalle->setText("Superficie :");
    superficieSalle = new QLabel(this);

    labelDescriptionSalle->setText("Description :");
    descriptionSalle = new QLabel(this);

    labelIndiceQualiteAirSalle->setText("Indice Qualité de l'air :");
    indiceQualiteAirSalle = new QLabel(this);

    labelIndiceICONE->setText("Indice ICONE :");
    indiceICONE = new QLabel(this);

    labelTemperatureSalle->setText("Température :");
    temperatureSalle = new QLabel(this);

    labelHumiditeSalle->setText("Humidité :");
    humiditeSalle = new QLabel(this);

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
    Salle::TypeMessage getTypeMessage(QString typeDonnee);
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
    connect(
      communicationMQTT->getClient(),
      SIGNAL(messageReceived(const QByteArray&, const QMqttTopicName&)),
      this,
      SLOT(recevoirMessageMQTT(const QByteArray&, const QMqttTopicName&)));
}

/**
 * @fn EcoClassroom::chargerSalles
 * @brief Charger les salles
 */
void EcoClassroom::chargerSalles()
{
    qDebug() << Q_FUNC_INFO;
    salles.clear();

#ifdef AVEC_BDD
    QVector<QStringList> sallesBDD;
    QString              requete = "SELECT * FROM Salle";
    bool                 retour;

    retour = baseDeDonnees->recuperer(requete, sallesBDD);
    if(retour)
    {
        qDebug() << Q_FUNC_INFO << sallesBDD;
        for(int i = 0; i < sallesBDD.size(); ++i)
        {
            qDebug() << Q_FUNC_INFO << sallesBDD[i];
            salles[sallesBDD[i][Salle::TableSalle::CHAMP_NOM]] = new Salle(
              sallesBDD[i][Salle::TableSalle::CHAMP_NOM],
              sallesBDD[i][Salle::TableSalle::CHAMP_SUPERFICIE].toInt(),
              sallesBDD[i][Salle::TableSalle::CHAMP_DESCRIPTION]);
            salles[sallesBDD[i][Salle::TableSalle::CHAMP_NOM]]->setOccupation(
              sallesBDD[i][Salle::TableSalle::CHAMP_EstOccupe].toInt());
            salles[sallesBDD[i][Salle::TableSalle::CHAMP_NOM]]->setLumiere(
              sallesBDD[i][Salle::TableSalle::CHAMP_EtatLumieres].toInt());
            salles[sallesBDD[i][Salle::TableSalle::CHAMP_NOM]]->setFenetre(
              sallesBDD[i][Salle::TableSalle::CHAMP_EtatFenetres].toInt());

            salles[sallesBDD[i][Salle::TableSalle::CHAMP_NOM]]->setIndiceTHI(
              sallesBDD[i][Salle::TableSalle::CHAMP_IndiceConfortTHI].toInt());
            salles[sallesBDD[i][Salle::TableSalle::CHAMP_NOM]]->setIndiceICONE(
              sallesBDD[i][Salle::TableSalle::CHAMP_IndiceConfinement].toInt());
            salles[sallesBDD[i][Salle::TableSalle::CHAMP_NOM]]
              ->setIndiceQualiteAir(
                sallesBDD[i][Salle::TableSalle::CHAMP_IndiceQualiteAir]
                  .toInt());
        }
    }
    else
    {
        QMessageBox::critical(0, "Erreur BDD", "Aucune salle chargée !");
    }
#else
    // Pour les tests
    // Exemple simple (si pas de base de données)
    salles["B11"] = new Salle("B11", 18, "Salle de TD");
    salles["B20"] = new Salle("B20", 65, "Atelier");
    salles["B21"] = new Salle("B21", 35, "Salle de TP");
    salles["B22"] = new Salle("B22", 80, "Salle de cours");
#endif

    qDebug() << Q_FUNC_INFO << salles;
    qDebug() << Q_FUNC_INFO << "Nb salles" << salles.size();

#ifdef SIMULATION_CO2
    simulerMesureCO2();
#endif

    effacerSalles();

    QMapIterator<QString, Salle*> salle(salles);
    while(salle.hasNext())
    {
        salle.next();
        qDebug() << Q_FUNC_INFO << "Salle" << salle.key();
        afficherSalleTable(*salle.value());
    }
}

#ifdef SIMULATION_CO2
/**
 * @fn EcoClassroom::simulerMesureCO2
 * @brief Permet de simuler les mesures de CO2 pour les salles
 * et donc simuler la mesure de l'indice ICONE
 */
void EcoClassroom::simulerMesureCO2()
{
    // différentes mesures
    // échantillons (5 h de mesures - 1 mesure toutes les 10 minutes)
    QVector<unsigned int> mesuresCO2DeLaB11(
      { 312,  455,  380,  658,  889,  905,  1100, 1540, 1422, 1669,
        1702, 1698, 1805, 1850, 1630, 1496, 1355, 1255, 1104, 1040,
        922,  669,  702,  698,  512,  555,  480,  404,  489,  458 }); // en ppm
    QVector<unsigned int> mesuresCO2DeLaB20(
      { 312,  455, 380,  658,  889,  905, 999, 997, 822, 969,
        1002, 698, 1005, 1050, 1130, 896, 855, 755, 804, 840,
        622,  669, 702,  698,  512,  555, 480, 458, 489, 999 }); // en ppm
    QVector<unsigned int> mesuresCO2DeLaB21(
      { 312, 455, 380, 658, 889, 905, 900, 940, 922, 969,
        702, 698, 805, 850, 630, 496, 355, 255, 504, 540,
        922, 669, 702, 698, 512, 555, 480, 458, 489, 540 }); // en ppm
    QVector<unsigned int> mesuresCO2DeLaB22(
      { 1312, 1455, 1380, 1658, 189,  1905, 1701, 1740, 1722, 1769,
        1702, 1798, 1805, 1850, 1730, 1896, 1355, 1755, 1704, 1940,
        1922, 1869, 1702, 1698, 1712, 1755, 1780, 1758, 1789, 1705 }); // en ppm

    if(salles.contains("B11"))
    {
        qDebug() << Q_FUNC_INFO << "mesuresCO2DeLaB11" << mesuresCO2DeLaB11;
        for(int i = 0; i < mesuresCO2DeLaB11.size(); ++i)
        {
            salles["B11"]->setCO2(mesuresCO2DeLaB11[i]);
        }
        qDebug() << Q_FUNC_INFO << salles["B11"]->getNom();
        salles["B11"]->calculerIndiceICONE();
        enregistrerICONEDansBDD(salles["B11"]);
        enregistrerQualiteAirDansBDD(salles["B11"]);
    }

    if(salles.contains("B20"))
    {
        qDebug() << Q_FUNC_INFO << "mesuresCO2DeLaB20" << mesuresCO2DeLaB20;
        for(int i = 0; i < mesuresCO2DeLaB20.size(); ++i)
        {
            salles["B20"]->setCO2(mesuresCO2DeLaB20[i]);
        }
        qDebug() << Q_FUNC_INFO << salles["B20"]->getNom();
        salles["B20"]->calculerIndiceICONE();
        enregistrerICONEDansBDD(salles["B20"]);
        enregistrerQualiteAirDansBDD(salles["B20"]);
    }

    if(salles.contains("B21"))
    {
        qDebug() << Q_FUNC_INFO << "mesuresCO2DeLaB21" << mesuresCO2DeLaB21;
        for(int i = 0; i < mesuresCO2DeLaB21.size(); ++i)
        {
            salles["B21"]->setCO2(mesuresCO2DeLaB21[i]);
        }
        qDebug() << Q_FUNC_INFO << salles["B21"]->getNom();
        salles["B21"]->calculerIndiceICONE();
        enregistrerICONEDansBDD(salles["B21"]);
        enregistrerQualiteAirDansBDD(salles["B21"]);
    }

    if(salles.contains("B22"))
    {
        qDebug() << Q_FUNC_INFO << "mesuresCO2DeLaB22" << mesuresCO2DeLaB22;
        for(int i = 0; i < mesuresCO2DeLaB22.size(); ++i)
        {
            salles["B22"]->setCO2(mesuresCO2DeLaB22[i]);
        }
        qDebug() << Q_FUNC_INFO << salles["B22"]->getNom();
        salles["B22"]->calculerIndiceICONE();
        enregistrerICONEDansBDD(salles["B22"]);
        enregistrerQualiteAirDansBDD(salles["B22"]);
    }
}
#endif

/**
 * @fn EcoClassroom::creerElementsTexteCellule
 * @param salle
 */
void EcoClassroom::creerElementsTexteCellule(const Salle& salle)
{
    elementNom = new QTableWidgetItem(salle.getNom());
    elementTHI = new QTableWidgetItem(salle.getTHI());
    elementCO2 = new QTableWidgetItem(
      QString(afficherNiveauQualiteAir(salle.getIndiceQualiteAir())));
    elementICONE = new QTableWidgetItem(
      QString(afficherNiveauICONE(salle.getIndiceICONE())));

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
                                     COLONNE_SALLE_PRESENCE,
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
             << afficherNiveauICONE(salle.getIndiceICONE()) << "lumiere"
             << salle.getLumiere() << "fenetre" << salle.getFenetre()
             << "occupation" << salle.getOccupation();

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
void EcoClassroom::afficherInformationsSalle(Salle& salle, bool affichage)
{
    if(!affichage)
    {
        qDebug() << Q_FUNC_INFO << nomSalle->text() << " vs " << salle.getNom();
        if(nomSalle->text() != salle.getNom())
            return;
    }
    salle.determinerIndiceQualiteAir();
    qDebug() << Q_FUNC_INFO << "nom " << salle.getNom() << "superficie "
             << salle.getSuperficie() << "description "
             << salle.getDescription() << "qualite air "
             << salle.getIndiceQualiteAir() << "temperature "
             << salle.getTemperature() << "humidité " << salle.getHumidite();
    nomSalle->setText(salle.getNom());
    superficieSalle->setText(QString::number(salle.getSuperficie()) +
                             " m<sup>2</sup>");
    descriptionSalle->setText(salle.getDescription());
    indiceQualiteAirSalle->setText(
      afficherNiveauQualiteAir(salle.getIndiceQualiteAir()) + " (" +
      QString::number(salle.getCO2()) + "ppm) ");
    indiceICONE->setText(afficherNiveauICONE(salle.getIndiceICONE()));
    temperatureSalle->setText(QString::number(salle.getTemperature()) + " °C");
    humiditeSalle->setText(QString::number(salle.getHumidite()) + " %");
    if(affichage)
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
 * @fn EcoClassroom::recevoirMessage
 * @brief Permet de recevoir le message MQTT
 * @param message
 * @param topic
 */
void EcoClassroom::recevoirMessageMQTT(const QByteArray&     message,
                                       const QMqttTopicName& topic)
{
    qDebug() << Q_FUNC_INFO << QDateTime::currentDateTime().toString()
             << "topic" << topic.name() << "message" << message;
    QStringList champsTopic = topic.name().split("/");
    qDebug() << Q_FUNC_INFO << "champsTopic" << champsTopic;

    if(champsTopic.at(Salle::ChampsTopic::RACINE)
         .startsWith(RACINE_TOPIC)) // Ex de topic : salles/B22/Sonde/co2
    {
        traiterNouveauMessageMQTT(
          champsTopic.at(Salle::ChampsTopic::SALLE),
          champsTopic.at(Salle::ChampsTopic::MODULE),
          champsTopic.at(Salle::ChampsTopic::TYPE_DONNEE),
          QString(message));
    }
}

/**
 * @fn EcoClassroom::traiterNouveauMessageMQTT
 * @brief permet de traiter le message MQTT qui vient d'être reçu
 * @param salle
 * @param module
 * @param typeDonnee
 * @param message
 */
void EcoClassroom::traiterNouveauMessageMQTT(QString salle,
                                             QString module,
                                             QString typeDonnee,
                                             QString message)
{
    qDebug() << Q_FUNC_INFO << QDateTime::currentDateTime().toString()
             << "salle" << salle << "module" << module << "typeDonnee"
             << typeDonnee << "message" << message;

    // est-ce que c'est une salle "inconnue" ?
    if(!salles.contains(salle))
    {
        // nouvelle salle !
        // 1. instancier cette nouvelle salle et l'insérer dans salles
        salles[salle] = new Salle(salle, 0, "");
        salles[salle]->getDescription();
        salles[salle]->getSuperficie();
        Salle salleSelectionner = *salles[salle];
        afficherSalleTable(salleSelectionner);
        // 2. "stocker" dans la base de données (INSERT)
        enregistrerSalle(salles[salle]->getNom(),
                         salles[salle]->getDescription(),
                         salles[salle]->getSuperficie());
    }

    // 3. mettre à jour la donnée de la salle
    Salle::TypeMessage type = Salle::getTypeMessage(typeDonnee);
    qDebug() << Q_FUNC_INFO << "salle" << salle << "typeDonnee" << typeDonnee
             << "type" << type << "message" << message;
    switch(type)
    {
        case Salle::TypeMessage::INCONNU:
            qDebug() << "donnée inconnue";
            break;
        case Salle::TypeMessage::TEMPERATURE:
            salles[salle]->setTemperature(message.toDouble());
            break;
        case Salle::TypeMessage::HUMIDITE:
            salles[salle]->setHumidite(message.toUInt());
            break;
        case Salle::TypeMessage::CO2:
            salles[salle]->setCO2(message.toUInt());
            break;
        case Salle::TypeMessage::LUMIERE:
            salles[salle]->setLumiere(message.toInt());
            break;
        case Salle::TypeMessage::FENETRE:
            salles[salle]->setFenetre(message.toInt());
            break;
        case Salle::TypeMessage::OCCUPATION:
            salles[salle]->setOccupation(message.toInt());
            break;
    }

    // 5. Mettre à jour l'affichage détaillé d'une salle
    switch(type)
    {
        case Salle::TypeMessage::TEMPERATURE:
        case Salle::TypeMessage::HUMIDITE:
        case Salle::TypeMessage::CO2:
            afficherInformationsSalle(*salles[salle], false);
            break;
    }

    // 4a. mettre à jour l'affichage "textuel" de la donnée de la salle
    for(int i = 0; i < tableWidgetSalles->rowCount(); i++)
    {
        QTableWidgetItem* elementNom =
          tableWidgetSalles->item(i, COLONNE_SALLE_NOM);
        // type de donnée ?
        if(elementNom->data(0).toString() == salle && typeDonnee == "co2")
        {
            salles[salle]->calculerIndiceICONE();
            QTableWidgetItem* elementIcone =
              tableWidgetSalles->item(i, COLONNE_SALLE_ICONE);
            elementIcone->setData(
              Qt::DisplayRole,
              afficherNiveauICONE(salles[salle]->getIndiceICONE()));

            salles[salle]->determinerIndiceQualiteAir();
            QTableWidgetItem* elementQualiteAir =
              tableWidgetSalles->item(i, COLONNE_SALLE_QUALITE_AIR);
            elementQualiteAir->setData(
              Qt::DisplayRole,
              afficherNiveauQualiteAir(salles[salle]->getIndiceQualiteAir()));
            Salle salleSelectionner = *salles[salle];
            alerterDepassementSeuilCO2(salleSelectionner);
            enregistrerICONEDansBDD(salles[salle]);
            enregistrerQualiteAirDansBDD(salles[salle]);
            break;
        }
        else if(elementNom->data(0).toString() == salle &&
                (typeDonnee == "temperature" || typeDonnee == "humidite"))
        {
            salles[salle]->determinerIndiceTHI();
            QTableWidgetItem* elementTHI =
              tableWidgetSalles->item(i, COLONNE_SALLE_CONFORT_THERMIQUE);
            elementTHI->setData(Qt::DisplayRole, salles[salle]->getTHI());
            enregistrerTHIDansBDD(salles[salle]);
            break;
        }

        // 4b. mettre à jour l'affichage "widget" de la donnée de la salle
        if(elementNom->data(0).toString() == salle && typeDonnee == "lumiere")
        {
            QLabel* nouvelElementLumiere = new QLabel(this);
            nouvelElementLumiere->setAlignment(Qt::AlignHCenter |
                                               Qt::AlignVCenter);
            if(!salles[salle]->getLumiere())
            {
                nouvelElementLumiere->setPixmap(QPixmap(":/images/led-verte"));
                tableWidgetSalles->setCellWidget(i,
                                                 COLONNE_SALLE_LUMIERES,
                                                 nouvelElementLumiere);
            }
            else
            {
                nouvelElementLumiere->setPixmap(QPixmap(":/images/led-rouge"));
                tableWidgetSalles->setCellWidget(i,
                                                 COLONNE_SALLE_LUMIERES,
                                                 nouvelElementLumiere);
            }
            enregistrerEtatLumiereDansBDD(salles[salle]);
            break;
        }
        else if(elementNom->data(0).toString() == salle &&
                typeDonnee == "presence")
        {
            QLabel* nouvelElementOccupation = new QLabel(this);
            nouvelElementOccupation->setAlignment(Qt::AlignHCenter |
                                                  Qt::AlignVCenter);

            if(!salles[salle]->getOccupation())
            {
                nouvelElementOccupation->setPixmap(
                  QPixmap(":/images/led-verte"));
                tableWidgetSalles->setCellWidget(i,
                                                 COLONNE_SALLE_PRESENCE,
                                                 nouvelElementOccupation);
            }
            else
            {
                nouvelElementOccupation->setPixmap(
                  QPixmap(":/images/led-rouge"));
                tableWidgetSalles->setCellWidget(i,
                                                 COLONNE_SALLE_PRESENCE,
                                                 nouvelElementOccupation);
            }
            enregistrerEtatPresenceDansBDD(salles[salle]);
            break;
        }
        else if(elementNom->data(0).toString() == salle &&
                typeDonnee == "fenetre")
        {
            QLabel* nouvelElementFenetre = new QLabel(this);
            nouvelElementFenetre->setAlignment(Qt::AlignHCenter |
                                               Qt::AlignVCenter);

            if(!salles[salle]->getFenetre())
            {
                nouvelElementFenetre->setPixmap(QPixmap(":/images/led-verte"));
                tableWidgetSalles->setCellWidget(i,
                                                 COLONNE_SALLE_FENETRES,
                                                 nouvelElementFenetre);
            }
            else
            {
                nouvelElementFenetre->setPixmap(QPixmap(":/images/led-rouge"));
                tableWidgetSalles->setCellWidget(i,
                                                 COLONNE_SALLE_FENETRES,
                                                 nouvelElementFenetre);
            }
            enregistrerEtatFenetreDansBDD(salles[salle]);
            break;
        }
    }
}

/**
 * @fn EcoClassroom::alerterDepassementSeuil
 * @brief Vérifie et alerte d'un dépassement de seuil de CO2 dans une salle
 */
void EcoClassroom::alerterDepassementSeuilCO2(const Salle& salle)
{
    qDebug() << Q_FUNC_INFO << salle.getNom() << "CO2" << salle.getCO2();
    for(int i = 0; i < tableWidgetSalles->rowCount(); i++)
    {
        QTableWidgetItem* elementNom =
          tableWidgetSalles->item(i, COLONNE_SALLE_NOM);
        if(elementNom->data(0).toString() == salle.getNom())
        {
            QTableWidgetItem* nouvelElementCO2 =
              tableWidgetSalles->item(i, COLONNE_SALLE_QUALITE_AIR);
            // Test du dépassement seuil CO2
            if(salle.getCO2() >= SEUIL_ALERTE_CO2)
            {
                // Fond de la cellule en rouge
                coloriserFondCellule(nouvelElementCO2, QColor(255, 0, 0));
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
                coloriserFondCellule(nouvelElementCO2, QColor(0, 150, 0));
            }
        }
    }
}

/**
 * @fn EcoClassroom::notifierSignalementConfinement
 * @brief Signale le confinement d'une salle grâce à une notification
 * système
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

/**
 * @fn EcoClassroom::enregistrerICONEDansBDD
 * @brief Enregistre les indices ICONE calculés grâce aux mesures réalisées
 * @param salle
 */
void EcoClassroom::enregistrerICONEDansBDD(Salle* salle)
{
    QString requeteICONE =
      "UPDATE Salle SET idIndiceConfinement = '" +
      QString::number(salles[salle->getNom()]->getIndiceICONE()) +
      "' WHERE nom = " + "'" + salle->getNom() + "'" + ";";
    qDebug() << Q_FUNC_INFO << "requete" << requeteICONE;
    baseDeDonnees->executer(requeteICONE);
}

/**
 * @fn EcoClassroom::enregistrerQualiteAirDansBDD
 * @brief Enregistre les indices Qualité de l'Air calculés grâce aux mesures
 * réalisées
 * @param salle
 */
void EcoClassroom::enregistrerQualiteAirDansBDD(Salle* salle)
{
    salle->determinerIndiceQualiteAir();
    qDebug() << Q_FUNC_INFO << "indiceQualiteAir"
             << salles[salle->getNom()]->getIndiceQualiteAir();
    QString requeteQualiteAir =
      "UPDATE Salle SET idIndiceQualiteAir = '" +
      QString::number(salles[salle->getNom()]->getIndiceQualiteAir()) +
      "' WHERE nom = " + "'" + salle->getNom() + "'" + ";";
    qDebug() << Q_FUNC_INFO << "requeteQualiteAir" << requeteQualiteAir;
    baseDeDonnees->executer(requeteQualiteAir);
}

void EcoClassroom::enregistrerTHIDansBDD(Salle* salle)
{
    salle->determinerIndiceTHI();
    qDebug() << Q_FUNC_INFO << "THI" << salles[salle->getNom()]->getIndiceTHI();
    QString requeteTHI =
      "UPDATE Salle SET idIndiceConfortTHI = '" +
      QString::number(salles[salle->getNom()]->getIndiceTHI()) +
      "' WHERE nom = " + "'" + salle->getNom() + "'" + ";";
    qDebug() << Q_FUNC_INFO << "requeteTHI" << requeteTHI;
    baseDeDonnees->executer(requeteTHI);
}

void EcoClassroom::enregistrerEtatFenetreDansBDD(Salle* salle)
{
    qDebug() << Q_FUNC_INFO << "etatFenetre"
             << salles[salle->getNom()]->getFenetre();
    QString requete = "UPDATE Salle SET etatFenetres = '" +
                      QString::number(salles[salle->getNom()]->getFenetre()) +
                      "' WHERE nom = " + "'" + salle->getNom() + "'" + ";";
    qDebug() << Q_FUNC_INFO << "requete" << requete;
    baseDeDonnees->executer(requete);
}

void EcoClassroom::enregistrerEtatLumiereDansBDD(Salle* salle)
{
    qDebug() << Q_FUNC_INFO << "etatLumiere"
             << salles[salle->getNom()]->getLumiere();
    QString requete = "UPDATE Salle SET etatLumieres = '" +
                      QString::number(salles[salle->getNom()]->getLumiere()) +
                      "' WHERE nom = " + "'" + salle->getNom() + "'" + ";";
    qDebug() << Q_FUNC_INFO << "requete" << requete;
    baseDeDonnees->executer(requete);
}

void EcoClassroom::enregistrerEtatPresenceDansBDD(Salle* salle)
{
    qDebug() << Q_FUNC_INFO << "occupation"
             << salles[salle->getNom()]->getOccupation();
    QString requete =
      "UPDATE Salle SET estOccupe = '" +
      QString::number(salles[salle->getNom()]->getOccupation()) +
      "' WHERE nom = " + "'" + salle->getNom() + "'" + ";";
    qDebug() << Q_FUNC_INFO << "requete" << requete;
    baseDeDonnees->executer(requete);
}

void EcoClassroom::enregistrerSalle(QString      nomDeLaSalle,
                                    QString      descriptionDeLaSalle,
                                    unsigned int superficieDeLaSalle)
{
    QString requeteSalle =
      "INSERT INTO Salle (nom, description, superficie) VALUES (" +
      nomDeLaSalle + "," + descriptionDeLaSalle + "," + superficieDeLaSalle +
      ")";
    qDebug() << Q_FUNC_INFO << "requeteSalle" << requeteSalle;
    // baseDeDonnees->executer(requeteSalle);
}

/**
 * @fn EcoClassroom::afficherNiveauICONE
 * @brief permet d'afficher le niveau ICONE par rapport à l'indice ICONE
 * @return
 */
QString EcoClassroom::afficherNiveauICONE(int indiceIcone) const
{
    if(indiceIcone == CONFINEMENT_NUL)
        return "Nul";
    if(indiceIcone == CONFINEMENT_FAIBLE)
        return "Faible";
    if(indiceIcone == CONFINEMENT_MOYEN)
        return "Moyen";
    if(indiceIcone == CONFINEMENT_ELEVE)
        return "Élevé";
    if(indiceIcone == CONFINEMENT_TRES_ELEVE)
        return "Très Élevé";
    if(indiceIcone == CONFINEMENT_EXTREME)
        return "Extrême";
    else
        return QString::number(indiceIcone);
}

/**
 *@fn EcoClassroom::afficherNiveauQualiteAir(int indiceQualiteAir) const
 * @brief Méthode qui affiche le niveau de la Qualité de l'Air en fonction
 *de l'indice Qualité de L'Air
 * @param indiceQualiteAir
 * @return QString
 */
QString EcoClassroom::afficherNiveauQualiteAir(int indiceQualiteAir) const
{
    if(indiceQualiteAir == Salle::IndiceQualiteAir::Excellente)
        return "Excellente";
    else if(indiceQualiteAir == Salle::IndiceQualiteAir::Tres_Bien)
        return "Très Bien";
    else if(indiceQualiteAir == Salle::IndiceQualiteAir::Modere)
        return "Modéré";
    else if(indiceQualiteAir == Salle::IndiceQualiteAir::Mauvais)
        return "Mauvais";
    else if(indiceQualiteAir == Salle::IndiceQualiteAir::Tres_Mauvais)
        return "Très Mauvais";
    else
        return "Sévère";
}
