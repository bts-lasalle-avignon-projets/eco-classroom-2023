#ifndef SALLE_H
#define SALLE_H
#include <QString>

class Salle
{
private:
    QString nom;
    unsigned int superficie;
    QString description;
public:
    Salle();
    Salle(QString nom, unsigned int superficie, QString description);
};

#endif // SALLE_H
