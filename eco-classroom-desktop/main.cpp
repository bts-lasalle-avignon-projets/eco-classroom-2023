/**
 * @file main.cpp
 * @brief Définition du main
 */
#include "ecoclassroom.h"

#include <QApplication>

/**
 * @fn main
 * @brief Méthode principale du programme
 */
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    EcoClassroom ecoClassroom;
    ecoClassroom.show();
    return a.exec();
}
