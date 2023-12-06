#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include "carte_joaillerie.h" // Inclure le fichier d'en-tte de CarteJoaillerie
#include "CarteRoyale.h"      // Inclure le fichier d'en-tte de CarteRoyale
#include "stockGemmes.h"      // Inclure le fichier d'en-tte de StockGemmes
#include <vector>
#include <iostream>

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
    void addBonus(const CarteJoaillerie& carte);
    void setNbCouronnes(int nbCouronnes);
    void setGemmes(const StockGemmesOr& gemmes);
    void setBonus(const StockGemmes& bonus);

    int peutAcheter(const CarteJoaillerie& carte){
        StockGemmes temp = gemmes + bonus;
        if (temp<carte.get_cout()){
            temp=temp/carte.get_cout();
            if(temp.total_gemmes()>gemmes.get_Or()){
                std::cout<<"avec or il reste encore "<<temp.total_gemmes()-gemmes.get_Or()<<"\n";
                return 0;  
            }
            else{
                std::cout<<"acheté avec jetons or.\n";
                return 1;  
            }
        }
        else{
            std::cout<<"ca marche :"<<temp-carte.get_cout()<<"\n"; 
            return 1;  

        }
        //temp = carte.get_cout()-temp;
        //std::cout<<"\n--------------------------------------\n";
        //std::cout<<"   "<<carte.get_cout();
        //std::cout<<"\n";
        //std::cout<<"   "<<gemmes;
        //std::cout<<"\n";
        //std::cout<<"--------------------------------------\n";
        //std::cout<<"prix avec gemmes+bonus"<<temp<<"\n\n";
        return 0;
    }
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

#endif // JOUEUR_H_INCLUDED
