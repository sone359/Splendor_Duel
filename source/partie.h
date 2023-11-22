#ifndef PARTIE_H
#define PARTIE_H

#include "pyramide.h"
#include "carte_joaillerie_test.h"
#include "plateau.h"
#include "interfaceConsole.h"


class Partie{
    private :
    
    public : 
        CarteJoaillerie * cartes[67];
        
        void initPyramide(){
            Pyramide::initialiser(cartes);
            Pyramide::getInstance()->afficherPyramide();
        }

        void initPlateau(){
            Plateau::get_plateau();
        }

        Partie(){
            for (int i=0;i<67;i++){cartes[i]=new CarteJoaillerie(i,i);};
            initPyramide();
            initPlateau();
        }
        ~Partie(){
        for (int i=0;i<67;i++){delete cartes[i];}

        }
};

#endif
