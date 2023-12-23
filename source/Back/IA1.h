#ifndef IA1_H
#define IA1_H

#include "partie.h"
#include "stockGemmes.h"
#include <random>

class IA1
{
public:
    bool deroulement_tour(bool test = false);

    //Getters
    Partie& getPartie() const {*Partie::get_partie();}
    unsigned int getNumJoueur() const {return getPartie().joueur_actif();}

    virtual ~IA1() = default;

protected:
    bool prendre_3_jetons();
    bool prendre_2_jetons();
    bool prendre_1_jetons();
    float valeur(CarteJoaillerie& carte) const;
    void gestion_effets(CarteJoaillerie& carte);
    void gestion_effets(CarteRoyale& carte);

private:
    StockGemmes jetons_cible;
};

#endif
