#ifndef SALLE_H
#define SALLE_H
#include "mesures.h"
#include "etatsalle.h"

#include <QString>
#include <QTableWidgetItem>
#include <QLabel>

class Salle
{
  private:
    QString          nom;
    unsigned int     superficie;
    QString          description;
    Mesures*         mesures;
    EtatsSalle*      etats;
    QMap<Salle, int> Salles;
    void             afficherSallesTables(Salle salles);

  public:
    Salle();
    Salle(QString nom, unsigned int superficie, QString description);
};

#endif // SALLE_H
