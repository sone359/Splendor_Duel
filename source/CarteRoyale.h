#ifndef CARTEROYALE_H_INCLUDED
#define CARTEROYALE_H_INCLUDED

#include <string>
#include "Effet.h"  // Inclure le fichier d'en-tête de l'énuméré Effet si nécessaire

class CarteRoyale
{
private:
    int pointsPrestige;
    Effet capacite;
    std::string cheminImage;

public:
    // Constructeurs
    CarteRoyale();
    CarteRoyale(int pointsPrestige, Effet capacite, const std::string& cheminImage);
        // Constructeur de recopie
    CarteRoyale(const CarteRoyale& other);

    // Opérateur d'affectation
    CarteRoyale& operator=(const CarteRoyale& other);
    // Getters
    int getPointsPrestige() const;
    Effet getCapacite() const;
    std::string getCheminImage() const;

    // Setters
    void setPointsPrestige(int pointsPrestige);
    void setCapacite(Effet capacite);
    void setCheminImage(const std::string& cheminImage);

    // Destructeur
    ~CarteRoyale();
};




#endif // CARTEROYALE_H_INCLUDED
