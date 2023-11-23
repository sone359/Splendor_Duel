#include "Joueur.h"

// Constructeurs
Joueur::Joueur() :  nbPrivileges(0), nbCouronnes(0){}

Joueur::Joueur(int nbPrivileges, int nbCouronnes,StockGemmes & tgemmes,StockGemmesOr & tbonus)
    : nbPrivileges(nbPrivileges), nbCouronnes(nbCouronnes), gemmes(tgemmes),bonus(tbonus) {}

// Constructeur de copie
Joueur::Joueur(const Joueur& other)
    : nbPrivileges(other.nbPrivileges),
      nbCouronnes(other.nbCouronnes),
      gemmes(other.gemmes),
      bonus(other.bonus)

{
    delete[] cartesJoailleriesPossedees ;
    cartesJoailleriesPossedees = other.cartesJoailleriesPossedees;
    CarteJoaillerie * newTab2 = cartesJoailleriesReservees;
    int taille = sizeof(other.cartesJoailleriesReservees) / sizeof(other.cartesJoailleriesReservees);
    for(int i=0;i<taille;i++) cartesJoailleriesReservees[i]= other.cartesJoailleriesReservees[i];
    delete[] newTab2 ;
    delete[] cartesRoyalesPossedees ;
    cartesRoyalesPossedees = other.cartesRoyalesPossedees;
}

// Oprateur d'affectation
Joueur& Joueur::operator=(const Joueur& other)
{
    if (this == &other)
    {
        return *this; // viter l'auto-affectation
    }

    // Copie des membres simples
    nbPrivileges = other.nbPrivileges;
    nbCouronnes = other.nbCouronnes;
    bonus=other.bonus;
    delete[] cartesJoailleriesPossedees ;
    cartesJoailleriesPossedees = other.cartesJoailleriesPossedees;
    CarteJoaillerie * newTab2 = cartesJoailleriesReservees;
    int taille = sizeof(other.cartesJoailleriesReservees) / sizeof(other.cartesJoailleriesReservees);
    for(int i=0;i<taille;i++) cartesJoailleriesReservees[i]= other.cartesJoailleriesReservees[i];
    delete[] newTab2 ;
    delete[] cartesRoyalesPossedees ;
    cartesRoyalesPossedees = other.cartesRoyalesPossedees;

    // Copie des tableaux et des objets complexes ( adapter selon votre implmentation relle)
    // Exemple : delete[] cartesJoailleriesPossedees; cartesJoailleriesPossedees = new CarteJoaillerie[...];

    return *this;
}

// Destructeur
Joueur::~Joueur()
{
    delete[] cartesJoailleriesPossedees;
    delete[] cartesJoailleriesReservees;
}

// Getters
int Joueur::getNbPrivileges() const
{
    return nbPrivileges;
}
CarteJoaillerie* Joueur::getCartesJoailleriesPossedees() const
{
    return cartesJoailleriesPossedees;
}
CarteJoaillerie* Joueur::getCartesJoailleriesReservees()
{
    return cartesJoailleriesReservees;
}
CarteRoyale* Joueur::getCartesRoyalesPossedees() const
{
    return cartesRoyalesPossedees;
}
int Joueur::getNbCouronnes() const
{
    return nbCouronnes;
}
StockGemmes Joueur::getGemmes() const
{
    return gemmes;
}

StockGemmesOr Joueur::getBonus() const
{
    return bonus;
}
// Setters
void Joueur::setNbPrivileges(int nbPrivileges)
{
    this->nbPrivileges = nbPrivileges;
}

void Joueur::setCartesJoailleriesPossedees(CarteJoaillerie* cartes)
{
    delete[] cartesJoailleriesPossedees ;
    cartesJoailleriesPossedees = cartes;

}

void Joueur::setCartesJoailleriesReservees(const CarteJoaillerie cartes[3])
{
    CarteJoaillerie * newTab2 = cartesJoailleriesReservees;
    int taille = sizeof(cartes) / sizeof(cartes);
    for(int i=0;i<taille;i++) cartesJoailleriesReservees[i]= cartes[i];
    delete[] newTab2 ;
}

void Joueur::setCartesRoyalesPossedees(CarteRoyale* cartes)
{
delete[] cartesRoyalesPossedees ;
cartesRoyalesPossedees = cartes;

}

void Joueur::setNbCouronnes(int nbCouronnes)
{
    nbCouronnes = nbCouronnes;
}

void Joueur::setGemmes(const StockGemmes& gemmes)
{
    this->gemmes = gemmes;
}


void Joueur::setBonus(const StockGemmesOr& bonus)
{
    this->bonus = bonus;
}
