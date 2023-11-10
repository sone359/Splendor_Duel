#include "plateau.h"

bool Plateau::verifAdjacence(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3)
{
    //Vérification de l'adjacence sur une colonne
    if ((coor_jeton1[0] == coor_jeton2[0]) && (coor_jeton1[0] == coor_jeton3[0]))
    {
        if ((Plateau::minLigne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton1) && (((coor_jeton2[1] == coor_jeton1[1]+1) && (coor_jeton3[1] == coor_jeton1[1]+2)) || ((coor_jeton2[1] == coor_jeton1[1]+2) && (coor_jeton3[1] == coor_jeton1[1]+1))))
        {return true;}
        if ((Plateau::minLigne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton2) && (((coor_jeton1[1] == coor_jeton2[1]+1) && (coor_jeton3[1] == coor_jeton2[1]+2)) || ((coor_jeton1[1] == coor_jeton2[1]+2) && (coor_jeton3[1] == coor_jeton2[1]+1))))
        {return true;}
        if ((Plateau::minLigne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton3) && (((coor_jeton1[1] == coor_jeton3[1]+1) && (coor_jeton2[1] == coor_jeton3[1]+2)) || ((coor_jeton1[1] == coor_jeton3[1]+2) && (coor_jeton2[1] == coor_jeton3[1]+1))))
        {return true;}
    }
    //Vérification de l'adjacence sur une ligne
    if ((coor_jeton1[1] == coor_jeton2[1]) && (coor_jeton1[1] == coor_jeton3[1]))
    {
        if ((Plateau::minColonne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton1) && (((coor_jeton2[0] == coor_jeton1[0]+1) && (coor_jeton3[0] == coor_jeton1[0]+2)) || ((coor_jeton2[0] == coor_jeton1[0]+2) && (coor_jeton3[0] == coor_jeton1[0]+1))))
        {return true;}
        if ((Plateau::minColonne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton2) && (((coor_jeton1[0] == coor_jeton2[0]+1) && (coor_jeton3[0] == coor_jeton2[0]+2)) || ((coor_jeton1[0] == coor_jeton2[0]+2) && (coor_jeton3[0] == coor_jeton2[0]+1))))
        {return true;}
        if ((Plateau::minColonne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton3) && (((coor_jeton1[0] == coor_jeton3[0]+1) && (coor_jeton2[0] == coor_jeton3[0]+2)) || ((coor_jeton1[0] == coor_jeton3[0]+2) && (coor_jeton2[0] == coor_jeton3[0]+1))))
        {return true;}
    }
    //Vérification de l'adjacence sur une diagonale
    if (Plateau::minColonne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton1)
    {
        if (((coor_jeton2[0] == coor_jeton1[0]+1) && (coor_jeton3[0] == coor_jeton1[0]+2)) && (((coor_jeton2[1] == coor_jeton1[1]+1) && (coor_jeton3[1] == coor_jeton1[1]+2)) || ((coor_jeton2[1] == coor_jeton1[1]-1) && (coor_jeton3[1] == coor_jeton1[1]-2))))
        {return true;}
        if (((coor_jeton2[0] == coor_jeton1[0]+2) && (coor_jeton3[0] == coor_jeton1[0]+1)) && (((coor_jeton2[1] == coor_jeton1[1]+2) && (coor_jeton3[1] == coor_jeton1[1]+1)) || ((coor_jeton2[1] == coor_jeton1[1]-2) && (coor_jeton3[1] == coor_jeton1[1]-1))))
        {return true;}
    }
    if (Plateau::minColonne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton2)
    {
        if (((coor_jeton1[0] == coor_jeton2[0]+1) && (coor_jeton3[0] == coor_jeton2[0]+2)) && (((coor_jeton1[1] == coor_jeton2[1]+1) && (coor_jeton3[1] == coor_jeton2[1]+2)) || ((coor_jeton1[1] == coor_jeton2[1]-1) && (coor_jeton3[1] == coor_jeton2[1]-2))))
        {return true;}
        if (((coor_jeton1[0] == coor_jeton2[0]+2) && (coor_jeton3[0] == coor_jeton2[0]+1)) && (((coor_jeton1[1] == coor_jeton2[1]+2) && (coor_jeton3[1] == coor_jeton2[1]+1)) || ((coor_jeton1[1] == coor_jeton2[1]-2) && (coor_jeton3[1] == coor_jeton2[1]-1))))
        {return true;}
    }
    if (Plateau::minColonne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton3)
    {
        if (((coor_jeton1[0] == coor_jeton3[0]+1) && (coor_jeton2[0] == coor_jeton3[0]+2)) && (((coor_jeton1[1] == coor_jeton3[1]+1) && (coor_jeton2[1] == coor_jeton3[1]+2)) || ((coor_jeton1[1] == coor_jeton3[1]-1) && (coor_jeton2[1] == coor_jeton3[1]-2))))
        {return true;}
        if (((coor_jeton1[0] == coor_jeton3[0]+2) && (coor_jeton2[0] == coor_jeton3[0]+1)) && (((coor_jeton1[1] == coor_jeton3[1]+2) && (coor_jeton2[1] == coor_jeton3[1]+1)) || ((coor_jeton1[1] == coor_jeton3[1]-2) && (coor_jeton2[1] == coor_jeton3[1]-1))))
        {return true;}
    }
    //Sinon
    return false;
}

bool Plateau::verifAdjacence(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2)
{
    //Vérification de l'adjacence sur une colonne
    if ((coor_jeton1[0] == coor_jeton2[0]) && ((coor_jeton2[1] == coor_jeton1[1]+1) || (coor_jeton2[1] == coor_jeton1[1]-1)))
    {return true;}
    //Vérification de l'adjacence sur une ligne
    if ((coor_jeton1[1] == coor_jeton2[1]) && ((coor_jeton2[0] == coor_jeton1[0]+1) || (coor_jeton2[0] == coor_jeton1[0]-1)))
    {return true;}
    //Vérification de l'adjacence sur une diagonale
    if ((coor_jeton2[0] == coor_jeton1[0]+1) && ((coor_jeton2[1] == coor_jeton1[1]+1) || (coor_jeton2[1] == coor_jeton1[1]-1)))
    {return true;}
    if ((coor_jeton2[0] == coor_jeton1[0]-1) && ((coor_jeton2[1] == coor_jeton1[1]+1) || (coor_jeton2[1] == coor_jeton1[1]-1)))
    {return true;}
    //Sinon
    return false;
}

//Fonctions utilitaires
std::array<unsigned int, 2> Plateau::minColonne(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3)
{
    if ((coor_jeton1[0] <= coor_jeton2[0]) && (coor_jeton1[0] <= coor_jeton3[0])) {return coor_jeton1;};
    if ((coor_jeton2[0] <= coor_jeton1[0]) && (coor_jeton2[0] <= coor_jeton3[0])) {return coor_jeton2;};
    return coor_jeton3;
}

std::array<unsigned int, 2> Plateau::minLigne(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3)
{
    if ((coor_jeton1[1] <= coor_jeton2[1]) && (coor_jeton1[1] <= coor_jeton3[1])) {return coor_jeton1;};
    if ((coor_jeton2[1] <= coor_jeton1[1]) && (coor_jeton2[1] <= coor_jeton3[1])) {return coor_jeton2;};
    return coor_jeton3;
}
