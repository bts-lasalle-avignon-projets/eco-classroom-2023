#include "ecoclassroom.h"
#include "ui_ecoclassroom.h"
#include "salle.h"

EcoClassroom::EcoClassroom(QWidget* parent) :
    QWidget(parent), ui(new Ui::EcoClassroom)
{
    affichageGlobaleSalles = new QWidget();
    QWidget::showMaximized();
    QGridLayout* layout = new QGridLayout(this);
    boutonB11           = new QPushButton("B11",
                                this); // Abonnement au nom de la salle
    boutonB20           = new QPushButton("B20", this);
    boutonB21           = new QPushButton("B21", this);
    texteIADI           = new QLabel("Indice de confort thermique");
    texteICONE          = new QLabel("Qualité de l'air");
    texteLumiere        = new QLabel("Lumière");
    textePresence       = new QLabel("Présence");
    texteFenetre        = new QLabel("Fenètre(s) ouverte(s)");
    layout->addWidget(texteIADI, 3, 1, 1, 1);
    layout->addWidget(texteICONE);
    layout->addWidget(texteLumiere);
    layout->addWidget(
      textePresence); //@todo le tri est pas exemple salle ou on peut
                      // travailler, pas en filtrant croissant decroissant
    layout->addWidget(texteFenetre);
    setLayout(layout);
}

EcoClassroom::~EcoClassroom()
{
    delete ui;
}

void EcoClassroom::afficherSalles()
{
}

void EcoClassroom::afficherUneSalle()
{
}

void EcoClassroom::afficherMesures()
{
}

void EcoClassroom::afficherEtats()
{
}

void EcoClassroom::afficherTHI()
{
}

void EcoClassroom::afficherIADI()
{
}

void EcoClassroom::afficherICONE()
{
}

void EcoClassroom::filtrerSalles()
{
}

void EcoClassroom::afficherDetailsSalles()
{
}

void EcoClassroom::afficherGraphiques()
{
}
