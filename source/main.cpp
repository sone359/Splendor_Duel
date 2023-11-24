#include <iostream>

#include "Back/stockGemmes.h"
#include "Back/plateau.h"
#include "Back/sac.h"
#include "Console/interfaceConsole.h"


using namespace std;

int main()
{
    Plateau& pl = Plateau::get_plateau();
    Sac& sac = Sac::get_sac();
    InterfaceConsole ic;

    for(unsigned int i = 0 ; i < 4 ; i++){
        sac.ajouter_jeton(Bleu);
        sac.ajouter_jeton(Vert);
        sac.ajouter_jeton(Blanc);
        sac.ajouter_jeton(Rouge);
        sac.ajouter_jeton(Noir);
    }
    sac.ajouter_jeton(Perle);
    sac.ajouter_jeton(Perle);
    for(unsigned int i = 0 ; i < 3 ; i++){
        sac.ajouter_jeton(Or);
    }


    ic.afficherPlateau();
    pl.ajouterJeton(sac.retirer_jeton());
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
    ic.afficherPlateau();

    return 0;
}
