#ifndef PARTIE_H
#define PARTIE_H

#include "pyramide.h"
#include "carte_joaillerie_test.h"


class Partie{
    private :
    
    public : 
        CarteJoaillerie * cartes[67];
        
        void initPyramide(){
            Pyramide::initialiser(cartes);
            Pyramide::getInstance()->afficherPyramide();
        }

        void initPlateau(){
            
        }

        Partie(){
        for (int i=0;i<67;i++){cartes[i]=new CarteJoaillerie(i,i);};
            initPyramide();
        }
        ~Partie(){
        for (int i=0;i<67;i++){delete cartes[i];}

        }
};

#endif
