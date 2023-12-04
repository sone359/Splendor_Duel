#ifndef CARTE_JOAILLERIE_H
#define CARTE_JOAILLERIE_H

#include <ostream>
#include <string>
#include <vector>
#include "stockGemmes.h"
#include "Effet.h"


class CarteJoaillerie {
private:
    StockGemmes cout;//
    int niveau;//
    int pointsPrestige;//
    int nombreBonus;//
    StockGemmes typeBonus;//couleur
    std::vector<Effet> capacite;//
    int couronnes;//
    std::string cheminImage;

public:
    CarteJoaillerie(){};
    CarteJoaillerie(int n,int p,int d,StockGemmes color, int cr, StockGemmes prix, std::vector<Effet> e) : 
    cout(prix), niveau(n), pointsPrestige(p), nombreBonus(d), typeBonus(color),couronnes(cr), capacite(e){
        //cout.set_Bleu(ps);
        //cout.set_Blanc(pd);
        //cout.set_Vert(pe);
        //cout.set_Rouge(pr);
        //cout.set_Noir(po);
        //cout.set_Perle(pp);

        //equivalences data-Effet :
            //rejouer,//second_turn
            //privilege,//privilege_scroll
            //couleur,//multi_gem
            //gemme,//token
            //voler,//steal
            //sans//none

        //if (e=="Token") capacite=gemme;
        //else if (e =="Multi_gem") capacite = couleur;
        //else if (e =="Steal") capacite = voler;
        //else if (e =="Privilege_scroll") capacite = privilege;
        //else if (e =="Second_turn") capacite = rejouer;
        //else if (e =="none") capacite = sans;
        
    };
    int get_niveau() const{
        //if (niveau < 1) {
        //    niveau = 1;
        //}
        //else if (niveau > 3) {
        //    niveau = 3;
        //} pourquoi ça arriverait?
        return niveau;
    }

    int get_pointsPrestige() const {
        return pointsPrestige;
    }

    StockGemmes get_typeBonus() const {
        return typeBonus;
    }

    std::vector<Effet> get_capacite()const {
        return capacite;
    }

    int get_couronnes() const{
        return couronnes;
    }

    //setters
    void setCout(StockGemmes c) {cout=c;};
    void setNiveau(int n) {niveau=n;};
    void setPointsPrestige(int p) {pointsPrestige=p;}
    void setNombreBonus(int n) {nombreBonus=n;}
    void setTypeBonus(StockGemmes type) {typeBonus=type;}
    void setCapacite(std::vector<Effet> e) {capacite=e;}
};

inline std::ostream& operator<<(std::ostream& os, const CarteJoaillerie& c) {
        os << "(" << c.get_niveau() << ", " ;
        for(Effet  effet : c.get_capacite()){
            os<< effet<<" ";
         }
        os <<", "<< c.get_pointsPrestige() << ")";
        return os;
    } 

#endif
