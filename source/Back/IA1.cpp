#include "IA1.h"

bool IA1::prendre_3_jetons() const
{
    int jetons_cible_max = -1; //Il est necessaire d'initialiser le compteur inférieur à 0 de manière a toujours avoir une combinaison de cases valides meme si elle ne contient aucun jeton vise
    unsigned int jetons_cible_temp = 0;
    std::array<unsigned int, 2> coor_jeton1;
    std::array<unsigned int, 2> coor_jeton2;
    std::array<unsigned int, 2> coor_jeton3;
    for (size_t i = 0 ; i < 3 ; i++)
    {
        for (size_t j = 0 ; j < 3 ; j++)
        {
            //Test des combinaisons horizontales
            jetons_cible_temp = 0;
            if (partie.get_plateau()[i][j] != Nul && partie.get_plateau()[i+1][j] != Nul && partie.get_plateau()[i+2][j] != Nul
                && partie.get_plateau()[i][j] != Or && partie.get_plateau()[i+1][j] != Or && partie.get_plateau()[i+2][j] != Or)
            {
                if (jetons_cible.inclus(partie.get_plateau()[i][j])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i+1][j])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i+2][j])) {jetons_cible_temp++;}

                if (jetons_cible_temp == 3)
                {
                    //Prendre les jetons
                    return true;
                }
                if (jetons_cible_temp > jetons_cible_max)
                {
                    jetons_cible_max = jetons_cible_temp;
                    coor_jeton1 = {i, j};
                    coor_jeton2 = {i+1, j};
                    coor_jeton3 = {i+2, j};
                }
            }
            //Test des combinaisons verticales
            jetons_cible_temp = 0;
            if (partie.get_plateau()[i][j] != Nul && partie.get_plateau()[i][j+1] != Nul && partie.get_plateau()[i][j+2] != Nul
                && partie.get_plateau()[i][j] != Or && partie.get_plateau()[i][j+1] != Or && partie.get_plateau()[i][j+2] != Or)
            {
                if (jetons_cible.inclus(partie.get_plateau()[i][j])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i][j+1])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i][j+2])) {jetons_cible_temp++;}

                if (jetons_cible_temp == 3)
                {
                    //Prendre les jetons
                    return true;
                }
                if (jetons_cible_temp > jetons_cible_max)
                {
                    jetons_cible_max = jetons_cible_temp;
                    coor_jeton1 = {i, j};
                    coor_jeton2 = {i, j+1};
                    coor_jeton3 = {i, j+2};
                }
            }
        }
        //Test des combinaisons diagonales
        jetons_cible_temp = 0;
        for (size_t j = 0 ; j < 3-i ; j++)
        {
            if (partie.get_plateau()[i][i+j] != Nul && partie.get_plateau()[i+1][i+j+1] != Nul && partie.get_plateau()[i+2][i+j+2] != Nul
                && partie.get_plateau()[i][i+j] != Or && partie.get_plateau()[i+1][i+j+1] != Or && partie.get_plateau()[i+2][i+j+2] != Or)
            {
                if (jetons_cible.inclus(partie.get_plateau()[i][j])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i+1][i+j+1])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i+2][i+j+2])) {jetons_cible_temp++;}

                if (jetons_cible_temp == 3)
                {
                    //Prendre les jetons
                    return true;
                }
                if (jetons_cible_temp > jetons_cible_max)
                {
                    jetons_cible_max = jetons_cible_temp;
                    coor_jeton1 = {i, j};
                    coor_jeton2 = {i+1, i+j+1};
                    coor_jeton3 = {i+2, i+j+2};
                }
            }
            if (partie.get_plateau()[i+j][i] != Nul && partie.get_plateau()[i+j+1][i+1] != Nul && partie.get_plateau()[i+j+2][i+2] != Nul
                && partie.get_plateau()[i+j][i] != Or && partie.get_plateau()[i+j+1][i+1] != Or && partie.get_plateau()[i+j+2][i+2] != Or)
            {
                if (jetons_cible.inclus(partie.get_plateau()[i+j][j])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i+j+1][j+1])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i+j+2][j+2])) {jetons_cible_temp++;}

                if (jetons_cible_temp == 3)
                {
                    //Prendre les jetons
                    return true;
                }
                if (jetons_cible_temp > jetons_cible_max)
                {
                    jetons_cible_max = jetons_cible_temp;
                    coor_jeton1 = {i, j};
                    coor_jeton2 = {i+j+1, i+1};
                    coor_jeton3 = {i+j+2, i+2};
                }
            }
        }
    }
    if (jetons_cible_temp == 2)
    {
        //Prendre les jetons
        return true;
    }
    return false;
}

bool IA1::prendre_2_jetons() const
{
    int jetons_cible_max = -1; //Il est necessaire d'initialiser le compteur inférieur à 0 de manière a toujours avoir une combinaison de cases valides meme si elle ne contient aucun jeton vise
    unsigned int jetons_cible_temp = 0;
    std::array<unsigned int, 2> coor_jeton1;
    std::array<unsigned int, 2> coor_jeton2;
    for (size_t i = 0 ; i < 4 ; i++)
    {
        for (size_t j = 0 ; j < 4 ; j++)
        {
            //Test des combinaisons horizontales
            jetons_cible_temp = 0;
            if (partie.get_plateau()[i][j] != Nul && partie.get_plateau()[i+1][j] != Nul
                && partie.get_plateau()[i][j] != Or && partie.get_plateau()[i+1][j] != Or)
            {
                if (jetons_cible.inclus(partie.get_plateau()[i][j])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i+1][j])) {jetons_cible_temp++;}

                if (jetons_cible_temp == 2)
                {
                    //Prendre les jetons
                    return true;
                }
                if (jetons_cible_temp > jetons_cible_max)
                {
                    jetons_cible_max = jetons_cible_temp;
                    coor_jeton1 = {i, j};
                    coor_jeton2 = {i+1, j};
                }
            }
            //Test des combinaisons verticales
            jetons_cible_temp = 0;
            if (partie.get_plateau()[i][j] != Nul && partie.get_plateau()[i][j+1] != Nul
                && partie.get_plateau()[i][j] != Or && partie.get_plateau()[i][j+1] != Or)
            {
                if (jetons_cible.inclus(partie.get_plateau()[i][j])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i][j+1])) {jetons_cible_temp++;}

                if (jetons_cible_temp == 2)
                {
                    //Prendre les jetons
                    return true;
                }
                if (jetons_cible_temp > jetons_cible_max)
                {
                    jetons_cible_max = jetons_cible_temp;
                    coor_jeton1 = {i, j};
                    coor_jeton2 = {i, j+1};
                }
            }
        }
        //Test des combinaisons diagonales
        jetons_cible_temp = 0;
        for (size_t j = 0 ; j < 4-i ; j++)
        {
            if (partie.get_plateau()[i][i+j] != Nul && partie.get_plateau()[i+1][i+j+1] != Nul
                && partie.get_plateau()[i][i+j] != Or && partie.get_plateau()[i+1][i+j+1] != Or)
            {
                if (jetons_cible.inclus(partie.get_plateau()[i][j])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i+1][i+j+1])) {jetons_cible_temp++;}

                if (jetons_cible_temp == 2)
                {
                    //Prendre les jetons
                    return true;
                }
                if (jetons_cible_temp > jetons_cible_max)
                {
                    jetons_cible_max = jetons_cible_temp;
                    coor_jeton1 = {i, j};
                    coor_jeton2 = {i+1, i+j+1};
                }
            }
            if (partie.get_plateau()[i+j][i] != Nul && partie.get_plateau()[i+j+1][i+1] != Nul
                && partie.get_plateau()[i+j][i] != Or && partie.get_plateau()[i+j+1][i+1] != Or)
            {
                if (jetons_cible.inclus(partie.get_plateau()[i+j][j])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i+j+1][j+1])) {jetons_cible_temp++;}

                if (jetons_cible_temp == 2)
                {
                    //Prendre les jetons
                    return true;
                }
                if (jetons_cible_temp > jetons_cible_max)
                {
                    jetons_cible_max = jetons_cible_temp;
                    coor_jeton1 = {i, j};
                    coor_jeton2 = {i+j+1, i+1};
                }
            }
        }
    }
    if (jetons_cible_temp == 1)
    {
        //Prendre les jetons
        return true;
    }
    return false;
}

bool IA1::prendre_1_jetons() const
{
    int jetons_cible_max = -1; //Il est necessaire d'initialiser le compteur inférieur à 0 de manière a toujours avoir une combinaison de cases valides meme si elle ne contient aucun jeton vise
    unsigned int jetons_cible_temp = 0;
    std::array<unsigned int, 2> coor_jeton1;
    for (size_t i = 0 ; i < 4 ; i++)
    {
        for (size_t j = 0 ; j < 5 ; j++)
        {
            //Test des combinaisons horizontales
            jetons_cible_temp = 0;
            if (partie.get_plateau()[i][j] != Nul && partie.get_plateau()[i][j] != Or)
            {
                if (jetons_cible.inclus(partie.get_plateau()[i][j]))
                {
                    //Prendre les jetons
                    return true;
                }
                if (0 > jetons_cible_max)
                {
                    jetons_cible_max = 0;
                    coor_jeton1 = {i, j};
                }
            }
        }
    }
    if (jetons_cible_temp == 0)
    {
        //Prendre les jetons
        return true;
    }
    return false;
}
