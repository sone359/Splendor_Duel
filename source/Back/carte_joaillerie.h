#ifndef CARTE_JOAILLERIE_H
#define CARTE_JOAILLERIE_H

#include <ostream>
#include <string>
#include <vector>
#include <sstream>
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
    CarteJoaillerie(int n,int p,int d,StockGemmes color, int cr, StockGemmes prix, std::vector<Effet> e,std::string ch) :
    cout(prix), niveau(n), pointsPrestige(p), nombreBonus(d), typeBonus(color),couronnes(cr), capacite(e), cheminImage(ch){};
    int get_niveau() const{
        return niveau;
    }

    std::string getChemin()const{return cheminImage;}

    std::string sauvegarder()const{
        std::stringstream s;
        s<<get_niveau()<<';';
        s<<get_pointsPrestige()<<';';
        s<<get_nbBonus()<<';';
        if (get_typeBonus().get_Blanc()) {
            s<<"blanc;";
        }
        else if (get_typeBonus().get_Blanc()) {
            s<<"blanc;";
        }
        else if (get_typeBonus().get_Vert()) {
            s<<"vert;";
        }
        else if (get_typeBonus().get_Noir()) {
            s<<"noir;";
        }
        else if (get_typeBonus().get_Perle()) {
            s<<"perle;";
        }
        else if (get_typeBonus().get_Rouge()) {
            s<<"rouge;";
        }else{
            s<<"none;";
        }
        s<<get_couronnes()<<";";
        s<<get_cout().sauvegarder();
        int repeat=get_capacite().size();
        while(repeat){
            if (get_capacite()[repeat-1]==rejouer) {
                s<<"rejouer";
            }
            else if (get_capacite()[repeat-1]==privilege) {
                s<<"privilege";
            }
            else if (get_capacite()[repeat-1]==couleur) {
                s<<"couleur";
            }
            else if (get_capacite()[repeat-1]==gemme) {
                s<<"gemme";
            }
            else if (get_capacite()[repeat-1]==voler) {
                s<<"voler";
            }
            else if (get_capacite()[repeat-1]==sans) {
                s<<"sans";
            }
            repeat--;
            if (repeat) s<<',';
        }
        s<<";\n";
        return s.str();
    }

    void afficher_Couleur(std::ostream & os) const {
        if (get_typeBonus().get_Blanc()) {
            os<<"W";
            return;
            }
        if (get_typeBonus().get_Bleu()) {
            os<<"B";
            return;
            }
        if (get_typeBonus().get_Noir()) {
            os<<"N";
            return;
            }
        if (get_typeBonus().get_Perle()) {
            os<<"P";
            return;
            }
        if (get_typeBonus().get_Rouge()) {
            os<<"R";
            return;
            }
        if (get_typeBonus().get_Vert()) {
            os<<"V";
            return;
            }
        os<<"-";
    }

    int get_pointsPrestige() const {
        return pointsPrestige;
    }

    StockGemmes get_typeBonus() const {
        return typeBonus;
    }

    int get_nbBonus()const{
        return nombreBonus;
    }

    std::vector<Effet> get_capacite()const {
        return capacite;
    }

    int get_couronnes() const{
        return couronnes;
    }

    StockGemmes get_cout() const{
        return cout;
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
        os <<"----";
        c.afficher_Couleur(os);
        os<<"---\n";
        os << "|   "<<c.get_nbBonus()<<"  |\n" ;
        os <<"|   "<< c.get_pointsPrestige() << "  |\n";
        for(Effet  effet : c.get_capacite()){
            os<<"|   "<< effet<<"  |\n";
         }
        os<<"|BWVRNP|\n";
        os <<c.get_cout();
        os << "\n--------\n" ;
        return os;
    }

#endif
