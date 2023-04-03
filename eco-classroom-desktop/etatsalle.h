#ifndef ETATSALLE_H
#define ETATSALLE_H

class EtatsSalle
{
  private:
    /**
     * @todo Les attributs ?
     */
  public:
    EtatsSalle();
    ~EtatsSalle();
    bool getLumiere() const;
    bool getFenetre() const;
    bool getOccupation() const;
};

#endif // ETATSALLE_H
