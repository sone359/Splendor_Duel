#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include "carte_joaillerie.h" // Inclure le fichier d'en-tete de CarteJoaillerie
#include "CarteRoyale.h"      // Inclure le fichier d'en-tete de CarteRoyale
#include "stockGemmes.h"      // Inclure le fichier d'en-tete de StockGemmes
#include <vector>
#include <array>

class Joueur
{
private:
    int nbPrivileges;
    std::vector<CarteJoaillerie> cartesJoailleriesPossedees;
    std::vector<CarteJoaillerie> cartesJoailleriesReservees;
    std::vector<CarteRoyale> cartesRoyalesPossedees;
    int nbCouronnes;
    StockGemmesOr gemmes;
    StockGemmes bonus;
    unsigned int nbPointsPrestige = 0;
    std::array<unsigned int, 5> nbPointsPrestigeCouleurs = {0, 0, 0, 0, 0};

public:
    // Constructeurs
    Joueur();
    Joueur(int nbPrivileges, int nbCouronnes, StockGemmesOr & tgemmes, StockGemmes & tbonus);

    // Constructeur de copie
    Joueur(const Joueur& other)=delete;

    // Operateur d'affectation
    Joueur& operator=(const Joueur& other)=delete;

    // Destructeur
    ~Joueur(){};

    // Getters
    int getNbPrivileges() const;
    std::vector<CarteJoaillerie>  getCartesJoailleriesPossedees() const;
    std::vector<CarteJoaillerie>  getCartesJoailleriesReservees() const;
    std::vector<CarteRoyale>  getCartesRoyalesPossedees() const;
    int getNbCouronnes() const;
    StockGemmesOr getGemmes() const;
    StockGemmes getBonus() const;
    StockGemmesOr getRessources() const;
    unsigned int getNbPointsPrestige() const;
    unsigned int getNbPointsPrestigeBleu() const;
    unsigned int getNbPointsPrestigeVert() const;
    unsigned int getNbPointsPrestigeBlanc() const;
    unsigned int getNbPointsPrestigeRouge() const;
    unsigned int getNbPointsPrestigeNoir() const;

    // Setters
    void setNbPrivileges(int nbPrivileges);
    //pour initialiser les tableaux à partir d'une sauvegarde par exemple
    void setCartesJoailleriesPossedees(std::vector<CarteJoaillerie> cartes);
    void setCartesJoailleriesReservees(std::vector<CarteJoaillerie> cartes);
    void setCartesRoyalesPossedees(std::vector<CarteRoyale> cartes);
    //pour les modifier element par element
    void addCartesJoailleriesPossedees(CarteJoaillerie & carte);
    void addCartesJoailleriesReservees(CarteJoaillerie & carte);
    void addCartesRoyalesPossedees(CarteRoyale & carte);
    void setNbCouronnes(int nbCouronnes);
    void setGemmes(const StockGemmesOr& gemmes);
    void setBonus(const StockGemmes& bonus);

    int verifVictoire();
};

#endif // JOUEUR_H_INCLUDED
