#include "salle.h"

Salle::Salle() : nom(""), superficie(0), description("")
{

}

Salle::Salle(QString nom, unsigned int superficie, QString description) : nom(nom), superficie(superficie), description(description)
{

}
