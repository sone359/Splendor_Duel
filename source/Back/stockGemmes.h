#ifndef STOCKGEMMES_H
#define STOCKGEMMES_H

class StockGemmes
{
    public:
        // Constructeurs
        StockGemmes(unsigned int bleu = 0, unsigned int vert = 0, unsigned int blanc = 0, unsigned int rouge = 0, unsigned int noir = 0, unsigned int perle = 0);
        // Constructeur de recopie
        StockGemmes(const StockGemmes& autre) : StockGemmes(autre.get_Bleu(), autre.get_Vert(), autre.get_Blanc(), autre.get_Rouge(), autre.get_Noir(), autre.get_Perle()){};

        //Getters
        unsigned int get_Bleu() const {return gemmes[0];};
        unsigned int get_Vert() const {return gemmes[1];};
        unsigned int get_Blanc() const {return gemmes[2];};
        unsigned int get_Rouge() const {return gemmes[3];};
        unsigned int get_Noir() const {return gemmes[4];};
        unsigned int get_Perle() const {return gemmes[5];};

        //Setters
        void set_Bleu(unsigned int new_value){gemmes[0] = new_value;};
        void set_Vert(unsigned int new_value){gemmes[1] = new_value;};
        void set_Blanc(unsigned int new_value){gemmes[2] = new_value;};
        void set_Rouge(unsigned int new_value){gemmes[3] = new_value;};
        void set_Noir(unsigned int new_value){gemmes[4] = new_value;};
        void set_Perle(unsigned int new_value){gemmes[5] = new_value;};

        //Opérateurs surchargés
        StockGemmes operator+(const StockGemmes& autre_stock) const {return StockGemmes(get_Bleu()+autre_stock.get_Bleu(), get_Vert()+autre_stock.get_Vert(), get_Blanc()+autre_stock.get_Blanc(), get_Rouge()+autre_stock.get_Rouge(), get_Noir()+autre_stock.get_Noir(), get_Perle()+autre_stock.get_Perle());};
        StockGemmes operator-(const StockGemmes& autre_stock) const;
        StockGemmes operator=(const StockGemmes& autre_stock);

        // Destructeur
        ~StockGemmes() = default;

    protected:
        unsigned int gemmes[6] = {0};
};

class StockBonus : public StockGemmes
{
public:
    //Constructeur par défaut
    StockBonus(unsigned int bleu = 0, unsigned int vert = 0, unsigned int blanc = 0, unsigned int rouge = 0, unsigned int noir = 0, unsigned int perle = 0, unsigned int jaune = 0);
    //Getters
    unsigned int get_Or() const {return jeton_or;};
    //Setters
    void set_Or(unsigned int new_value){jeton_or = new_value;};

    //Opérateurs
    StockBonus operator+(const StockGemmes& autre_stock) const {return StockBonus(get_Bleu()+autre_stock.get_Bleu(), get_Vert()+autre_stock.get_Vert(), get_Blanc()+autre_stock.get_Blanc(), get_Rouge()+autre_stock.get_Rouge(), get_Noir()+autre_stock.get_Noir(), get_Perle()+autre_stock.get_Perle());};
    StockBonus operator-(const StockGemmes& autre_stock) const;
    StockBonus operator=(const StockGemmes& autre_stock);
    StockBonus operator=(const StockBonus& autre_stock);

protected:
    unsigned int jeton_or = 0;
};

unsigned int total_stock(const StockGemmes& stock);

#endif
