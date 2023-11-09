#ifndef PLATEAU_H
#define PLATEAU_H

#include "tools.h"
#include "stockGemmes.h"

class Plateau
{
public :

    void ajouterJeton(Jeton jeton);
    bool verifAdjacence(unsigned int* coor_jeton1, unsigned int* coor_jeton2, unsigned int* coor_jeton3=nullptr);
    Jeton retirerJeton(unsigned int* coor_jeton); //Peut renvoyer de l'or et est ainsi utilisé dans la prise de gemmes comme dans la réservation.
    //Réflexion possible à l'avenir : En fonction de son utilisation, envisageable de rendre retirerJeton privé
    StockGemmes actionRetirerJetons(unsigned int* coor_jeton1, unsigned int* coor_jeton2=nullptr, unsigned int* coor_jeton3=nullptr);

    Jeton* operator[](unsigned int colonne){return matrice[colonne];};


private:
    Jeton matrice[5][5] = {Nul};
    const unsigned int ordre_cases[25][2] = {{2, 2}, {2, 3}, {1, 3}, {1, 2}, {1, 1}, {2, 1}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {2, 4}, {1, 4}, {0, 4}, {0, 3}, {0, 2}, {0, 1}, {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}};

};

#endif
