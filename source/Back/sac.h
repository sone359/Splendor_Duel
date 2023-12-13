#ifndef SAC_H
#define SAC_H

#include <random>
#include "../tools.h"
#include "stockGemmes.h"

class Sac
{
public :

    static Sac& get_sac();
    static void delete_sac();

    void ajouter_jeton(Jeton jeton);
    Jeton retirer_jeton();
    void ajouter_stock(StockGemmesOr jetons);

    //Getter const
    const StockGemmesOr& get_gemmes() const{return gemmes;}

protected:
    static Sac* sac;
    Sac() = default;
    Sac(const Sac&);
    virtual ~Sac();
    void operator=(const Sac&);

private:
    StockGemmesOr gemmes;
    std::random_device random_seed; //Attribut car en raison du caract�re pseudo-al�atoire, il y a n�cessit� d'unicit� pour ne pas obtenir la m�me s�quence de nombre � chaque appel
};

#endif
