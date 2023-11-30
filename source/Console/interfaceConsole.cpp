#include "interfaceConsole.h"
#include "../Back/Joueur.h"

void InterfaceConsole::afficher_plateau()
{
    std::cout << "    0 1 2 3 4 " << std::endl;
    std::cout << "    _ _ _ _ _ " << std::endl;
    for (int i = 0 ; i < 5 ; i++)
    {
        std::cout << i << " | ";
        for (int j = 0 ; j < 5 ; j++)
        {
            switch (partie.get_plateau()[j][i])
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

void InterfaceConsole::afficher_jetons_possedes(unsigned int num_joueur)
{
    Joueur& joueur = partie.get_joueur(num_joueur);
    std::cout << "\nJetons possedes par le joueur " << num_joueur <<" : " << "B x " << joueur.getGemmes().get_Bleu() << ", V x " << joueur.getGemmes().get_Vert() << ", W x " << joueur.getGemmes().get_Blanc() << ", R x " << joueur.getGemmes().get_Rouge() << ", N x " << joueur.getGemmes().get_Noir() << ", P x " << joueur.getGemmes().get_Perle() << ", O x " << joueur.getGemmes().get_Or() << std::endl << std::endl;
}

void InterfaceConsole::afficher_pyramide()
{
    partie.get_pyramide().afficherPyramide();
}

void InterfaceConsole::deroulement_tour()
{
    //Affichage de l'état de la partie
    std::cout << "Tour " << partie.get_tour() << ", au joueur " << partie.joueur_actif() << " de jouer !" << std::endl << std::endl;
    //afficher_pyramide();
    afficher_jetons_possedes(partie.joueur_adverse());
    afficher_plateau();
    afficher_jetons_possedes(partie.joueur_actif());

    Joueur& joueur = partie.get_joueur(partie.joueur_actif());

    //Actions optionnelles

    //Utilisation de privilege, possiblement plusieurs
    while(joueur.getNbPrivileges() > 0)
    {
        std::cout << "Souhaitez-vous utiliser un privilege ? (oui/non)" << std::endl;
        std::string reponse;
        std::cin >> reponse;
        if(reponse == "non"){break;}
        if(reponse != "oui")
        {
            std::cout << "Saisie invalide, merci de rentrer oui ou non et d'appuyer sur la touche Entree de votre clavier" << std::endl;
        }
        else
        {
            afficher_plateau(); //Nouvel affichage du plateau à chaque privilege utilise, pour voir les changements
            unsigned int colonne = 0, ligne = 0;
            std::cout << "Quelle est la colonne du jeton a retirer ?";
            std::cin >> colonne;
            std::cout << "Quelle est la ligne du jeton a retirer ?";
            std::cin >> ligne;
            try
            {
                partie.utilise_privilege(joueur, colonne, ligne);
                afficher_jetons_possedes(partie.joueur_actif());
            }
            catch (const SplendorException& except) //Si une erreur liee aux regles du jeu (et non au programme directement) est interceptée, on l'affiche et on propose à nouveau au joueur d'utiliser un privilege
            {
                std::cout << except.what();
            }
        }
    }

    //Passage au tour suivant, sauf en cas d'effet rejouer
    partie.fin_tour();
}
