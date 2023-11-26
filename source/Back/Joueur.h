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
    StockGemmesOr gemmes;
    StockGemmes bonus;

public:
    // Constructeurs
    Joueur();
    Joueur(int privileges);
    Joueur(int nbPrivileges, int nbCouronnes, StockGemmesOr & tgemmes, StockGemmes & tbonus);

    // Constructeur de copie
    Joueur(const Joueur& other);

    // Operateur d'affectation
    Joueur& operator=(const Joueur& other);

    // Destructeur
    ~Joueur();

    // Getters
    int getNbPrivileges() const;
    CarteJoaillerie* getCartesJoailleriesPossedees() const;
    CarteJoaillerie* getCartesJoailleriesReservees() ;
    CarteRoyale* getCartesRoyalesPossedees() const;
    int getNbCouronnes() const;
    StockGemmesOr getGemmes() const;
    StockGemmes getBonus() const;

    // Setters
    void setNbPrivileges(int nbPrivileges);
    void setCartesJoailleriesPossedees(CarteJoaillerie* cartes);
    void setCartesJoailleriesReservees(const CarteJoaillerie cartes[3]);
    void setCartesRoyalesPossedees(CarteRoyale* cartes);
    void setNbCouronnes(int nbCouronnes);
    void setGemmes(const StockGemmesOr& gemmes);
    void setBonus(const StockGemmes& bonus);
};

#endif // JOUEUR_H_INCLUDED
