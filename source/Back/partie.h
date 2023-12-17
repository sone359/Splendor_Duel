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

    //Methodes statiques suivant le design pattern Singleton
    static Partie* get_partie();
    static Partie* get_partie(std::string s);
    static void delete_partie();

    std::vector<CarteJoaillerie> cartes;
    int lire_fichier(const char* fichier);

    void initCartes();

    unsigned int joueur_actif()const {return (tour%2)+1;};
    unsigned int joueur_adverse()const {return (joueur_actif()+1)%2+1;};
    void prend_privilege(Joueur& joueur);
    void utilise_privilege(Joueur& joueur, unsigned int colonne, unsigned int ligne);
    std::vector<std::array<unsigned int, 2>> remplir_plateau(Joueur& joueur);
    std::array<unsigned int, 2> remplir_case();
    CarteJoaillerie& acheter_carte(Joueur& joueur, int niv, int colonne);//colonne correspond à la position de la carte de gauche à droite 1-3,1,4 ou 1-5 en fct du niveau
    CarteJoaillerie& acheter_carte_reservee(Joueur& joueur,unsigned int num);
    void reserver_carte(Joueur& joueur, int niv, int colonne);//colonne correspond à la position de la carte de gauche à droite 1-3,1,4 ou 1-5 en fct du niveau OU 0 POUR LA PIOCHE
    void retirer_jetons(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3);
    void retirer_jetons(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2);
    void retirer_jetons(const std::array<unsigned int, 2>& coor_jeton);
    void retirer_jetons_or(const std::array<unsigned int, 2>& coor_jeton);
    void remettre_jeton(Jeton jeton);
    void ajouter_rejouer(){effet_rejouer++;};
    void voler(Joueur& joueur1, Joueur& joueur2, Jeton jeton);
    int fin_tour();
    int sauvegarder()const;
    std::string getTime()const;
    void chargerPartie(const std::string chemin);
    
    //Getters
    Plateau& get_plateau() const {return plateau;};
    Sac& get_sac() const {return sac;};
    Pyramide& get_pyramide() const {return *pyramide;};
    Joueur& get_joueur(unsigned int num_joueur);
    unsigned int get_tour() const {return tour;};
    unsigned int get_privileges_disponibles() const {return privileges_disponibles;};

    //Pas de setters
    Partie(std::string s);
    ~Partie();

protected:
    static Partie* partie;
    Partie();
    Partie(const Partie&);
    //virtual ~Partie();
    void operator=(const Partie&);

private:
    Plateau& plateau = Plateau::get_plateau();
    Sac& sac = Sac::get_sac();
    Pyramide* pyramide;// = Pyramide::getInstance();
    Joueur joueur1;
    Joueur joueur2;
    unsigned int tour = 0;
    std::vector<CarteRoyale> cartesRoyales;
    unsigned int privileges_disponibles = 3;
    unsigned int effet_rejouer = 0;
};

#endif
