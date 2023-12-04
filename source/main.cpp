#include <iostream>
#include <vector>

#include "Back/stockGemmes.h"
#include "Back/plateau.h"
#include "Back/sac.h"
#include "Back/partie.h"
#include "Back/Joueur.h"
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
    //CarteJoaillerie c=game.get_pyramide().acheterCarteJoaillerie(1,1);
    //game.get_pyramide().afficherPyramide();
    //std::cout<<"carte piochée : "<<c<<std::endl;
    //c=game.get_pyramide().reserverCarteJoaillerie(2,1);
    //game.get_pyramide().afficherPyramide();
    //std::cout<<"carte piochée : "<<c<<std::endl;
    //std::cout<<"JOUEUR 1"<<game.get_joueur(1);
    //game.acheter_carte(1,1,1);
    //std::cout<<"JOUEUR 1"<<game.get_joueur(1);
    //game.reserver_carte(1,1,1);
    //std::cout<<"JOUEUR 1"<<game.get_joueur(1);
    //game.reserver_carte(1,1,0);
    //std::cout<<"JOUEUR 1"<<game.get_joueur(1);
    //game.acheter_carte(1,1,0);
    //std::cout<<"JOUEUR 1"<<game.get_joueur(1);
    game.lire_fichier("../data/info_cartejoaillerie");
    //game.get_joueur(1).addCartesJoailleriesPossedees(c);
    //std::cout<<"j1 a mtn\n"<<game.get_joueur(1).getCartesJoailleriesPossedees()[0];
    //InterfaceConsole ic;

    //ic.afficherPlateau();
    //game.retirer_jetons(game.get_joueur(1), {1, 1}, {1, 2}, {1, 3});
    //ic.afficherPlateau();
    //ic.afficherJetonsPossedes(game.get_joueur(1));
    //game.retirer_jetons(game.get_joueur(2), {0, 0}, {2, 0}, {1, 0});
    //ic.afficherPlateau();
    //ic.afficherJetonsPossedes(game.get_joueur(2));
    //game.remplir_plateau(game.get_joueur(1));
    //ic.afficherPlateau();
    
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
