#ifndef INTERFACECONSOLE_H
#define INTERFACECONSOLE_H

#include "../Back/plateau.h"
#include "../Back/Joueur.h"
#include "../Back/partie.h"
#include <iostream>

class InterfaceConsole
{
public:
    void main();
    int deroulement_tour();
    bool action_prendre_jetons(Joueur& joueur);
    bool action_reserver(Joueur& joueur);
    bool action_acheter(Joueur& joueur);

    //Affichages publics pour les tests mais destinés à devenir private
    void afficher_plateau();
    void afficher_jetons_possedes(unsigned int num_joueur);
    void afficher_pyramide();

private:
    Partie& partie = Partie::get_partie();

};

#endif // INTERFACECONSOLE_H
