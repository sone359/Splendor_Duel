#include "sac.h"
#include <iostream>
#include <vector>
#include <chrono>

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

void Sac::ajouter_stock(StockGemmesOr jetons)
{
    for(int i=0;i<jetons.get_Blanc();i++){
        gemmes.ajouter_jeton(Blanc);
    }
    for(int i=0;i<jetons.get_Bleu();i++){
        gemmes.ajouter_jeton(Bleu);
    }
    for(int i=0;i<jetons.get_Rouge();i++){
        gemmes.ajouter_jeton(Rouge);
    }
    for(int i=0;i<jetons.get_Noir();i++){
        gemmes.ajouter_jeton(Noir);
    }
    for(int i=0;i<jetons.get_Perle();i++){
        gemmes.ajouter_jeton(Perle);
    }
    for(int i=0;i<jetons.get_Vert();i++){
        gemmes.ajouter_jeton(Vert);
    }
    for(int i=0;i<jetons.get_Or();i++){
        gemmes.ajouter_jeton(Or);
    }
}

Jeton Sac::retirer_jeton()
{
    //D�termination du poids de chaque type de jeton (emp�che notamment un type de jeton absent du sac d'�tre retir� car son poids sera �gal � 0)
    double nb_gemmes = total_stock(gemmes);
    std::vector<double> poids = {gemmes.get_Bleu()/nb_gemmes, gemmes.get_Vert()/nb_gemmes, gemmes.get_Blanc()/nb_gemmes, gemmes.get_Rouge()/nb_gemmes, gemmes.get_Noir()/nb_gemmes, gemmes.get_Perle()/nb_gemmes, gemmes.get_Or()/nb_gemmes};

    //G�n�ration d'un nombre al�atoire
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count()); //Seed triviale base sur l'heure donne comme exemple par cplusplus.com
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
