#include "sac.h"
#include <iostream>
#include <vector>

Sac* Sac::sac = nullptr;

Sac& Sac::get_sac()
{
    if (sac == nullptr)
    {
        sac = new Sac;
    }
    return *sac;
}

void Sac::delete_sac()
{
    delete sac;
    sac = nullptr;
}

Sac::~Sac(){}

void Sac::ajouter_jeton(Jeton jeton)
{
    gemmes.ajouter_jeton(jeton);
}

Jeton Sac::retirer_jeton()
{
    //Détermination du poids de chaque type de jeton (empêche notamment un type de jeton absent du sac d'être retiré car son poids sera égal à 0)
    double nb_gemmes = total_stock(gemmes);
    std::vector<double> poids = {gemmes.get_Bleu()/nb_gemmes, gemmes.get_Vert()/nb_gemmes, gemmes.get_Blanc()/nb_gemmes, gemmes.get_Rouge()/nb_gemmes, gemmes.get_Noir()/nb_gemmes, gemmes.get_Perle()/nb_gemmes, gemmes.get_Or()/nb_gemmes};

    //Génération d'un nombre aléatoire
    std::default_random_engine generator(random_seed());
    std::discrete_distribution<int> distribution(poids.begin(), poids.end());

    switch (distribution(generator))
    {
    case 0:
        gemmes.set_Bleu(gemmes.get_Bleu() - 1);
        return Bleu;
    case 1:
        gemmes.set_Vert(gemmes.get_Vert() - 1);
        return Vert;
    case 2:
        gemmes.set_Blanc(gemmes.get_Blanc() - 1);
        return Blanc;
    case 3:
        gemmes.set_Rouge(gemmes.get_Rouge() - 1);
        return Rouge;
    case 4:
        gemmes.set_Noir(gemmes.get_Noir() - 1);
        return Noir;
    case 5:
        gemmes.set_Perle(gemmes.get_Perle() - 1);
        return Perle;
    case 6:
        gemmes.set_Or(gemmes.get_Or() - 1);
        return Or;
    }
}
