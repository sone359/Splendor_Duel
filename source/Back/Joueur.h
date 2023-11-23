#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include "carte_joaillerie.h" // Inclure le fichier d'en-tte de CarteJoaillerie
#include "CarteRoyale.h"      // Inclure le fichier d'en-tte de CarteRoyale
#include "StockGemmes.h"      // Inclure le fichier d'en-tte de StockGemmes

class Joueur
{
private:
    int nbPrivileges;
    CarteJoaillerie* cartesJoailleriesPossedees;
    CarteJoaillerie cartesJoailleriesReservees[3];
    CarteRoyale* cartesRoyalesPossedees;
    int nbCouronnes;
    StockGemmes gemmes;
    StockGemmesOr bonus;

public:
    // Constructeurs
    Joueur();
    Joueur(int nbPrivileges, int nbCouronnes,StockGemmes & tgemmes,StockGemmesOr & tbonus);

    // Constructeur de copie
    Joueur(const Joueur& other);

    // Oprateur d'affectation
    Joueur& operator=(const Joueur& other);

    // Destructeur
    ~Joueur();

    // Getters
    int getNbPrivileges() const;
    CarteJoaillerie* getCartesJoailleriesPossedees() const;
    CarteJoaillerie* getCartesJoailleriesReservees() ;
    CarteRoyale* getCartesRoyalesPossedees() const;
    int getNbCouronnes() const;
    StockGemmes getGemmes() const;
    StockGemmesOr getBonus() const;

    // Setters
    void setNbPrivileges(int nbPrivileges);
    void setCartesJoailleriesPossedees(CarteJoaillerie* cartes);
    void setCartesJoailleriesReservees(const CarteJoaillerie cartes[3]);
    void setCartesRoyalesPossedees(CarteRoyale* cartes);
    void setNbCouronnes(int nbCouronnes);
    void setGemmes(const StockGemmes& gemmes);
    void setBonus(const StockGemmesOr& bonus);
};

#endif // JOUEUR_H_INCLUDED
