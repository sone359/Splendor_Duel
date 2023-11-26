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

protected:
    static Sac* sac;
    Sac() = default;
    Sac(const Sac&);
    virtual ~Sac();
    void operator=(const Sac&);

private:
    StockGemmesOr gemmes;
    std::random_device random_seed; //Attribut car en raison du caractère pseudo-aléatoire, il y a nécessité d'unicité pour ne pas obtenir la même séquence de nombre à chaque appel
};

#endif
