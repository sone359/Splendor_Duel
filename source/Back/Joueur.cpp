#include "Joueur.h"

// Constructeurs
Joueur::Joueur() :  nbPrivileges(0), nbCouronnes(0), gold(0) {}

Joueur::Joueur(int nbPrivileges, int nbCouronnes, int orValue)
    : nbPrivileges(nbPrivileges), nbCouronnes(nbCouronnes), gold(orValue) {}

// Constructeur de copie
Joueur::Joueur(const Joueur& other)
    : nbPrivileges(other.nbPrivileges),
      nbCouronnes(other.nbCouronnes),
      gold(other.gold)
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

// Op�rateur d'affectation
Joueur& Joueur::operator=(const Joueur& other)
{
    if (this == &other)
    {
        return *this; // �viter l'auto-affectation
    }

    // Copie des membres simples
    nbPrivileges = other.nbPrivileges;
    nbCouronnes = other.nbCouronnes;
    gold = other.gold;
    delete[] cartesJoailleriesPossedees ;
    cartesJoailleriesPossedees = other.cartesJoailleriesPossedees;
    CarteJoaillerie * newTab2 = cartesJoailleriesReservees;
    int taille = sizeof(other.cartesJoailleriesReservees) / sizeof(other.cartesJoailleriesReservees);
    for(int i=0;i<taille;i++) cartesJoailleriesReservees[i]= other.cartesJoailleriesReservees[i];
    delete[] newTab2 ;
    delete[] cartesRoyalesPossedees ;
    cartesRoyalesPossedees = other.cartesRoyalesPossedees;

    // Copie des tableaux et des objets complexes (� adapter selon votre impl�mentation r�elle)
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
int Joueur::getOr() const
{
    return gold;
}
StockBonus Joueur::getBonus() const
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

void Joueur::setOr(int orValue)
{
    gold = orValue;
}

void Joueur::setBonus(const StockBonus& bonus)
{
    this->bonus = bonus;
}

