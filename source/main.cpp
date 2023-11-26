#include <iostream>

#include "Back/stockGemmes.h"
#include "Back/plateau.h"
#include "Back/sac.h"
#include "Back/partie.h"
#include "Console/interfaceConsole.h"


using namespace std;

int main()
{
    Partie& game = Partie::get_partie();
    InterfaceConsole ic;

    ic.afficherPlateau();
    /*pl.ajouterJeton(sac.retirer_jeton());
    ic.afficherPlateau();
    pl.ajouterJeton(sac.retirer_jeton());
    ic.afficherPlateau();
    pl.ajouterJeton(sac.retirer_jeton());
    ic.afficherPlateau();
    pl.ajouterJeton(sac.retirer_jeton());
    ic.afficherPlateau();
    pl.ajouterJeton(sac.retirer_jeton());
    ic.afficherPlateau();
    pl.retirerJeton({2, 2});
    ic.afficherPlateau();
    pl.actionRetirerJetons({1, 1}, {1, 2}, {1, 3});
    ic.afficherPlateau();*/

    return 0;
}
