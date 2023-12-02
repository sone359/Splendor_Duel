#ifndef EFFET_H_INCLUDED
#define EFFET_H_INCLUDED

enum Effet
{
    rejouer,//second_turn
    privilege,//privilege_scroll
    couleur,//multi_gem
    gemme,//token
    voler,//steal
    sans//none
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
