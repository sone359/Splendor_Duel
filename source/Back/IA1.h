#ifndef IA1_H
#define IA1_H

#include "partie.h"
#include "stockGemmes.h"
#include <random>

class IA1
{
public:
    IA1(unsigned int joueur) : partie(*Partie::get_partie()), num_joueur(joueur) {}
    Partie& getPartie() {return partie;}
    unsigned int getNumJoueur(){return num_joueur;}

    bool prendre_3_jetons();
    bool prendre_2_jetons();
    bool prendre_1_jetons();
    float valeur(CarteJoaillerie& carte);
    bool deroulement_tour(bool test = false);
    void gestion_effets(CarteJoaillerie& carte);
    void gestion_effets(CarteRoyale& carte);

private:
    StockGemmes jetons_cible;
    Partie& partie;
    unsigned int num_joueur;
};

#endif
