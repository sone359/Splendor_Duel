#include "interfaceConsole.h"
#include "../Back/Joueur.h"
#include <iostream>
#include <vector>
#include <array>
#include <stdexcept>

void InterfaceConsole::afficherPlateau() const
{
    std::cout << "    0 1 2 3 4 " << std::endl;
    std::cout << "    _ _ _ _ _ " << std::endl;
    for (int i = 0 ; i < 5 ; i++)
    {
        std::cout << i << " | ";
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
        std::cout << "|" << std::endl;
    }
    std::cout << "    _ _ _ _ _ " << std::endl << std::endl;
}

void InterfaceConsole::afficherJetonsPossedes(Joueur& joueur) const
{
    std::cout << "Jetons possedes : " << "B x " << joueur.getGemmes().get_Bleu() << ", V x " << joueur.getGemmes().get_Vert() << ", W x " << joueur.getGemmes().get_Blanc() << ", R x " << joueur.getGemmes().get_Rouge() << ", N x " << joueur.getGemmes().get_Noir() << ", P x " << joueur.getGemmes().get_Perle() << ", O x " << joueur.getGemmes().get_Or() << std::endl << std::endl;
}

void InterfaceConsole::afficherPyramide() const{
    std::cout<<"AFFICHAGE PYRAMIDE CONSOLE\n";
    for(int j=3;j>=1;j--){
        for(int l=1;l<8;l++){
            for(int p=0;p<j*3;p++)std::cout<<" ";
            for (int i = 1; i <= 6-j; i++)
            {
                afficherCarteparligne(partie.get_pyramide().recupererCarteJoaillerie(j,i),l,std::cout);
                std::cout<<' ';
            }
        std::cout<<'\n';
        }
        std::cout<<'\n';
    }
}

void InterfaceConsole::afficherCarteparligne(const CarteJoaillerie& c,int ligne,std::ostream& os)const {
    if (ligne<1 || ligne>7) throw SplendorException("Une carte s'affiche en 7 lignes.\n");
    switch (ligne){
        case 1:
            os<<"----";c.afficher_Couleur(os);os<<"---";
            return;
        case 2:
            os <<"|  +"<< c.get_nbBonus() << "  |";
            return;
        case 3:
            os << "| PP"<<c.get_pointsPrestige()<<"  |" ;
            return;
        case 4:
            os<<"| ";
            switch (c.get_capacite()[0])
            {
            case 0:
                os<<"REJ";
                break;
            case 1:
                os<<"REJ";
                break;
            case 2:
                os<<"REJ";
                break;
            case 3:
                os<<"REJ";
                break;
            case 4:
                os<<"REJ";
                break;
            case 5:
                os<<"   ";
                break;
            default :
                throw SplendorException("Erreur capacite.\n");
                break;
            }
            os<<"  |";
        return;
        case 5:
            os<<"|BWVRNP|";
            return;
        case 6:
            os<<c.get_cout();
            return;
        case 7:
        os<<"--------";
        return;
    }
}
