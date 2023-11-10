#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include "carte_joaillerie.h" // Inclure le fichier d'en-tête de CarteJoaillerie
#include "CarteRoyale.h"      // Inclure le fichier d'en-tête de CarteRoyale
#include "StockGemmes.h"      // Inclure le fichier d'en-tête de StockGemmes

class Joueur
{
private:
    int nbPrivileges;
    CarteJoaillerie* cartesJoailleriesPossedees;
    CarteJoaillerie cartesJoailleriesReservees[3];
    CarteRoyale* cartesRoyalesPossedees;
    int nbCouronnes;
    StockGemmes gemmes;
    int gold;
    StockGemmes bonus;

public:
    // Constructeurs
    Joueur();
    Joueur(int nbPrivileges, int nbCouronnes, int gold);

    // Constructeur de copie
    Joueur(const Joueur& other);

    // Opérateur d'affectation
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
    int getOr() const;
    StockGemmes getBonus() const;

    // Setters
    void setNbPrivileges(int nbPrivileges);
    void setCartesJoailleriesPossedees(CarteJoaillerie* cartes);
    void setCartesJoailleriesReservees(const CarteJoaillerie cartes[3]);
    void setCartesRoyalesPossedees(CarteRoyale* cartes);
    void setNbCouronnes(int nbCouronnes);
    void setGemmes(const StockGemmes& gemmes);
    void setOr(int orValue);
    void setBonus(const StockGemmes& bonus);
};

#endif // JOUEUR_H_INCLUDED
