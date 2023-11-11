#include <iostream>

#include "stockGemmes.h"
#include "plateau.h"
#include "interfaceConsole.h"


using namespace std;

int main()
{
    //Tests concernant StockGemmes
    StockGemmes stockTest;
    cout << stockTest.get_Blanc() << endl;
    StockGemmes stockTest2(1, 2, 3, 4, 2, 1);
    cout << stockTest2.get_Blanc() << endl;
    //Tests concernant Plateau
    cout << minLigne({0, 5}, {1, 4}, {2, 2})[0] << endl;
    cout << minColonne({6, 5}, {1, 3}, {2, 2})[0] << endl;
    cout << verifAdjacence({0, 0}, {1, 1}, {2, 2}) << endl;
    cout << verifAdjacence({0, 0}, {1, 1}, {3, 3}) << endl;
    cout << verifAdjacence({0, 0}, {0, 1}, {0, 2}) << endl;
    cout << verifAdjacence({3, 1}, {1, 1}, {2, 1}) << endl;
    cout << verifAdjacence({0, 0}, {1, 1}) << endl;
    cout << verifAdjacence({0, 0}, {0, 1}) << endl;
    cout << verifAdjacence({0, 0}, {1, 0}) << endl;
    cout << verifAdjacence({3, 1}, {1, 1}) << endl;
    cout << verifAdjacence({2, 2}, {1, 1}) << endl;
    Plateau& pl = Plateau::get_plateau();
    cout << pl[0][0] << endl;

    InterfaceConsole ic;
    ic.afficherPlateau();
    pl.ajouterJeton(Bleu);
    ic.afficherPlateau();
    pl.ajouterJeton(Vert);
    ic.afficherPlateau();
    pl.ajouterJeton(Blanc);
    ic.afficherPlateau();
    pl.ajouterJeton(Rouge);
    ic.afficherPlateau();
    pl.ajouterJeton(Noir);
    ic.afficherPlateau();
    pl.retirerJeton({2, 2});
    ic.afficherPlateau();
    pl.actionRetirerJetons({1, 1}, {1, 2}, {1, 3});
    ic.afficherPlateau();

    return 0;
}
