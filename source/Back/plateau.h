#ifndef PLATEAU_H
#define PLATEAU_H

#include <array>

#include "../tools.h"
#include "stockGemmes.h"

class Plateau
{
public :

    //M�thodes statiques suivant le design pattern Singleton
    static Plateau* get_plateau();
    static Plateau* get_plateau(std::string line);
    static void delete_plateau();

    std::array<unsigned int, 2> ajouterJeton(Jeton jeton);
    Jeton retirerJeton(const std::array<unsigned int, 2>& coor_jeton); //Peut renvoyer de l'or et est ainsi utilis� dans la prise de gemmes comme dans la r�servation.
    StockGemmes actionRetirerJetons(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3);
    StockGemmes actionRetirerJetons(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2);
    StockGemmes actionRetirerJetons(const std::array<unsigned int, 2>& coor_jeton1);
    StockGemmesOr actionRetirerJetonsOr(const std::array<unsigned int, 2>& coor_jeton1);
    std::string sauvegarder()const;

    //Getter
    unsigned int get_nbCasesVides() const {return nbCasesVides;};

    //Op�rateurs surcharg�s
    const std::array<Jeton, 5> operator[](unsigned int colonne){return matrice[colonne];};//R�flexion possible � l'avenir : Est-ce vraiment utile ? Et est-ce que l'avoir en public ne met pas en p�ril l'encapsulation ?

protected:
    static Plateau* plateau;
    Plateau() = default;
    explicit Plateau(std::string s);
    Plateau(const Plateau&);
    virtual ~Plateau();
    void operator=(const Plateau&);

private:
    std::array<std::array<Jeton, 5>, 5> matrice = {Nul};
    const std::array<std::array<unsigned int, 2>, 25> ordre_cases = {{{2, 2}, {2, 3}, {1, 3}, {1, 2}, {1, 1}, {2, 1}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {2, 4}, {1, 4}, {0, 4}, {0, 3}, {0, 2}, {0, 1}, {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}}};
    unsigned int nbCasesVides = 25;

    //M�thodes utilitaires
    void addStock(StockGemmes& stock, const std::array<unsigned int, 2>& coor_jeton);
};

//Fonctions utilitaires li�es � Plateau
bool verifAdjacence(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3);
bool verifAdjacence(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2);
std::array<unsigned int, 2> minColonne(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3);
std::array<unsigned int, 2> minLigne(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3);

#endif
