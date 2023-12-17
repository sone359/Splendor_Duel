#include "plateau.h"

Plateau* Plateau::plateau = nullptr;

Plateau* Plateau::get_plateau()
{
    if (plateau == nullptr)
    {
        plateau = new Plateau;
    }
    return plateau;
}

void Plateau::delete_plateau()
{
    delete plateau;
    plateau = nullptr;
}

Plateau::~Plateau(){}

std::array<unsigned int, 2> Plateau::ajouterJeton(Jeton jeton)
{
    if (nbCasesVides==0){throw SplendorException("Le plateau est deja plein");}

    size_t i;

    for (i = 0 ; i < 25 ; i++)
    {
        ordre_cases[i][0];
        if (matrice[ordre_cases[i][0]][ordre_cases[i][1]] == Nul)
        {
            matrice[ordre_cases[i][0]][ordre_cases[i][1]] = jeton;
            nbCasesVides--;
            break;
        }
    }
    return ordre_cases[i];
}

Jeton Plateau::retirerJeton(const std::array<unsigned int, 2>& coor_jeton)
{
     if ((coor_jeton[0] > 25) || (coor_jeton[1] >25))
     {
         //Plus rapide et plus s�r mais n'a �t� ajout� qu'� partir de c++ 20 (qui ne semble pas support� par le compilateur par d�faut de Code Blocks)
         //throw SplendorException(std::format("La case ({}, {}) n'existe pas, impossible d'y retirer un jeton", coor_jeton[0], coor_jeton[1]));
         throw SplendorException("La case (" + std::to_string(coor_jeton[0]) + ", "  + std::to_string(coor_jeton[1]) + ") n'existe pas, impossible d'y retirer un jeton");
     }
     if (matrice[coor_jeton[0]][coor_jeton[1]] == Nul)
     {
         //Plus rapide et plus s�r mais n'a �t� ajout� qu'� partir de c++ 20 (qui ne semble pas support� par le compilateur par d�faut de Code Blocks)
         //throw SplendorException(std::format("La case ({}, {}) est vide, impossible d'y retirer un jeton", coor_jeton[0], coor_jeton[1]));
         throw SplendorException("La case (" + std::to_string(coor_jeton[0]) + ", "  + std::to_string(coor_jeton[1]) + ") est vide, impossible d'y retirer un jeton");
     }

     Jeton temp = matrice[coor_jeton[0]][coor_jeton[1]];
     matrice[coor_jeton[0]][coor_jeton[1]] = Nul;
     nbCasesVides++;
     return temp;
}

StockGemmes Plateau::actionRetirerJetons(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3)
{
    //Verification de l'adjacence des cases
    if (!(verifAdjacence(coor_jeton1, coor_jeton2, coor_jeton3)))
    {
        //Plus rapide et plus s�r mais n'a �t� ajout� qu'� partir de c++ 20 (qui ne semble pas support� par le compilateur par d�faut de Code Blocks)
        //throw SplendorException(std::format("S�lection invalide : Les cases {}, {} et {} ne sont pas adjacentes verticalement, horizontalement ou diagonalement.", coor_jeton1, coor_jeton2, coor_jeton3));
        throw SplendorException("Selection invalide : Les cases (" + std::to_string(coor_jeton1[0]) + ", "  + std::to_string(coor_jeton1[1]) + "), (" + std::to_string(coor_jeton2[0]) + ", "  + std::to_string(coor_jeton2[1]) + ") et (" + std::to_string(coor_jeton3[0]) + ", "  + std::to_string(coor_jeton3[1]) + ") ne sont pas adjacentes verticalement, horizontalement ou diagonalement.");
    }

    //Verification que les cases ne correspondent pas a un jeton Or (La valeur Nul est testee et declare une erreur dans retirerJeton)
    if (matrice[coor_jeton1[0]][coor_jeton1[1]] == Or)
    {
        //Plus rapide et plus sur mais n'a ete ajoute qu'a partir de c++ 20 (qui ne semble pas supporte par le compilateur par d�faut de Code Blocks)
        //throw SplendorException(std::format("Case {} invalide : L'or ne peut pas etre retire avec cette action", coor_jeton));
        throw SplendorException("Case (" + std::to_string(coor_jeton1[0]) + ", "  + std::to_string(coor_jeton1[1]) + ") invalide : L'or ne peut pas etre retire avec cette action");
    }
    if (matrice[coor_jeton2[0]][coor_jeton2[1]] == Or)
    {
        //Plus rapide et plus s�r mais n'a �t� ajout� qu'� partir de c++ 20 (qui ne semble pas support� par le compilateur par d�faut de Code Blocks)
        //throw SplendorException(std::format("Case {} invalide : L'or ne peut pas �tre retir� avec cette action", coor_jeton));
        throw SplendorException("Case (" + std::to_string(coor_jeton2[0]) + ", "  + std::to_string(coor_jeton2[1]) + ") invalide : L'or ne peut pas etre retire avec cette action");
    }
    if (matrice[coor_jeton3[0]][coor_jeton3[1]] == Or)
    {
        //Plus rapide et plus s�r mais n'a ete ajoute qu'a partir de c++ 20 (qui ne semble pas support� par le compilateur par d�faut de Code Blocks)
        //throw SplendorException(std::format("Case {} invalide : L'or ne peut pas �tre retir� avec cette action", coor_jeton));
        throw SplendorException("Case (" + std::to_string(coor_jeton3[0]) + ", "  + std::to_string(coor_jeton3[1]) + ") invalide : L'or ne peut pas etre retire avec cette action");
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
        //Plus rapide et plus s�r mais n'a �t� ajout� qu'� partir de c++ 20 (qui ne semble pas support� par le compilateur par d�faut de Code Blocks)
        //throw SplendorException(std::format("S�lection invalide : Les cases {} et {} ne sont pas adjacentes verticalement, horizontalement ou diagonalement.", coor_jeton1, coor_jeton2));
        throw SplendorException("Selection invalide : Les cases (" + std::to_string(coor_jeton1[0]) + ", "  + std::to_string(coor_jeton1[1]) + ") et (" + std::to_string(coor_jeton2[0]) + ", "  + std::to_string(coor_jeton2[1]) + ")) ne sont pas adjacentes verticalement, horizontalement ou diagonalement.");
    }

    //Verification que les cases ne sorrespondent � pas � un jeton Or (La valeur Nul est test�e et d�clare une erreur dans retirerJeton)
    if (matrice[coor_jeton1[0]][coor_jeton1[1]] == Or)
    {
        //Plus rapide et plus s�r mais n'a �t� ajout� qu'� partir de c++ 20 (qui ne semble pas support� par le compilateur par d�faut de Code Blocks)
        //throw SplendorException(std::format("Case {} invalide : L'or ne peut pas �tre retir� avec cette action", coor_jeton));
        throw SplendorException("Case (" + std::to_string(coor_jeton1[0]) + ", "  + std::to_string(coor_jeton1[1]) + ") invalide : L'or ne peut pas etre retire avec cette action");
    }
    if (matrice[coor_jeton2[0]][coor_jeton2[1]] == Or)
    {
        //Plus rapide et plus s�r mais n'a �t� ajout� qu'� partir de c++ 20 (qui ne semble pas support� par le compilateur par d�faut de Code Blocks)
        //throw SplendorException(std::format("Case {} invalide : L'or ne peut pas �tre retir� avec cette action", coor_jeton));
        throw SplendorException("Case (" + std::to_string(coor_jeton2[0]) + ", "  + std::to_string(coor_jeton2[1]) + ") invalide : L'or ne peut pas etre retire avec cette action");
    }

    StockGemmes stock;
    addStock(stock, coor_jeton1);
    addStock(stock, coor_jeton2);

    return stock;
}

StockGemmes Plateau::actionRetirerJetons(const std::array<unsigned int, 2>& coor_jeton1)
{
    if (matrice[coor_jeton1[0]][coor_jeton1[1]] == Or)
    {
        //Plus rapide et plus s�r mais n'a �t� ajout� qu'� partir de c++ 20 (qui ne semble pas support� par le compilateur par d�faut de Code Blocks)
        //throw SplendorException(std::format("Case {} invalide : L'or ne peut pas �tre retir� avec cette action", coor_jeton));
        throw SplendorException("Case (" + std::to_string(coor_jeton1[0]) + ", "  + std::to_string(coor_jeton1[1]) + ") invalide : L'or ne peut pas etre retire avec cette action");
    }
    StockGemmes stock;
    addStock(stock, coor_jeton1);
    return stock;
}

StockGemmesOr Plateau::actionRetirerJetonsOr(const std::array<unsigned int, 2>& coor_jeton1)
{
    if (matrice[coor_jeton1[0]][coor_jeton1[1]] != Or)
    {
        throw SplendorException("Case (" + std::to_string(coor_jeton1[0]) + ", "  + std::to_string(coor_jeton1[1]) + ") invalide : Cette action est prévue pour les jetons or.");
    }
    StockGemmesOr stock;
    addStock(stock, coor_jeton1);
    return stock;
}

//Fonctions utilitaires
bool verifAdjacence(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3)
{
    //V�rification de l'adjacence sur une colonne
    if ((coor_jeton1[0] == coor_jeton2[0]) && (coor_jeton1[0] == coor_jeton3[0]))
    {
        if ((minLigne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton1) && (((coor_jeton2[1] == coor_jeton1[1]+1) && (coor_jeton3[1] == coor_jeton1[1]+2)) || ((coor_jeton2[1] == coor_jeton1[1]+2) && (coor_jeton3[1] == coor_jeton1[1]+1))))
        {return true;}
        if ((minLigne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton2) && (((coor_jeton1[1] == coor_jeton2[1]+1) && (coor_jeton3[1] == coor_jeton2[1]+2)) || ((coor_jeton1[1] == coor_jeton2[1]+2) && (coor_jeton3[1] == coor_jeton2[1]+1))))
        {return true;}
        if ((minLigne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton3) && (((coor_jeton1[1] == coor_jeton3[1]+1) && (coor_jeton2[1] == coor_jeton3[1]+2)) || ((coor_jeton1[1] == coor_jeton3[1]+2) && (coor_jeton2[1] == coor_jeton3[1]+1))))
        {return true;}
    }
    //V�rification de l'adjacence sur une ligne
    if ((coor_jeton1[1] == coor_jeton2[1]) && (coor_jeton1[1] == coor_jeton3[1]))
    {
        if ((minColonne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton1) && (((coor_jeton2[0] == coor_jeton1[0]+1) && (coor_jeton3[0] == coor_jeton1[0]+2)) || ((coor_jeton2[0] == coor_jeton1[0]+2) && (coor_jeton3[0] == coor_jeton1[0]+1))))
        {return true;}
        if ((minColonne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton2) && (((coor_jeton1[0] == coor_jeton2[0]+1) && (coor_jeton3[0] == coor_jeton2[0]+2)) || ((coor_jeton1[0] == coor_jeton2[0]+2) && (coor_jeton3[0] == coor_jeton2[0]+1))))
        {return true;}
        if ((minColonne(coor_jeton1, coor_jeton2, coor_jeton3) == coor_jeton3) && (((coor_jeton1[0] == coor_jeton3[0]+1) && (coor_jeton2[0] == coor_jeton3[0]+2)) || ((coor_jeton1[0] == coor_jeton3[0]+2) && (coor_jeton2[0] == coor_jeton3[0]+1))))
        {return true;}
    }
    //V�rification de l'adjacence sur une diagonale
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
    //V�rification de l'adjacence sur une colonne
    if ((coor_jeton1[0] == coor_jeton2[0]) && ((coor_jeton2[1] == coor_jeton1[1]+1) || (coor_jeton2[1] == coor_jeton1[1]-1)))
    {return true;}
    //V�rification de l'adjacence sur une ligne
    if ((coor_jeton1[1] == coor_jeton2[1]) && ((coor_jeton2[0] == coor_jeton1[0]+1) || (coor_jeton2[0] == coor_jeton1[0]-1)))
    {return true;}
    //V�rification de l'adjacence sur une diagonale
    if ((coor_jeton2[0] == coor_jeton1[0]+1) && ((coor_jeton2[1] == coor_jeton1[1]+1) || (coor_jeton2[1] == coor_jeton1[1]-1)))
    {return true;}
    if ((coor_jeton2[0] == coor_jeton1[0]-1) && ((coor_jeton2[1] == coor_jeton1[1]+1) || (coor_jeton2[1] == coor_jeton1[1]-1)))
    {return true;}
    //Sinon
    return false;
}

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
    Jeton jeton_retire = retirerJeton(coor_jeton);
    stock.ajouter_jeton(jeton_retire);
}

std::string Plateau::sauvegarder()const{
    std::stringstream s;
    for(std::array<unsigned int, 2> coord : ordre_cases){
        s<<matrice[coord[0]][coord[1]]<<",";
    }
    s<<';';
    s<<nbCasesVides;
    return s.str();
}

Plateau* Plateau::get_plateau(std::string line){
    if (plateau == nullptr)
    {
        plateau = new Plateau(line);
    }
    return plateau;
}


Plateau::Plateau(std::string line){
    //std::cout<<"\n------LECTURE PLAT----------\n"<<line;
    std::istringstream iss(line);
    //std::cout<<"line"<<line<<'\n';
    std::string token,token1;
    std::getline(iss, token, ';');
    //std::cout<<"token"<<token<<'\n';
    std::istringstream iss1(token);
    for(std::array<unsigned int, 2> coord : ordre_cases){
        if (std::getline(iss1, token1, ',')) {
            //std::cout<<"token1"<<token1<<'\n';
            matrice[coord[0]][coord[1]]=Jeton(stoi(token1));
        }
    }
    std::getline(iss,token,';');
    nbCasesVides=stoi(token);
}