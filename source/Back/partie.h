#ifndef PARTIE_H
#define PARTIE_H

#include <vector>
#include <array>
#include <stdexcept>
#include "plateau.h"
#include "sac.h"
#include "joueur.h"
#include "CarteRoyale.h"
#include "pyramide.h"
#include "carte_joaillerie.h"


class Partie
{
public :

    //Méthodes statiques suivant le design pattern Singleton
    static Partie& get_partie();
    static void delete_partie();

    CarteJoaillerie * cartes[67];

    void initPyramide(){
        Pyramide::initialiser(cartes);
        //Pyramide::getInstance()->afficherPyramide();
    }

    std::vector<std::array<unsigned int, 2>> remplir_plateau();
    std::array<unsigned int, 2> remplir_case();
    unsigned int joueur_actif() {return (tour%2)+1;};

    //Getters
    Plateau& get_plateau() const {return plateau;};
    Sac& get_sac() const {return sac;};
    Joueur get_joueur(unsigned int num_joueur) const ;
    unsigned int get_tour() const {return tour;};
    unsigned int get_privileges_disponibles() const {return privileges_disponibles;};

    //Pas de setters

protected:
    static Partie* partie;
    Partie();
    Partie(const Partie&);
    virtual ~Partie();
    void operator=(const Partie&);

private:
    Plateau& plateau = Plateau::get_plateau();
    Sac& sac = Sac::get_sac();
    Joueur joueur1;
    Joueur joueur2 = Joueur(1);
    unsigned int tour = 0;
    std::vector<CarteRoyale> cartesRoyales;
    unsigned int privileges_disponibles = 3;
};

#endif
