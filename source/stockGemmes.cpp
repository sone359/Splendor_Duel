#include "stockGemmes.h"
#include <stdexcept>

//Méthodes publiques de la classe StockGemmes

//Contructeur de recopie
StockGemmes::StockGemmes(unsigned int bleu, unsigned int vert, unsigned int blanc, unsigned int rouge, unsigned int noir, unsigned int perle)
{
    set_Bleu(bleu);
    set_Vert(bleu);
    set_Blanc(bleu);
    set_Rouge(bleu);
    set_Noir(bleu);
    set_Perle(bleu);
}

//Setters
void StockGemmes::set_Bleu(unsigned int new_value)
{
    if (new_value <= 4) {gemmes[0] = new_value;}
    else {throw std::invalid_argument("La valeur d'un stock de jeton bleu ne peut pas être supérieure à 4");}
}
void StockGemmes::set_Vert(unsigned int new_value)
{
    if (new_value <= 4) {gemmes[1] = new_value;}
    else {throw std::invalid_argument("La valeur d'un stock de jeton vert ne peut pas être supérieure à 4");}
}
void StockGemmes::set_Blanc(unsigned int new_value)
{
    if (new_value <= 4) {gemmes[2] = new_value;}
    else {throw std::invalid_argument("La valeur d'un stock de jeton blanc ne peut pas être supérieure à 4");}
}
void StockGemmes::set_Rouge(unsigned int new_value)
{
    if (new_value <= 4) {gemmes[3] = new_value;}
    else {throw std::invalid_argument("La valeur d'un stock de jeton rouge ne peut pas être supérieure à 4");}
}
void StockGemmes::set_Noir(unsigned int new_value)
{
    if (new_value <= 4) {gemmes[4] = new_value;}
    else {throw std::invalid_argument("La valeur d'un stock de jeton noir ne peut pas être supérieure à 4");}
}
void StockGemmes::set_Perle(unsigned int new_value)
{
    if (new_value <= 2) {gemmes[5] = new_value;}
    else {throw std::invalid_argument("La valeur d'un stock de jeton perle ne peut pas être supérieure à 2");}
}
