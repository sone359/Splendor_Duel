#include "stockGemmes.h"
#include "../tools.h"
#include <stdexcept>

//Méthodes publiques de la classe StockGemmes

void StockGemmes::ajouter_jeton(Jeton jeton)
{
    switch (jeton)
    {
    case Nul:
        throw std::invalid_argument("Impossible d'ajouter un jeton Nul (correspond à une valeur inexistante)");
    case Or:
        throw std::invalid_argument("Impossible d'ajouter un jeton Or (inexistant dans ce type de stock, préférez un StockGemmesOr)");
    case Bleu:
        set_Bleu(get_Bleu() + 1);
        break;
    case Vert:
        set_Vert(get_Vert() + 1);
        break;
    case Blanc:
        set_Blanc(get_Blanc() + 1);
        break;
    case Rouge:
        set_Rouge(get_Rouge() + 1);
        break;
    case Noir:
        set_Noir(get_Noir() + 1);
        break;
    case Perle:
        set_Perle(get_Perle() + 1);
        break;
    }
}

//Contructeur
StockGemmes::StockGemmes(unsigned int bleu, unsigned int vert, unsigned int blanc, unsigned int rouge, unsigned int noir, unsigned int perle)
{
    set_Bleu(bleu);
    set_Vert(vert);
    set_Blanc(blanc);
    set_Rouge(rouge);
    set_Noir(noir);
    set_Perle(perle);
}

StockGemmes StockGemmes::operator-(const StockGemmes& autre_stock) const
{
    int bleu = get_Bleu() - autre_stock.get_Bleu();
    int vert = get_Vert() - autre_stock.get_Vert();
    int blanc = get_Blanc() - autre_stock.get_Blanc();
    int rouge = get_Rouge() - autre_stock.get_Rouge();
    int noir = get_Noir() - autre_stock.get_Noir();
    int perle = get_Perle() - autre_stock.get_Perle();

    if ((bleu < 0) || (vert < 0) || (blanc < 0) || (rouge < 0) || (noir < 0) || (perle < 0))
    {
        throw SplendorException("Votre stock de jetons est insuffisant");
    }
    return StockGemmes(bleu, vert, blanc, rouge, noir, perle);
}

StockGemmes StockGemmes::operator=(const StockGemmes& autre_stock)
{
    this->set_Bleu(autre_stock.get_Bleu());
    this->set_Vert(autre_stock.get_Vert());
    this->set_Blanc(autre_stock.get_Blanc());
    this->set_Rouge(autre_stock.get_Rouge());
    this->set_Noir(autre_stock.get_Noir());
    this->set_Perle(autre_stock.get_Perle());
    return *this;
}

void StockGemmes::operator+=(const StockGemmes& autre_stock){
    set_Bleu(this->get_Bleu()+autre_stock.get_Bleu());
    set_Vert(this->get_Vert()+autre_stock.get_Vert());
    set_Blanc(this->get_Blanc()+autre_stock.get_Blanc());
    set_Rouge(this->get_Rouge()+autre_stock.get_Rouge());
    set_Noir(this->get_Noir()+autre_stock.get_Noir());
    set_Perle(this->get_Perle()+autre_stock.get_Perle());
}

int StockGemmes::operator<(const StockGemmes& s)const{
    if(this->get_Bleu()<s.get_Bleu()||
        this->get_Vert()<s.get_Vert()||
        this->get_Blanc()<s.get_Blanc()||
        this->get_Rouge()<s.get_Rouge()||
        this->get_Noir()<s.get_Noir()||
        this->get_Perle()<s.get_Perle()) return 1;
    else{return 0;}
}

//renvoit la difference en valeurs absolues des stockgemmes (pour peut_acheter)
StockGemmes StockGemmes::operator/(const StockGemmes& autre_stock){
    StockGemmes result;
    for(int i=0;i<6;i++){
        if(gemmes[i]<autre_stock.gemmes[i]) result.gemmes[i]=abs(gemmes[i]-autre_stock.gemmes[i]);
    }
    //result.set_Bleu(abs(this->get_Bleu()-autre_stock.get_Bleu()));
    //result.set_Vert(abs(this->get_Vert()-autre_stock.get_Vert()));
    //result.set_Blanc(abs(this->get_Blanc()-autre_stock.get_Blanc()));
    //result.set_Rouge(abs(this->get_Rouge()-autre_stock.get_Rouge()));
    //result.set_Noir(abs(this->get_Noir()-autre_stock.get_Noir()));
    //result.set_Perle(abs(this->get_Perle()-autre_stock.get_Perle()));
    return result;
}


unsigned int total_stock(const StockGemmes& stock)
{
    return stock.get_Bleu() + stock.get_Vert() + stock.get_Blanc() + stock.get_Rouge() + stock.get_Noir() + stock.get_Perle();
}

void StockGemmesOr::ajouter_jeton(Jeton jeton)
{
    switch (jeton)
    {
    case Nul:
        throw SplendorException("Impossible d'ajouter un jeton Nul (correspond à une valeur inexistante)");
    case Bleu:
        set_Bleu(get_Bleu() + 1);
        break;
    case Vert:
        set_Vert(get_Vert() + 1);
        break;
    case Blanc:
        set_Blanc(get_Blanc() + 1);
        break;
    case Rouge:
        set_Rouge(get_Rouge() + 1);
        break;
    case Noir:
        set_Noir(get_Noir() + 1);
        break;
    case Perle:
        set_Perle(get_Perle() + 1);
        break;
    case Or:
        set_Or(get_Or() + 1);
        break;
    }
}

//Contructeur
StockGemmesOr::StockGemmesOr(unsigned int bleu, unsigned int vert, unsigned int blanc, unsigned int rouge, unsigned int noir, unsigned int perle, unsigned int jaune)// : StockGemmes::StockGemmes()
{
    set_Bleu(bleu);
    set_Vert(vert);
    set_Blanc(blanc);
    set_Rouge(rouge);
    set_Noir(noir);
    set_Perle(perle);
    set_Or(jaune);
}

StockGemmesOr StockGemmesOr::operator-(const StockGemmes& autre_stock) const
{
    int bleu = get_Bleu() - autre_stock.get_Bleu();
    int vert = get_Vert() - autre_stock.get_Vert();
    int blanc = get_Blanc() - autre_stock.get_Blanc();
    int rouge = get_Rouge() - autre_stock.get_Rouge();
    int noir = get_Noir() - autre_stock.get_Noir();
    int perle = get_Perle() - autre_stock.get_Perle();
    int jeton_or = get_Or();

    while (bleu < 0 && jeton_or > 0)
    {
        bleu ++;
        jeton_or--;
    }
    while (vert < 0 && jeton_or > 0)
    {
        vert ++;
        jeton_or--;
    }
    while (blanc < 0 && jeton_or > 0)
    {
        blanc ++;
        jeton_or--;
    }
    while (rouge < 0 && jeton_or > 0)
    {
        rouge ++;
        jeton_or--;
    }
    while (noir < 0 && jeton_or > 0)
    {
        noir ++;
        jeton_or--;
    }
    while (perle < 0 && jeton_or > 0)
    {
        perle ++;
        jeton_or--;
    }

    if ((bleu < 0) || (vert < 0) || (blanc < 0) || (rouge < 0) || (noir < 0) || (perle < 0))
    {
        throw SplendorException("La soustraction des stockGemmes donne un résultat négatif.");
    }

    return StockGemmesOr(bleu, vert, blanc, rouge, noir, perle, jeton_or);
}

StockGemmesOr StockGemmesOr::operator=(const StockGemmes& autre_stock)
{
    set_Bleu(autre_stock.get_Bleu());
    set_Vert(autre_stock.get_Vert());
    set_Blanc(autre_stock.get_Blanc());
    set_Rouge(autre_stock.get_Rouge());
    set_Noir(autre_stock.get_Noir());
    set_Perle(autre_stock.get_Perle());
    set_Or(0);
    return *this;
}

StockGemmesOr StockGemmesOr::operator=(const StockGemmesOr& autre_stock)
{
    set_Bleu(autre_stock.get_Bleu());
    set_Vert(autre_stock.get_Vert());
    set_Blanc(autre_stock.get_Blanc());
    set_Rouge(autre_stock.get_Rouge());
    set_Noir(autre_stock.get_Noir());
    set_Perle(autre_stock.get_Perle());
    set_Or(autre_stock.get_Or());
    return *this;
}

unsigned int total_stock(const StockGemmesOr& stock)
{
    return stock.get_Bleu() + stock.get_Vert() + stock.get_Blanc() + stock.get_Rouge() + stock.get_Noir() + stock.get_Perle() + stock.get_Or();
}
