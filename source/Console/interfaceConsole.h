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
#include "../Back/IA1.h"

class InterfaceConsole
{
public:
    InterfaceConsole();

protected:
    bool deroulement_tour();
    bool action_prendre_jetons(Joueur& joueur);
    bool action_reserver(Joueur& joueur);
    bool action_acheter(Joueur& joueur);
    void gestion_effets(CarteJoaillerie& carte);
    void gestion_effets(CarteRoyale& carte);

    void afficherPyramide() const;
     //pour afficher la pyramide dans le terminal c'est a dire afficher les cartes
    //les unes a cote des autres on doit les afficher ligne par ligne
    void afficherCarteparligne(const CarteJoaillerie& j,unsigned int ligne,std::ostream& os)const;
    void afficherJoueur(unsigned int joueur) const;
    void afficherPlateau() const;
    void afficherJetonsPossedes(unsigned int num_joueur) const;
    void afficherBonus(unsigned int num_joueur) const;
    void afficherPrestige(unsigned int num_joueur) const;
    void afficherPlateauparLigne(unsigned int ligne, std::ostream& os) const;
    void afficherPyramideparLigne(unsigned int ligne, std::ostream& os) const;
    void afficherConsole() const;
    void titre()const;
    void afficherReglesparLigne(unsigned int ligne, std::ostream& os)const;
    void afficherCarteRoyaleparLigne(unsigned int ligne, unsigned int carte,std::ostream& os)const;

private:
    Partie * partie;
    IA1 IA;
};

#endif // INTERFACECONSOLE_H
