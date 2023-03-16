#include "ecoclassroom.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ecoClassroom w;
    w.show();
    return a.exec();
}
