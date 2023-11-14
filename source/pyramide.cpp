#ifndef PYRAMIDE_CPP
#define PYRAMIDE_CPP

#include <iostream>

#include "pyramide.h"
#include "carte_joaillerie_test.h"

Pyramide* Pyramide::instance = nullptr;


    Pyramide::Pyramide(CarteJoaillerie * cartes[67]){
        //créer les pioches
        for (int i = 0; i<40 ; i++){
            Niveau1.push(cartes[i]);
        }
        //std::cout<<"\nnv1 top :"<<Niveau1.top()->getCout();
        for (int i= 39; i<60 ; i++){
            Niveau2.push(cartes[i]);
        }
        //std::cout<<"\nnv2 top :"<<Niveau2.top()->getCout();

        for (int i = 59; i<67 ; i++){
            Niveau3.push(cartes[i]);
        }
        //std::cout<<"\nnv3 top :"<<Niveau3.top()->getCout();

        for(int i =0; i<5 ;i++){
            piocherCarteJoaillerie(1,i);
        }
        for(int i =0; i<4 ;i++){
            piocherCarteJoaillerie(2,i);
        }
        for(int i =0; i<3 ;i++){
            piocherCarteJoaillerie(3,i);
        }

        
    }

    void Pyramide::initialiser(CarteJoaillerie * jeu[67]){
        instance = new Pyramide(jeu);
    }


    Pyramide* Pyramide::getInstance(){
        if(instance==nullptr)//l'instance n'existe pas
            std::cerr<<"La pyramide doit d'abord être initialisee.\n"<<std::endl;
        
        return instance;//renvoit l'instance
    }

    CarteJoaillerie* Pyramide::reserverCarteJoaillerie(int numeroLigne, int numeroColonne){
        //meme fonction que acheter du point de vue de pyramide mais pour joueur ce sera plus clair
        return acheterCarteJoaillerie(numeroLigne,numeroColonne);
    }

    CarteJoaillerie* Pyramide::acheterCarteJoaillerie(int numeroLigne, int numeroColonne){
        //on récupère la carte à cette adresse pour la retourner
        CarteJoaillerie* result = recupererCarteJoaillerie(numeroLigne,numeroColonne);//modif ça ça n'a pas de sens
        //elle est remplacee en piochant
        piocherCarteJoaillerie(numeroLigne,numeroColonne);
        return result;
    }

    void Pyramide::piocherCarteJoaillerie(int numeroLigne, int numeroColonne){
        switch (numeroLigne)
        {
        case 1:
            ligne1[numeroColonne]=Niveau1.top();
            Niveau1.pop();
            break;
        case 2:
            ligne2[numeroColonne]=Niveau2.top();
            Niveau2.pop();
            break;
        case 3:
            ligne3[numeroColonne]=Niveau3.top();
            Niveau3.pop();
            break;
        }
    }

    CarteJoaillerie* Pyramide::recupererCarteJoaillerie(int numeroLigne, int numeroColonne){
        switch (numeroLigne)
        {
        case 1:
            return ligne1[numeroColonne];
            break;
        case 2:
            return ligne2[numeroColonne];
            break;
        case 3:
            return ligne3[numeroColonne];
            break;
        default:
            std::cerr<<"Erreur : numero de ligne invalide.\n"<<std::endl;
            return nullptr;

        }
    }

    void Pyramide::afficherPyramide(){
        std::cout<<"    ";
        for (int i = 0; i < 3; i++)
        {
            std::cout<<" "<<ligne3[i]->afficherCarte()<<" ";
        }
        std::cout<<'\n';

        std::cout<<"  ";
        for (int i = 0; i < 4; i++)
        {
            std::cout<<" "<<ligne2[i]->afficherCarte()<<" ";
        }
        std::cout<<'\n';

        for (int i = 0; i < 5; i++)
        {
            std::cout<<" "<<ligne1[i]->afficherCarte()<<" ";
        }
        std::cout<<'\n';
        
    }



#endif