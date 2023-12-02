#include "Joueur.h"

// Constructeurs
Joueur::Joueur() :  nbPrivileges(0), nbCouronnes(0){}

Joueur::Joueur(int nbPrivileges, int nbCouronnes, StockGemmesOr & tgemmes, StockGemmes & tbonus)
    : nbPrivileges(nbPrivileges), nbCouronnes(nbCouronnes), gemmes(tgemmes), bonus(tbonus) {}



// Getters
int Joueur::getNbPrivileges() const
{
    return nbPrivileges;
}
std::vector<CarteJoaillerie> Joueur::getCartesJoailleriesPossedees() const
{
    return cartesJoailleriesPossedees;
}
std::vector<CarteJoaillerie> Joueur::getCartesJoailleriesReservees() const
{
    return cartesJoailleriesReservees;
}
std::vector<CarteRoyale> Joueur::getCartesRoyalesPossedees() const
{
    return cartesRoyalesPossedees;
}
int Joueur::getNbCouronnes() const
{
    return nbCouronnes;
}
StockGemmesOr Joueur::getGemmes() const
{
    return gemmes;
}

StockGemmes Joueur::getBonus() const
{
    return bonus;
}

StockGemmesOr Joueur::getRessources() const {
    return gemmes+bonus;
}

unsigned int Joueur::getNbPointsPrestige() const
{
    return nbPointsPrestige;
}
unsigned int Joueur::getNbPointsPrestigeBleu() const
{
    return nbPointsPrestigeCouleurs[0];
}
unsigned int Joueur::getNbPointsPrestigeVert() const
{
    return nbPointsPrestigeCouleurs[1];
}
unsigned int Joueur::getNbPointsPrestigeBlanc() const
{
    return nbPointsPrestigeCouleurs[2];
}
unsigned int Joueur::getNbPointsPrestigeRouge() const
{
    return nbPointsPrestigeCouleurs[3];
}
unsigned int Joueur::getNbPointsPrestigeNoir() const
{
    return nbPointsPrestigeCouleurs[4];
}


// Setters
void Joueur::setNbPrivileges(int nbPrivileges)
{
    this->nbPrivileges = nbPrivileges;
}

void Joueur::setCartesJoailleriesPossedees(std::vector<CarteJoaillerie> cartes){
    cartesJoailleriesPossedees=cartes;
}

void Joueur::addCartesJoailleriesPossedees(CarteJoaillerie& carte)
{
    cartesJoailleriesPossedees.push_back(carte);
}

void Joueur::setCartesJoailleriesReservees(std::vector<CarteJoaillerie> cartes)
{
    cartesJoailleriesReservees=cartes;
}

void Joueur::addCartesJoailleriesReservees(CarteJoaillerie& carte)
{
    if (cartesJoailleriesReservees.size()>3) throw SplendorException("Impossible de reserver plus de 3 cartes.");
    else cartesJoailleriesReservees.push_back(carte);
}


void Joueur::setCartesRoyalesPossedees(std::vector<CarteRoyale> cartes)
{
    cartesRoyalesPossedees=cartes;
}

void Joueur::addCartesRoyalesPossedees(CarteRoyale& carte)
{
    cartesRoyalesPossedees.push_back(carte);
}

void Joueur::setNbCouronnes(int nc)
{
    nbCouronnes = nc;
}

void Joueur::setGemmes(const StockGemmesOr& g)
{
    this->gemmes = g;
}


void Joueur::setBonus(const StockGemmes& b)
{
    this->bonus = b;
}

int Joueur::verifVictoire()
//Renvoie 0 si le joueur n'a pas atteint les conditions de victoire, 1 s'il a plus de 20 points de prestige, 2 s'il a plus de 10 couronnes ou 3 s'il a plus de 10 points de prestige dans une des couleurs de gemmes
{
    if(nbPointsPrestige >= 20)
    {
        return 1;
    }
    if(nbCouronnes >= 10)
    {
        return 2;
    }
    if(getNbPointsPrestigeBleu() >= 10 || getNbPointsPrestigeVert() >= 10 || getNbPointsPrestigeBlanc() >= 10 || getNbPointsPrestigeRouge() >= 10 || getNbPointsPrestigeNoir() >= 10)
    {
        return 3;
    }
    return 0;
}
