#ifndef INTERFACECONSOLE_H
#define INTERFACECONSOLE_H

#include "../Back/plateau.h"
#include "../Back/Joueur.h"

class InterfaceConsole
{
public:
    void afficherPlateau();
    void afficherJetonsPossedes(Joueur& joueur);

private:
    Plateau& plateau = Plateau::get_plateau();

};

#endif // INTERFACECONSOLE_H
