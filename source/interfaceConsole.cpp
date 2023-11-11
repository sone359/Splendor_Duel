#include "interfaceConsole.h"
#include "Joueur.h"
#include <iostream>

void InterfaceConsole::afficherPlateau()
{
    for (int i = 0 ; i < 5 ; i++)
    {
        for (int j = 0 ; j < 5 ; j++)
        {
            switch (plateau[j][i])
            {
            case Nul:
                std::cout << "- ";
                break;
            case Bleu:
                std::cout << "B ";
                break;
            case Vert:
                std::cout << "V ";
                break;
            case Blanc:
                std::cout << "W ";
                break;
            case Rouge:
                std::cout << "R ";
                break;
            case Noir:
                std::cout << "N ";
                break;
            case Perle:
                std::cout << "P ";
                break;
            case Or:
                std::cout << "O ";
                break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/*void InterfaceConsole::afficherJetonsPossedes(Joueur& joueur)
{
    std::cout << "Jetons possédés : " << "B x " << joueur.getGemmes().get_Bleu() << ", V x " << joueur.getGemmes().get_Vert() << ", W x " << joueur.getGemmes().get_Blanc() << ", R x " << joueur.getGemmes().get_Rouge() << ", N x " << joueur.getGemmes().get_Noir() << ", P x " << joueur.getGemmes().get_Perle() << ", O x " << joueur.getBonus.get_Or() << endl;
}*/
