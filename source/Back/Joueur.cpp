#include "Joueur.h"

// Constructeurs
Joueur::Joueur() :  nbPrivileges(0), nbCouronnes(0){}

Joueur::Joueur(int nbPrivileges, int nbCouronnes, StockGemmesOr & tgemmes, StockGemmes & tbonus)
    : nbPrivileges(nbPrivileges), nbCouronnes(nbCouronnes), gemmes(tgemmes), bonus(tbonus) {}

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

// Operateur d'affectation
Joueur& Joueur::operator=(const Joueur& other)
{
    if (this == &other)
    {
        return *this; // Eviter l'auto-affectation
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

    // Copie des tableaux et des objets complexes (a adapter selon votre implementation relle)
    // Exemple : delete[] cartesJoailleriesPossedees; cartesJoailleriesPossedees = new CarteJoaillerie[...];

    return *this;
}

// Destructeur
Joueur::~Joueur()
{
    delete[] cartesJoailleriesPossedees;
    //Il me semble que vu que le tableau est statique il n'y a pas besoin de le libérer (en plus le compilateur fait la tête, c'est pas bon signe) - Simon
    //delete[] cartesJoailleriesReservees;
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
StockGemmesOr Joueur::getGemmes() const
{
    return gemmes;
}

StockGemmes Joueur::getBonus() const
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

void Joueur::setGemmes(const StockGemmesOr& gemmes)
{
    this->gemmes = gemmes;
}


void Joueur::setBonus(const StockGemmes& bonus)
{
    this->bonus = bonus;
}
