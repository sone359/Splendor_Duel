#ifndef INTERFACECONSOLE_H
#define INTERFACECONSOLE_H

#include "../Back/plateau.h"
#include "../Back/Joueur.h"
#include "../Back/partie.h"
#include <iostream>

class InterfaceConsole
{
public:
    void deroulement_tour();
    //Affichages publics pour les tests mais destinés à devenir private
    void afficher_plateau();
    void afficher_jetons_possedes(unsigned int num_joueur);
    void afficher_pyramide();

private:
    Partie& partie = Partie::get_partie();

};

#endif // INTERFACECONSOLE_H
