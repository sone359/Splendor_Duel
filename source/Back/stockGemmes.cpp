#include "stockGemmes.h"
#include "../tools.h"
#include <stdexcept>

//Méthodes publiques de la classe StockGemmes

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
    set_Bleu(autre_stock.get_Bleu());
    set_Vert(autre_stock.get_Vert());
    set_Blanc(autre_stock.get_Blanc());
    set_Rouge(autre_stock.get_Rouge());
    set_Noir(autre_stock.get_Noir());
    set_Perle(autre_stock.get_Perle());
    return *this;
}

unsigned int total_stock(const StockGemmes& stock)
{
    return stock.get_Bleu() + stock.get_Vert() + stock.get_Blanc() + stock.get_Rouge() + stock.get_Noir() + stock.get_Perle();
}

//Contructeur
StockBonus::StockBonus(unsigned int bleu, unsigned int vert, unsigned int blanc, unsigned int rouge, unsigned int noir, unsigned int perle, unsigned int jaune)// : StockGemmes::StockGemmes()
{
    set_Bleu(bleu);
    set_Vert(vert);
    set_Blanc(blanc);
    set_Rouge(rouge);
    set_Noir(noir);
    set_Perle(perle);
    set_Or(jaune);
}

StockBonus StockBonus::operator-(const StockGemmes& autre_stock) const
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
        throw SplendorException("Votre stock de jetons est insuffisant");
    }

    return StockBonus(bleu, vert, blanc, rouge, noir, perle, jeton_or);
}

StockBonus StockBonus::operator=(const StockGemmes& autre_stock)
{
    *this = autre_stock;
    set_Or(0);
    return *this;
}

StockBonus StockBonus::operator=(const StockBonus& autre_stock)
{
    *this = autre_stock;
    set_Or(autre_stock.get_Or());
    return *this;
}
