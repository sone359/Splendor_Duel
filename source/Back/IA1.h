#ifndef IA1_H
#define IA1_H

#include "partie.h"
#include "stockGemmes.h"


class IA1
{
public:
    IA1() : partie(Partie::get_partie()) {}
    Partie& getPartie() {return partie;}

    bool prendre_3_jetons() const;
    bool prendre_2_jetons() const;
    bool prendre_1_jetons() const;
    float valeur(CarteJoaillerie& carte);

private:
    StockGemmes jetons_cible;
    Partie& partie;
};

#endif
