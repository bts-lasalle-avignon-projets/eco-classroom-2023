#ifndef ETATSALLE_H
#define ETATSALLE_H

class EtatsSalle
{
  private:
    bool lumiere;
    bool fenetre;
    bool occupation;

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
