#ifndef STOCKGEMMES_H
#define STOCKGEMMES_H

class StockGemmes
{
    public:
        // Constructeurs
        StockGemmes() = default;
        StockGemmes(unsigned int bleu, unsigned int vert, unsigned int blanc, unsigned int rouge, unsigned int noir, unsigned int perle);
        // Constructeur de recopie
        StockGemmes(const StockGemmes& autre) = default;

        //Getters
        unsigned int get_Bleu() const {return gemmes[0];};
        unsigned int get_Vert() const {return gemmes[1];};
        unsigned int get_Blanc() const {return gemmes[2];};
        unsigned int get_Rouge() const {return gemmes[3];};
        unsigned int get_Noir() const {return gemmes[4];};
        unsigned int get_Perle() const {return gemmes[5];};

        //Setters
        void set_Bleu(unsigned int new_value);
        void set_Vert(unsigned int new_value);
        void set_Blanc(unsigned int new_value);
        void set_Rouge(unsigned int new_value);
        void set_Noir(unsigned int new_value);
        void set_Perle(unsigned int new_value);

        //Opérateurs surchargés
        StockGemmes operator+(const StockGemmes& autre_stock) const {return StockGemmes(get_Bleu()+autre_stock.get_Bleu(), get_Vert()+autre_stock.get_Vert(), get_Blanc()+autre_stock.get_Blanc(), get_Rouge()+autre_stock.get_Rouge(), get_Noir()+autre_stock.get_Noir(), get_Perle()+autre_stock.get_Perle());};

        // Destructeur
        ~StockGemmes() = default;

    private:
        int gemmes[6] = {0};
};

#endif
