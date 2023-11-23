#include <iostream>

#include "Back/stockGemmes.h"
#include "Back/plateau.h"
#include "Console/interfaceConsole.h"


using namespace std;

int main()
{
    Plateau& pl = Plateau::get_plateau();
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
