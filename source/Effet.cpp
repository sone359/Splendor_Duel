// Effet.cpp

#include "Effet.h"

EffetHandler::EffetHandler(Effet effet)
{
    this->effet = effet;
}

void EffetHandler::appliquerEffet()
{
    switch (effet)
    {
        case rejouer:
            // Implémentez l'effet "rejouer" ici
            break;
        case privilege:
            // Implémentez l'effet "privilege" ici
            break;
        case couleur:
            // Implémentez l'effet "couleur" ici
            break;
        case gemme:
            // Implémentez l'effet "gemme" ici
            break;
        case voler:
            // Implémentez l'effet "voler" ici
            break;
    }
}
