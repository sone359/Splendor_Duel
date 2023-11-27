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
    game.retirer_jetons(game.get_joueur(1), {1, 1}, {1, 2}, {1, 3});
    ic.afficherPlateau();
    ic.afficherJetonsPossedes(game.get_joueur(1));
    game.retirer_jetons(game.get_joueur(2), {0, 0}, {2, 0}, {1, 0});
    ic.afficherPlateau();
    ic.afficherJetonsPossedes(game.get_joueur(2));
    game.remplir_plateau(game.get_joueur(1));
    ic.afficherPlateau();
    printf("\n%d",game.get_joueur(1).getNbPrivileges());
    printf("\n%d",game.get_joueur(2).getNbPrivileges());

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
