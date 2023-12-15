#ifndef INTERFACECONSOLE_H
#define INTERFACECONSOLE_H

#include <vector>
#include <array>
#include <stdexcept>
#include <iostream>
#include "../Back/plateau.h"
#include "../Back/Joueur.h"
#include "../Back/partie.h"
#include "../Back/CarteRoyale.h"
#include "../Back/pyramide.h"
#include "../Back/carte_joaillerie.h"
#include "../Back/Effet.h"

class InterfaceConsole
{
public:
    void main();

protected:
    Partie& partie = Partie::get_partie();

    bool deroulement_tour();
    bool action_prendre_jetons(Joueur& joueur);
    bool action_reserver(Joueur& joueur);
    bool action_acheter(Joueur& joueur);
    void gestion_effets(CarteJoaillerie& carte);
    void gestion_effets(CarteRoyale& carte);

    void afficherPyramide() const;
     //pour afficher la pyramide dans le terminal c'est a dire afficher les cartes
    //les unes a cote des autres, on doit les afficher ligne par ligne
    void afficherCarteparligne(const CarteJoaillerie& j,int ligne,std::ostream& os) const;
    void afficherJoueur(unsigned int joueur) const;
    void afficherPlateau() const;
    void afficherJetonsPossedes(unsigned int num_joueur) const;
    void afficherPointsPrestige(unsigned int num_joueur) const;


};

#endif // INTERFACECONSOLE_H
