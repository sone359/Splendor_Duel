#include <iostream>
#include <vector>

#include "Back/stockGemmes.h"
#include "Back/plateau.h"
#include "Back/sac.h"
#include "Back/partie.h"
#include "Console/interfaceConsole.h"


using namespace std;

int main()
{
    //std::cout<<"youhou";
    //std::vector<CarteJoaillerie> cartes(67,CarteJoaillerie());
    //cartes[0].setNiveau(1);
    //std::cout<<cartes[0].get_niveau();
    //std::cout<<"youhou";

    //std::cout<<"youhou";
    //Pyramide::getInstance();
    //std::cout<<"youhou";
    Partie& game = Partie::get_partie();
    Pyramide::getInstance()->afficherPyramide();

    InterfaceConsole ic;
    ic.deroulement_tour();
    //ic.afficher_pyramide();
    ic.afficher_plateau();
    game.retirer_jetons(game.get_joueur(1), {1, 1}, {1, 2}, {1, 3});
    ic.afficher_plateau();
    ic.afficher_jetons_possedes(1);
    game.retirer_jetons(game.get_joueur(2), {0, 0}, {2, 0}, {1, 0});
    ic.afficher_plateau();
    ic.afficher_jetons_possedes(2);
    game.remplir_plateau(game.get_joueur(1));
    ic.afficher_plateau();


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
