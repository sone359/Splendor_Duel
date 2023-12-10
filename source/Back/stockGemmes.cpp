#include "stockGemmes.h"

//Méthodes publiques de la classe StockGemmes

StockGemmes& StockGemmes::ajouter_jeton(Jeton jeton)
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

    return *this;
}

StockGemmes& StockGemmes::retirer_jeton(Jeton jeton)
{
    switch (jeton)
    {
    case Nul:
        throw std::invalid_argument("Impossible de retirer un jeton Nul (correspond à une valeur inexistante)");
    case Or:
        throw std::invalid_argument("Impossible de retirer un jeton Or (inexistant dans ce type de stock, préférez un StockGemmesOr)");
    case Bleu:
        if(get_Bleu() == 0){throw SplendorException("Impossible de retirer un jeton Bleu (stock vide)");}
        set_Bleu(get_Bleu() - 1);
        break;
    case Vert:
        if(get_Vert() == 0){throw SplendorException("Impossible de retirer un jeton Vert (stock vide)");}
        set_Vert(get_Vert()  - 1);
        break;
    case Blanc:
        if(get_Blanc() == 0){throw SplendorException("Impossible de retirer un jeton Blanc (stock vide)");}
        set_Blanc(get_Blanc()  - 1);
        break;
    case Rouge:
        if(get_Rouge() == 0){throw SplendorException("Impossible de retirer un jeton Rouge (stock vide)");}
        set_Rouge(get_Rouge()  - 1);
        break;
    case Noir:
        if(get_Noir() == 0){throw SplendorException("Impossible de retirer un jeton Noir (stock vide)");}
        set_Noir(get_Noir()  - 1);
        break;
    case Perle:
        if(get_Perle() == 0){throw SplendorException("Impossible de retirer un jeton Perle (stock vide)");}
        set_Perle(get_Perle()  - 1);
        break;
    }

    return *this;
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
    set_Bleu(get_Bleu()+autre_stock.get_Bleu());
    set_Vert(get_Vert()+autre_stock.get_Vert());
    set_Blanc(get_Blanc()+autre_stock.get_Blanc());
    set_Rouge(get_Rouge()+autre_stock.get_Rouge());
    set_Noir(get_Noir()+autre_stock.get_Noir());
    set_Perle(get_Perle()+autre_stock.get_Perle());
}

int StockGemmes::operator<(const StockGemmes& s)const{
    if(get_Bleu()<=s.get_Bleu()||
        get_Vert()<=s.get_Vert()||
        get_Blanc()<=s.get_Blanc()||
        get_Rouge()<=s.get_Rouge()||
        get_Noir()<=s.get_Noir()||
        get_Perle()<=s.get_Perle()) return 1;
    else{return 0;}
}

void StockGemmes::operator-=(const StockGemmes& autre_stock){
    int calc=0;
    for (int i =0; i<6;i++){
        calc = gemmes[i]-autre_stock.gemmes[i];
        if (calc>0) gemmes[i]=calc;
        else gemmes[i]=0;
    }
}


//renvoit la difference en valeurs absolues des stockgemmes (pour peut_acheter)
StockGemmes StockGemmes::operator/(const StockGemmes& autre_stock)const{
    StockGemmes result;
    //pour chaque couleur
    for(int i=0;i<6;i++){
        //si le premier est < au 2e le resultat =z
        if(gemmes[i]<autre_stock.gemmes[i]) result.gemmes[i]=abs(gemmes[i]-autre_stock.gemmes[i]);
    }
    return result;
}


unsigned int total_stock(const StockGemmes& stock)
{
    return stock.get_Bleu() + stock.get_Vert() + stock.get_Blanc() + stock.get_Rouge() + stock.get_Noir() + stock.get_Perle();
}

StockGemmesOr& StockGemmesOr::ajouter_jeton(Jeton jeton)
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

    return *this;
}

StockGemmesOr& StockGemmesOr::retirer_jeton(Jeton jeton)
{
    switch (jeton)
    {
    case Nul:
        throw std::invalid_argument("Impossible de retirer un jeton Nul (correspond à une valeur inexistante)");
    case Or:
        if(get_Or() == 0){throw SplendorException("Impossible de retirer un jeton Or (stock vide)");}
        set_Or(get_Or() - 1);
        break;
    case Bleu:
        if(get_Bleu() == 0){throw SplendorException("Impossible de retirer un jeton Bleu (stock vide)");}
        set_Bleu(get_Bleu() - 1);
        break;
    case Vert:
        if(get_Vert() == 0){throw SplendorException("Impossible de retirer un jeton Vert (stock vide)");}
        set_Vert(get_Vert()  - 1);
        break;
    case Blanc:
        if(get_Blanc() == 0){throw SplendorException("Impossible de retirer un jeton Blanc (stock vide)");}
        set_Blanc(get_Blanc()  - 1);
        break;
    case Rouge:
        if(get_Rouge() == 0){throw SplendorException("Impossible de retirer un jeton Rouge (stock vide)");}
        set_Rouge(get_Rouge()  - 1);
        break;
    case Noir:
        if(get_Noir() == 0){throw SplendorException("Impossible de retirer un jeton Noir (stock vide)");}
        set_Noir(get_Noir()  - 1);
        break;
    case Perle:
        if(get_Perle() == 0){throw SplendorException("Impossible de retirer un jeton Perle (stock vide)");}
        set_Perle(get_Perle()  - 1);
        break;
    }

    return *this;
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

StockGemmesOr StockGemmesOr::operator/(const StockGemmesOr& autre_stock)const{
    StockGemmesOr result;
    //pour chaque couleur
    for(int i=0;i<6;i++){
        //si le premier est < au 2e le resultat = la diff
        if(gemmes[i]<autre_stock.gemmes[i]) result.gemmes[i]=abs(gemmes[i]-autre_stock.gemmes[i]);
    }
    if (jeton_or<autre_stock.jeton_or) {
        result.set_Or(autre_stock.get_Or()-get_Or());
    }
    return result;
}

unsigned int total_stock(const StockGemmesOr& stock)
{
    return stock.get_Bleu() + stock.get_Vert() + stock.get_Blanc() + stock.get_Rouge() + stock.get_Noir() + stock.get_Perle() + stock.get_Or();
}