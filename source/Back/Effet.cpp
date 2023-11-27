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
            // Impl�mentez l'effet "rejouer" ici
            break;
        case privilege:
            // Impl�mentez l'effet "privilege" ici
            break;
        case couleur:
            // Impl�mentez l'effet "couleur" ici
            break;
        case gemme:
            // Impl�mentez l'effet "gemme" ici
            break;
        case voler:
            // Impl�mentez l'effet "voler" ici
            break;
    }
}
