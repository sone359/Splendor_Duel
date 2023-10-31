#ifndef PYRAMIDE_H
#define PYRAMIDE_H

#include <stack>
#include "carte_joaillerie.h"

class Pyramide {
    private :
    //3 stacks de CarteJoailleries
    std::stack<CarteJoaillerie> Niveau1;
    std::stack<CarteJoaillerie> Niveau2;
    std::stack<CarteJoaillerie> Niveau3;
    //voir gestion de mémoire est-ce qu'il faut dealloc?

    //3 lignes
    CarteJoaillerie ligne1[5];
    CarteJoaillerie ligne2[4];
    CarteJoaillerie ligne3[3];
    //singleton dc constructeur
    Pyramide();
    //et instance
    static Pyramide instance;
    //constructeur de recop, assignment op
    Pyramide operator=(Pyramide& p)=delete;
    Pyramide(Pyramide& p)=delete;

    public : 
    //instance accessible par Partie
    Pyramide& getInstance();
    //acheter retourne la CarteJoaillerie achetée et la remplace ds la pyramide avec piocher
    CarteJoaillerie& acheterCarteJoaillerie(int numeroLigne, int numeroColonne);
    //reserver retourne la CarteJoaillerie réservée et la remplace ds la pyramide avec piocher
    CarteJoaillerie& reserverCarteJoaillerie(int numeroLigne, int NumeroColonne);
    //piocher prend une CarteJoaillerie du bon stack et la met à la place donnée
    void piocherCarteJoaillerie(int numeroLigne, int NumeroColonne);

};

#endif