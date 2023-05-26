/**
 * @file mesures.h
 * @brief Déclaration de la classe Mesures
 */
#ifndef MESURES_H
#define MESURES_H
#include <QVector>

#define CONFINEMENT_NUL        0
#define CONFINEMENT_FAIBLE     1
#define CONFINEMENT_MOYEN      2
#define CONFINEMENT_ELEVE      3
#define CONFINEMENT_TRES_ELEVE 4
#define CONFINEMENT_EXTREME    5

#define SEUIL_BAS_CO2_DEFINI  1000
#define SEUIL_HAUT_CO2_DEFINI 1700
/**
 * @class Mesures
 * @brief Classe permettant de gérer les mesures d'une salle
 */
class Mesures
{
  private:
    double                temperature; //!< Temperature dans la salle
    unsigned int          humidite;    //!< Humidite dans la salle
    QVector<unsigned int> co2;         //!< Taux de CO2 dans la salle

  public:
    Mesures();
    ~Mesures();

    double       getTemperature() const;
    unsigned int getHumidite() const;
    unsigned int getCO2() const;
    void         setTemperature(double temperature);
    void         setHumidite(unsigned int humidite);
    void         setCO2(unsigned int mesureCo2);
    int          calculerIndiceICONE();
    double       calculerProportionSeuilN1();
    double       calculerProportionSeuilN2();
    int calculerIndiceBrute(double proportionSeuilN1, double proportionSeuilN2);
    int determinerIndiceICONE(int indiceBrute);
};

#endif // MESURES_H
