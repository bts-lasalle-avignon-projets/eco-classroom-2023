#ifndef SALLE_H
#define SALLE_H
#include <QString>

class Salle
{
private:
    QString nomSalle;
    unsigned int superficieSalle;
    QString descriptionSalle;
public:
    Salle();
    Salle(QString nomSalle, unsigned int superficieSalle, QString descriptionSalle);
};

#endif // SALLE_H
