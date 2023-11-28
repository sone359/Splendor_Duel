#include "Joueur.h"
#include <vector>
#include <algorithm>

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
