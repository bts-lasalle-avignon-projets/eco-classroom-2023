/**
 * @file main.cpp
 * @brief Définition du main
 */
#include <QApplication>
#include "ecoclassroom.h"

/**
 * @fn main
 * @brief Programme principal
 * @details Crée et affiche la fenêtre principale de l'application
 */
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    EcoClassroom ecoClassroom;
    ecoClassroom.show();
    return a.exec();
}
