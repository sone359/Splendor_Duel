#ifndef PYRAMIDE_H
#define PYRAMIDE_H

#include <vector>
#include <stack>
#include <iostream>

#include "carte_joaillerie.h"

class Pyramide {
    private :
    //3 stacks de CarteJoailleries
    std::stack<CarteJoaillerie> Niveau1;
    std::stack<CarteJoaillerie> Niveau2;
    std::stack<CarteJoaillerie> Niveau3;

    //3 lignes
    std::vector<CarteJoaillerie> ligne1;
    std::vector<CarteJoaillerie> ligne2;
    std::vector<CarteJoaillerie> ligne3;
    //singleton dc constructeur
    Pyramide(std::vector<CarteJoaillerie > jeu);
    //constructeur de recop, assignment op
    void operator=(Pyramide& p)=delete;
    Pyramide(Pyramide& p)=delete;
    //et instance
    static Pyramide *  instance;
    //utiles pour l'affichage quand il y a moins de cartes/ligne
    unsigned int cartesRestantes1=5,cartesRestantes2=4,cartesRestantes3=3;
    //ENLEVER//pour pouvoir separer le constructeur de getInstance pcq il prend des arguments un bool permet de verif l'init
    //ENLEVERbool init=false;

    public :
    //instance accessible par Partie
    static Pyramide* getInstance();
    static Pyramide* getInstance(std::vector<CarteJoaillerie> cartes);
    //acheter retourne la CarteJoaillerie achetée et la remplace ds la pyramide avec piocher
    CarteJoaillerie acheterCarteJoaillerie(int numeroLigne, int numeroColonne);
    //reserver retourne la CarteJoaillerie réservée et la remplace ds la pyramide avec piocher
    CarteJoaillerie reserverCarteJoaillerie(int numeroLigne, int numeroColonne);
    //piocher prend une CarteJoaillerie du bon stack et la met à la place donnée
    void piocherCarteJoaillerie(int numeroLigne, int numeroColonne);
    //appelee par acheter et reserver, recuperer renvoit la carte à la place donnée
    CarteJoaillerie recupererCarteJoaillerie(int numeroLigne, int numeroColonne);
    void afficherPyramide();
    std::stack<CarteJoaillerie> & getPioche(int niveau);
    unsigned int getCartesRestantes(unsigned int niveau)const;
};



#endif
