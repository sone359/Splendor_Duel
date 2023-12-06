#ifndef PYRAMIDE_CPP
#define PYRAMIDE_CPP

#include "pyramide.h"

Pyramide* Pyramide::instance = nullptr;


    Pyramide::Pyramide(std::vector<CarteJoaillerie> cartes){
        ligne1.resize(5);  
        ligne2.resize(4);
        ligne3.resize(3);
        //std::cout<<"hello constr pyr"<<std::endl;
        //créer les pioches
        for(CarteJoaillerie  carte : cartes){
            if (carte.get_niveau() == 1) Niveau1.push(carte);
            if (carte.get_niveau() == 2) Niveau2.push(carte);
            if (carte.get_niveau() == 3) Niveau3.push(carte);
        }

        for(int i =1; i<6 ;i++){
            piocherCarteJoaillerie(1,i);
        }
        for(int i =1; i<5 ;i++){
            piocherCarteJoaillerie(2,i);
        }
        for(int i =1; i<4 ;i++){
            piocherCarteJoaillerie(3,i);
        }


    }

    void Pyramide::initialiser(std::vector<CarteJoaillerie> cartes){
        if (instance == nullptr) {
            instance = new Pyramide(cartes);
        } else {
            std::cerr << "La pyramide a déjà été initialisée.\n" << std::endl;
        }
    }


    Pyramide* Pyramide::getInstance(){
        if(instance==nullptr)//l'instance n'existe pas
            std::cerr<<"La pyramide doit d'abord être initialisee.\n"<<std::endl;

        return instance;//renvoit l'instance
    }

    CarteJoaillerie Pyramide::reserverCarteJoaillerie(int numeroLigne, int numeroColonne){
        //meme fonction que acheter + on peut reserver dans la pioche
        if (numeroColonne==0) {
            CarteJoaillerie res;
            switch (numeroLigne)
            {
            case 1:
                res = Niveau1.top();
                Niveau1.pop();
                break;
            case 2:
                res = Niveau2.top();
                Niveau2.pop();
                break;
            case 3:
                res = Niveau3.top();
                Niveau3.pop();
                break;
            }
            return res;
        }
        return acheterCarteJoaillerie(numeroLigne,numeroColonne);
    }

    CarteJoaillerie Pyramide::acheterCarteJoaillerie(int numeroLigne, int numeroColonne){
        //on récupère la carte à cette adresse pour la retourner
        CarteJoaillerie result = recupererCarteJoaillerie(numeroLigne,numeroColonne);
        //elle est remplacee en piochant
        piocherCarteJoaillerie(numeroLigne,numeroColonne);
        return result;
    }

    void Pyramide::piocherCarteJoaillerie(int numeroLigne, int numeroColonne){
        switch (numeroLigne)
        {
        case 1:
            ligne1[numeroColonne-1]=Niveau1.top();
            Niveau1.pop();
            break;
        case 2:
            ligne2[numeroColonne-1]=Niveau2.top();
            Niveau2.pop();
            break;
        case 3:
            ligne3[numeroColonne-1]=Niveau3.top();
            Niveau3.pop();
            break;
        }
    }

    CarteJoaillerie Pyramide::recupererCarteJoaillerie(int numeroLigne, int numeroColonne){
        switch (numeroLigne)
        {
        case 1:
            if (numeroColonne > 0 && numeroColonne <= ligne1.size()) {
                CarteJoaillerie carte = ligne1[numeroColonne-1];
                return carte;
            } else {
                throw SplendorException("Erreur : numero de colonne invalide.\n");
            }
        case 2:
            if (numeroColonne > 0 && numeroColonne <= ligne2.size()) {
                CarteJoaillerie carte = ligne2[numeroColonne-1];
                return carte;
            } else {
                throw SplendorException("Erreur : numero de colonne invalide.\n");
            }
        case 3:
            if (numeroColonne > 0 && numeroColonne <= ligne3.size()) {
                CarteJoaillerie carte = ligne3[numeroColonne-1];
                return carte;
            } else {
                throw SplendorException("Erreur : numero de colonne invalide.\n");
            }
        default:
            throw SplendorException("Erreur : numero de ligne invalide.\n");
        }
    }

    void Pyramide::afficherPyramide(){
        std::cout<<"AFFICHAGE PYRAMIDE\n";

        std::cout<<"LIGNE3\n";
        for (int i = 0; i < 3; i++)
        {
            std::cout<<" "<<ligne3[i]<<" ";
        }
        std::cout<<'\n';

        std::cout<<"LIGNE2\n";
        for (int i = 0; i < 4; i++)
        {
            std::cout<<" "<<ligne2[i]<<" ";
        }
        std::cout<<'\n';

        std::cout<<"LIGNE1\n";
        for (int i = 0; i < 5; i++)
        {
            std::cout<<" "<<ligne1[i]<<" ";
        }
        std::cout<<'\n';

    }



#endif
