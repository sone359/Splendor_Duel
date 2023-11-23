#include "plateau.h"

Plateau* Plateau::plateau = nullptr;

Plateau& Plateau::get_plateau()
{
    if (plateau == nullptr)
    {
        plateau = new Plateau;
    }
    return *plateau;
}

void Plateau::delete_plateau()
{
    delete plateau;
    plateau = nullptr;
}

Plateau::~Plateau(){}

bool verifAdjacence(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3)
{
    //Vérification de l'adjacence sur une colonne
    if ((coor_jeton1[0] == coor_jeton2[0]) && (coor_jeton1[0] == coor_jeton3[0]))
    {
        if ((minLigne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton1) && (((coor_jeton2[1] == coor_jeton1[1]+1) && (coor_jeton3[1] == coor_jeton1[1]+2)) || ((coor_jeton2[1] == coor_jeton1[1]+2) && (coor_jeton3[1] == coor_jeton1[1]+1))))
        {return true;}
        if ((minLigne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton2) && (((coor_jeton1[1] == coor_jeton2[1]+1) && (coor_jeton3[1] == coor_jeton2[1]+2)) || ((coor_jeton1[1] == coor_jeton2[1]+2) && (coor_jeton3[1] == coor_jeton2[1]+1))))
        {return true;}
        if ((minLigne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton3) && (((coor_jeton1[1] == coor_jeton3[1]+1) && (coor_jeton2[1] == coor_jeton3[1]+2)) || ((coor_jeton1[1] == coor_jeton3[1]+2) && (coor_jeton2[1] == coor_jeton3[1]+1))))
        {return true;}
    }
    //Vérification de l'adjacence sur une ligne
    if ((coor_jeton1[1] == coor_jeton2[1]) && (coor_jeton1[1] == coor_jeton3[1]))
    {
        if ((minColonne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton1) && (((coor_jeton2[0] == coor_jeton1[0]+1) && (coor_jeton3[0] == coor_jeton1[0]+2)) || ((coor_jeton2[0] == coor_jeton1[0]+2) && (coor_jeton3[0] == coor_jeton1[0]+1))))
        {return true;}
        if ((minColonne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton2) && (((coor_jeton1[0] == coor_jeton2[0]+1) && (coor_jeton3[0] == coor_jeton2[0]+2)) || ((coor_jeton1[0] == coor_jeton2[0]+2) && (coor_jeton3[0] == coor_jeton2[0]+1))))
        {return true;}
        if ((minColonne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton3) && (((coor_jeton1[0] == coor_jeton3[0]+1) && (coor_jeton2[0] == coor_jeton3[0]+2)) || ((coor_jeton1[0] == coor_jeton3[0]+2) && (coor_jeton2[0] == coor_jeton3[0]+1))))
        {return true;}
    }
    //Vérification de l'adjacence sur une diagonale
    if (minColonne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton1)
    {
        if (((coor_jeton2[0] == coor_jeton1[0]+1) && (coor_jeton3[0] == coor_jeton1[0]+2)) && (((coor_jeton2[1] == coor_jeton1[1]+1) && (coor_jeton3[1] == coor_jeton1[1]+2)) || ((coor_jeton2[1] == coor_jeton1[1]-1) && (coor_jeton3[1] == coor_jeton1[1]-2))))
        {return true;}
        if (((coor_jeton2[0] == coor_jeton1[0]+2) && (coor_jeton3[0] == coor_jeton1[0]+1)) && (((coor_jeton2[1] == coor_jeton1[1]+2) && (coor_jeton3[1] == coor_jeton1[1]+1)) || ((coor_jeton2[1] == coor_jeton1[1]-2) && (coor_jeton3[1] == coor_jeton1[1]-1))))
        {return true;}
    }
    if (minColonne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton2)
    {
        if (((coor_jeton1[0] == coor_jeton2[0]+1) && (coor_jeton3[0] == coor_jeton2[0]+2)) && (((coor_jeton1[1] == coor_jeton2[1]+1) && (coor_jeton3[1] == coor_jeton2[1]+2)) || ((coor_jeton1[1] == coor_jeton2[1]-1) && (coor_jeton3[1] == coor_jeton2[1]-2))))
        {return true;}
        if (((coor_jeton1[0] == coor_jeton2[0]+2) && (coor_jeton3[0] == coor_jeton2[0]+1)) && (((coor_jeton1[1] == coor_jeton2[1]+2) && (coor_jeton3[1] == coor_jeton2[1]+1)) || ((coor_jeton1[1] == coor_jeton2[1]-2) && (coor_jeton3[1] == coor_jeton2[1]-1))))
        {return true;}
    }
    if (minColonne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton3)
    {
        if (((coor_jeton1[0] == coor_jeton3[0]+1) && (coor_jeton2[0] == coor_jeton3[0]+2)) && (((coor_jeton1[1] == coor_jeton3[1]+1) && (coor_jeton2[1] == coor_jeton3[1]+2)) || ((coor_jeton1[1] == coor_jeton3[1]-1) && (coor_jeton2[1] == coor_jeton3[1]-2))))
        {return true;}
        if (((coor_jeton1[0] == coor_jeton3[0]+2) && (coor_jeton2[0] == coor_jeton3[0]+1)) && (((coor_jeton1[1] == coor_jeton3[1]+2) && (coor_jeton2[1] == coor_jeton3[1]+1)) || ((coor_jeton1[1] == coor_jeton3[1]-2) && (coor_jeton2[1] == coor_jeton3[1]-1))))
        {return true;}
    }
    //Sinon
    return false;
}

bool verifAdjacence(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2)
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

void Plateau::ajouterJeton(Jeton jeton)
{
    size_t i;

    for (i = 0 ; i < 25 ; i++)
    {
        ordre_cases[i][0];
        if (matrice[ordre_cases[i][0]][ordre_cases[i][1]] == Nul)
        {
            matrice[ordre_cases[i][0]][ordre_cases[i][1]] = jeton;
            break;
        }
    }
    if (i==25){throw SplendorException("Le plateau est déjà plein");}
}

Jeton Plateau::retirerJeton(const std::array<unsigned int, 2>& coor_jeton)
{
     if (matrice[coor_jeton[0]][coor_jeton[1]] == Nul)
     {
         //Plus rapide et plus sûr mais n'a été ajouté qu'à partir de c++ 20 (qui ne semble pas supporté par le compilateur par défaut de Code Blocks)
         //throw SplendorException(std::format("La case ({}, {}) est vide, impossible d'y retirer un jeton", coor_jeton[0], coor_jeton[1]));
         throw SplendorException("La case (" + std::to_string(coor_jeton[0]) + ", "  + std::to_string(coor_jeton[1]) + ") est vide, impossible d'y retirer un jeton");
     }
     else
     {
         Jeton temp = matrice[coor_jeton[0]][coor_jeton[1]];
         matrice[coor_jeton[0]][coor_jeton[1]] = Nul;
         return temp;
     }
}

StockGemmes Plateau::actionRetirerJetons(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3)
{
    if (!(verifAdjacence(coor_jeton1, coor_jeton2, coor_jeton3)))
    {
        //Plus rapide et plus sûr mais n'a été ajouté qu'à partir de c++ 20 (qui ne semble pas supporté par le compilateur par défaut de Code Blocks)
        //throw SplendorException(std::format("Sélection invalide : Les cases {}, {} et {} ne sont pas adjacentes verticalement, horizontalement ou diagonalement.", coor_jeton1, coor_jeton2, coor_jeton3));
        throw SplendorException("Sélection invalide : Les cases (" + std::to_string(coor_jeton1[0]) + ", "  + std::to_string(coor_jeton1[1]) + "), (" + std::to_string(coor_jeton2[0]) + ", "  + std::to_string(coor_jeton2[1]) + ") et (" + std::to_string(coor_jeton3[0]) + ", "  + std::to_string(coor_jeton3[1]) + ") ne sont pas adjacentes verticalement, horizontalement ou diagonalement.");
    }

    StockGemmes stock;
    addStock(stock, coor_jeton1);
    addStock(stock, coor_jeton2);
    addStock(stock, coor_jeton3);

    return stock;
}

StockGemmes Plateau::actionRetirerJetons(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2)
{
    if (!(verifAdjacence(coor_jeton1, coor_jeton2)))
    {
        //Plus rapide et plus sûr mais n'a été ajouté qu'à partir de c++ 20 (qui ne semble pas supporté par le compilateur par défaut de Code Blocks)
        //throw SplendorException(std::format("Sélection invalide : Les cases {} et {} ne sont pas adjacentes verticalement, horizontalement ou diagonalement.", coor_jeton1, coor_jeton2));
        throw SplendorException("Sélection invalide : Les cases (" + std::to_string(coor_jeton1[0]) + ", "  + std::to_string(coor_jeton1[1]) + ") et (" + std::to_string(coor_jeton2[0]) + ", "  + std::to_string(coor_jeton2[1]) + ")) ne sont pas adjacentes verticalement, horizontalement ou diagonalement.");
    }

    StockGemmes stock;
    addStock(stock, coor_jeton1);
    addStock(stock, coor_jeton2);

    return stock;
}

StockGemmes Plateau::actionRetirerJetons(const std::array<unsigned int, 2>& coor_jeton1)
{
    StockGemmes stock;
    addStock(stock, coor_jeton1);
    return stock;
}

//Fonctions utilitaires
std::array<unsigned int, 2> minColonne(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3)
{
    if ((coor_jeton1[0] <= coor_jeton2[0]) && (coor_jeton1[0] <= coor_jeton3[0])) {return coor_jeton1;};
    if ((coor_jeton2[0] <= coor_jeton1[0]) && (coor_jeton2[0] <= coor_jeton3[0])) {return coor_jeton2;};
    return coor_jeton3;
}

std::array<unsigned int, 2> minLigne(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3)
{
    if ((coor_jeton1[1] <= coor_jeton2[1]) && (coor_jeton1[1] <= coor_jeton3[1])) {return coor_jeton1;};
    if ((coor_jeton2[1] <= coor_jeton1[1]) && (coor_jeton2[1] <= coor_jeton3[1])) {return coor_jeton2;};
    return coor_jeton3;
}

void Plateau::addStock(StockGemmes& stock, const std::array<unsigned int, 2>& coor_jeton)
{
    if (matrice[coor_jeton[0]][coor_jeton[1]] == Or)
    {
        //Plus rapide et plus sûr mais n'a été ajouté qu'à partir de c++ 20 (qui ne semble pas supporté par le compilateur par défaut de Code Blocks)
        //throw SplendorException(std::format("Case {} invalide : L'or ne peut pas être retiré avec cette action", coor_jeton));
        throw SplendorException("Case (" + std::to_string(coor_jeton[0]) + ", "  + std::to_string(coor_jeton[1]) + ") invalide : L'or ne peut pas être retiré avec cette action");
    }
    Jeton jeton_retire = retirerJeton(coor_jeton);
    //La valeur Nul est testée et déclare une erreur dans retirerJeton
    switch (jeton_retire)
    {
    case Bleu:
        stock.set_Bleu(stock.get_Bleu() + 1);
        break;
    case Vert:
        stock.set_Vert(stock.get_Vert() + 1);
        break;
    case Blanc:
        stock.set_Blanc(stock.get_Blanc() + 1);
        break;
    case Rouge:
        stock.set_Rouge(stock.get_Rouge() + 1);
        break;
    case Noir:
        stock.set_Noir(stock.get_Noir() + 1);
        break;
    case Perle:
        stock.set_Perle(stock.get_Perle() + 1);
        break;
    }
}
