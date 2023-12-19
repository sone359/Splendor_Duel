#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include "carte_joaillerie.h" // Inclure le fichier d'en-tete de CarteJoaillerie
#include "CarteRoyale.h"      // Inclure le fichier d'en-tete de CarteRoyale
#include "stockGemmes.h"      // Inclure le fichier d'en-tete de StockGemmes
#include <vector>
#include <iostream>
#include <array>
#include <algorithm>
#include <deque>

class Joueur
{
private:
    int nbPrivileges;
    std::vector<CarteJoaillerie> cartesJoailleriesPossedees;
    std::deque<CarteJoaillerie> cartesJoailleriesReservees;
    std::vector<CarteRoyale> cartesRoyalesPossedees;
    int nbCouronnes;
    StockGemmesOr gemmes;
    StockGemmes bonus;
    unsigned int nbPointsPrestige = 0;
    StockGemmes PointsPrestigeCouleurs;

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
    std::deque<CarteJoaillerie>  getCartesJoailleriesReservees() const;
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
    StockGemmes getPointsPrestigeCouleur()const{return PointsPrestigeCouleurs;}

    // Setters
    void setNbPrivileges(int nbPrivileges);
    //pour initialiser les tableaux à partir d'une sauvegarde par exemple
    void setCartesJoailleriesPossedees(std::vector<CarteJoaillerie> cartes);
    void setCartesJoailleriesReservees(std::deque<CarteJoaillerie> cartes);
    void setCartesRoyalesPossedees(std::vector<CarteRoyale> cartes);
    //pour les modifier element par element
    void addCartesJoailleriesPossedees(CarteJoaillerie carte);
    void addCartesJoailleriesReservees(CarteJoaillerie & carte);
    void addCartesRoyalesPossedees(CarteRoyale & carte);
    void addBonus(const CarteJoaillerie& carte);
    void addPrestige(const CarteJoaillerie& carte);
    void addCouronnes(const CarteJoaillerie& cartes);
    void setNbCouronnes(int nbCouronnes);
    void setGemmes(const StockGemmesOr& gemmes);
    void setBonus(const StockGemmes& bonus);
    void setPointsPrestigeCouleur(const StockGemmes& pp){PointsPrestigeCouleurs=pp;}

    std::string sauvegarder()const;
    void addPointsPrestiges(unsigned int quantite){nbPointsPrestige += quantite;}

    int verifVictoire();

    CarteJoaillerie& acheterCarteReservee(unsigned int num);


    bool peutAcheter(const CarteJoaillerie& carte);

};

inline std::ostream& operator<<(std::ostream& os, const Joueur& j) {
        os <<"\nPrivileges : "<< j.getNbPrivileges() << "\nCouronnes : " << j.getNbCouronnes()<<'\n';
        os << "  Cartes Joailleries Possedees:\n";
        for (const auto& carte : j.getCartesJoailleriesPossedees()) {
            os << "    " << carte << "\n";
        }
        os << "  Cartes Joailleries Reservees:\n";
        for (const auto& carte : j.getCartesJoailleriesReservees()) {
            os << "    " << carte << "\n";
        }
        return os;
    }

#endif
