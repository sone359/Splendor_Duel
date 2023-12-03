#ifndef PARTIE_H
#define PARTIE_H

#include <vector>
#include <array>
#include <stdexcept>
#include <iostream>
#include "plateau.h"
#include "sac.h"
#include "Joueur.h"
#include "CarteRoyale.h"
#include "pyramide.h"
#include "carte_joaillerie.h"


class Partie
{
public :

    //M�thodes statiques suivant le design pattern Singleton
    static Partie& get_partie();
    static void delete_partie();

    std::vector<CarteJoaillerie> cartes;


    void initCartes();

    unsigned int joueur_actif() {return (tour%2)+1;};
    void prend_privilege(Joueur& joueur);
    std::vector<std::array<unsigned int, 2>> remplir_plateau(Joueur& joueur);
    std::array<unsigned int, 2> remplir_case();
    void retirer_jetons(Joueur& joueur, const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3);
    void retirer_jetons(Joueur& joueur, const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2);
    void retirer_jetons(Joueur& joueur, const std::array<unsigned int, 2>& coor_jeton);
    void acheter_carte(int numjoueur, int niv, int colonne);//colonne correspond à la position de la carte de gauche à droite 1-3,1,4 ou 1-5 en fct du niveau
    void reserver_carte(int numjoueur, int niv, int colonne);//colonne correspond à la position de la carte de gauche à droite 1-3,1,4 ou 1-5 en fct du niveau OU 0 POUR LA PIOCHE

    //Getters
    Pyramide& get_pyramide()const{return *pyramide;}
    Plateau& get_plateau() const {return plateau;};
    Sac& get_sac() const {return sac;};
    Joueur& get_joueur(unsigned int num_joueur);
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
    Pyramide* pyramide;
    Sac& sac = Sac::get_sac();
    Joueur joueur1;
    Joueur joueur2;
    unsigned int tour = 0;
    std::vector<CarteRoyale> cartesRoyales;
    unsigned int privileges_disponibles = 3;
};

#endif
