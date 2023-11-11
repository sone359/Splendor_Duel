#ifndef PYRAMIDE_H
#define PYRAMIDE_H

#include <stack>
#include "carte_joaillerie_test.h"

class Pyramide {
    private :
    //3 stacks de CarteJoailleries
    std::stack<CarteJoaillerie*> Niveau1;
    std::stack<CarteJoaillerie*> Niveau2;
    std::stack<CarteJoaillerie*> Niveau3;

    //3 lignes
    CarteJoaillerie * ligne1[5];
    CarteJoaillerie * ligne2[4];
    CarteJoaillerie * ligne3[3];//tableaux de pointeurs pcq les cartes peuvent pas être dupliquées
    //singleton dc constructeur
    Pyramide(CarteJoaillerie * cartes[67]);
    //constructeur de recop, assignment op
    void operator=(Pyramide& p)=delete;
    Pyramide(Pyramide& p)=delete;
    //et instance
    static Pyramide * instance;
    //pour pouvoir separer le constructeur de getInstance pcq il prend des arguments un bool permet de verif l'init
    bool init=false;

    public : 
    //appelee au debut du jeu pour init l'instance
    static void initialiser(CarteJoaillerie * jeu[67]);
    //instance accessible par Partie
    static Pyramide* getInstance();
    //acheter retourne la CarteJoaillerie achetée et la remplace ds la pyramide avec piocher
    CarteJoaillerie* acheterCarteJoaillerie(int numeroLigne, int numeroColonne);
    //reserver retourne la CarteJoaillerie réservée et la remplace ds la pyramide avec piocher
    CarteJoaillerie* reserverCarteJoaillerie(int numeroLigne, int numeroColonne);
    //piocher prend une CarteJoaillerie du bon stack et la met à la place donnée
    void piocherCarteJoaillerie(int numeroLigne, int numeroColonne);
    //appelee par acheter et reserver, recuperer renvoit la carte à la place donnée
    CarteJoaillerie* recupererCarteJoaillerie(int numeroLigne, int numeroColonne);

    void afficherPyramide();

};



#endif
