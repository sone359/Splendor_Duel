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
    return gemmes.random_pop();
}
