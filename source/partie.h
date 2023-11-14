#ifndef PARTIE_H
#define PARTIE_H

#include "pyramide.h"
#include "carte_joaillerie_test.h"


class Partie{
    private :
    
    public : 
        CarteJoaillerie * cartes[67];
        
        void init(){
            Pyramide::initialiser(cartes);
            Pyramide::getInstance()->afficherPyramide();
        }
};

#endif