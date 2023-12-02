#include <iostream>
#include <vector>

#include "Back/stockGemmes.h"
#include "Back/plateau.h"
#include "Back/sac.h"
#include "Back/partie.h"
#include "Console/interfaceConsole.h"


using namespace std;

int main()
{
    //std::cout<<"youhou";
    //std::vector<CarteJoaillerie> cartes(67,CarteJoaillerie());
    //cartes[0].setNiveau(1);
    //std::cout<<cartes[0].get_niveau();
    //std::cout<<"youhou";

    //std::cout<<"youhou";
    //Pyramide::getInstance();
    //std::cout<<"youhou";
    Partie& game = Partie::get_partie();
    InterfaceConsole ic;
    ic.main();

    return 0;
}
