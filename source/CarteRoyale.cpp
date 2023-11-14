#include "CarteRoyale.h"

// Constructeur par d�faut
CarteRoyale::CarteRoyale()
    : pointsPrestige(0), capacite(Effet::rejouer), cheminImage("")
{
}

// Constructeur avec param�tres
CarteRoyale::CarteRoyale(int pointsPrestige, Effet capacite, const std::string& cheminImage)
    : pointsPrestige(pointsPrestige), capacite(capacite), cheminImage(cheminImage)
{
}
// Constructeur de recopie
CarteRoyale::CarteRoyale(const CarteRoyale& other)
    : pointsPrestige(other.pointsPrestige), capacite(other.capacite), cheminImage(other.cheminImage)
{
}

// Op�rateur d'affectation
CarteRoyale& CarteRoyale::operator=(const CarteRoyale& other)
{
    if (this == &other) {
        return *this; // �viter l'auto-affectation
    }

    pointsPrestige = other.pointsPrestige;
    capacite = other.capacite;
    cheminImage = other.cheminImage;
    return *this;
}
// Getter pour pointsPrestige
int CarteRoyale::getPointsPrestige() const
{
    return pointsPrestige;
}

// Getter pour capacite
Effet CarteRoyale::getCapacite() const
{
    return capacite;
}

// Getter pour cheminImage
std::string CarteRoyale::getCheminImage() const
{
    return cheminImage;
}

// Setter pour pointsPrestige
void CarteRoyale::setPointsPrestige(int points)
{
    pointsPrestige = points;
}

// Setter pour capacite
void CarteRoyale::setCapacite(Effet effet)
{
    capacite = effet;
}

// Setter pour cheminImage
void CarteRoyale::setCheminImage(const std::string& chemin)
{
    cheminImage = chemin;
}

// Destructeur
CarteRoyale::~CarteRoyale()
{
    // Si vous avez besoin de lib�rer des ressources � la destruction de l'objet, faites-le ici.
}
