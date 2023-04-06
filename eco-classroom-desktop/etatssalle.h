/**
 * @file etatsalle.h
 * @brief Déclaration de la classe EtatsSalle
 */
#ifndef ETATSALLE_H
#define ETATSALLE_H

/**
 * @class EtatsSalle
 * @brief Classe permettant de gérer les etats d'une salle
 */
class EtatsSalle
{
  private:
    bool lumiere;    //!< Lumiere allumée ou éteinte dans la salle
    bool fenetre;    //!< Fenetre de la salle ouverte ou fermée
    bool occupation; //!< Des personnes ou pas dans la salle

  public:
    EtatsSalle();
    EtatsSalle(bool lumiere, bool fenetre, bool occupation);
    ~EtatsSalle();

    bool getLumiere() const;
    bool getFenetre() const;
    bool getOccupation() const;
    void setLumiere(bool lumiere);
    void setFenetre(bool fenetre);
    void setOccupation(bool occupation);
};

#endif // ETATSALLE_H
