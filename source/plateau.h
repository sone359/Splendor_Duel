#ifndef PLATEAU_H
#define PLATEAU_H

#include <array>

#include "tools.h"
#include "stockGemmes.h"

class Plateau
{
public :

    //M�thodes statiques car n'ayant pas besoin des attributs d'une instance particuli�re de la classe
    static bool verifAdjacence(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3);
    static bool verifAdjacence(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2);
    //Fonctions utilitaires
    static std::array<unsigned int, 2> minColonne(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3);
    static std::array<unsigned int, 2> minLigne(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3);


    void ajouterJeton(Jeton jeton);
    Jeton retirerJeton(unsigned int* coor_jeton); //Peut renvoyer de l'or et est ainsi utilis� dans la prise de gemmes comme dans la r�servation.
    //R�flexion possible � l'avenir : En fonction de son utilisation, envisageable de rendre retirerJeton priv�
    StockGemmes actionRetirerJetons(unsigned int* coor_jeton1, unsigned int* coor_jeton2=nullptr, unsigned int* coor_jeton3=nullptr);

    //Op�rateurs surcharg�s
    const Jeton* operator[](unsigned int colonne){return matrice[colonne];};//R�flexion possible � l'avenir : Est-ce vraiment utile ? Et est-ce que l'avoir en public ne met pas en p�ril l'encapsulation ?

private:
    Jeton matrice[5][5] = {Nul};
    const std::array<std::array<unsigned int, 2>, 25> ordre_cases[25][2] = {{2, 2}, {2, 3}, {1, 3}, {1, 2}, {1, 1}, {2, 1}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {2, 4}, {1, 4}, {0, 4}, {0, 3}, {0, 2}, {0, 1}, {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}};

};

#endif
