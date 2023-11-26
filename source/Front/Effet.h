#ifndef EFFET_H_INCLUDED
#define EFFET_H_INCLUDED

enum Effet
{
    rejouer,
    privilege,
    couleur,
    gemme,
    voler,
    sans
};

class EffetHandler
{
public:
    EffetHandler(Effet effet);
    void appliquerEffet();

private:
    Effet effet;
};


#endif // EFFET_H_INCLUDED
