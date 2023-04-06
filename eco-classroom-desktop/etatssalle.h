/**
 * @file etatsalle.h
 * @brief Déclaration de la classe EtatsSalle
 */

#ifndef ETATSALLE_H
#define ETATSALLE_H

/**
<<<<<<< HEAD:eco-classroom-desktop/etatssalle.h
 * @file etatssalle.h
 * @brief Déclaration de la classe EtatsSalle
 */

=======
 * @class EtatsSalle
 * @brief
 */
>>>>>>> 89131f2eb499b7830a36b46c1ac1a86225fb4f19:eco-classroom-desktop/etatsalle.h
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
