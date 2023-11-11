#ifndef PARTIE_H
#define PARTIE_H

#include "pyramide.h"
#include "carte_joaillerie_test.h"


class Partie{
    private :
    
        CarteJoaillerie * cartes[67];
    public : 
        
        void init(){
            Pyramide::initialiser(cartes);
        }
};

#endif