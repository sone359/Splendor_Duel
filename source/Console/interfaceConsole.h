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

class InterfaceConsole
{
public:
    void afficherPyramide() const;
    //pour afficher la pyramide dans le terminal aka afficher les cartes
    //les unes à coté des autres on doit les afficher ligne par ligne
    void afficherCarteparligne(const CarteJoaillerie& j,int ligne,std::ostream& os)const;
    void afficherPlateau() const;
    void afficherJetonsPossedes(Joueur& joueur)const;

private:
    Plateau& plateau = Plateau::get_plateau();
    Partie& partie = Partie::get_partie();
};

#endif // INTERFACECONSOLE_H
