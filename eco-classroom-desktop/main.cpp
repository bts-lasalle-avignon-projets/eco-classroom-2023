#include "ecoclassroom.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EcoClassroom ecoClassroom;
    ecoClassroom.show();
    return a.exec();
}
