#ifndef CARTE_JOAILLERIE_H
#define CARTE_JOAILLERIE_H
#include <string>


class CarteJoaillerie {
private:
    StockGemmes cout;
    int niveau;
    int pointsPrestige;
    int nombreBonus;
    std::string typeBonus;
    Effet capacite;
    int couronnes;
    std::string cheminImage;

public:
    int get_niveau(){
        if (niveau < 1) {
            niveau = 1;
        }
        else if (niveau > 3) {
            niveau = 3;
        }
        return niveau;
    }

    int get_pointsPrestige() {
        return pointsPrestige;
    }

    std::string get_typeBonus() {
        return typeBonus;
    }

    std::string get_capacite() {
        return capacite;
    }

    int get_couronnes() {
        return couronnes;
    }
};

#endif