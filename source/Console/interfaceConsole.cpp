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

int InterfaceConsole::deroulement_tour()
{
    //Initialisation de la possession de l'effet rejouer, qui peut etre obtenu par l'achat d'une carte et qu'il est necessaire de verifier a la fin du tour
    bool effet_rejouer = false;
    //Affichage de l'�tat de la partie
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
            afficher_plateau(); //Nouvel affichage du plateau � chaque privilege utilise, pour voir les changements
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
            catch (const SplendorException& except) //Si une erreur liee aux regles du jeu (et non au programme directement) est intercept�e, on l'affiche et on propose � nouveau au joueur d'utiliser un privilege
            {
                std::cout << except.what() << std::endl;
            }
        }
    }

    //Remplissage optionnel du plateau
    bool fin_remplissage = (partie.get_plateau().get_nbCasesVides() == 0);
    while(!fin_remplissage)
    {
        std::cout << "Souhaitez-vous remplir le plateau (cela donnera un privilege a votre adversaire) ? (oui/non)" << std::endl;
        std::string reponse;
        std::cin >> reponse;
        if(reponse == "non"){break;}
        if(reponse != "oui")
        {
            std::cout << "Saisie invalide, merci de rentrer oui ou non et d'appuyer sur la touche Entree de votre clavier" << std::endl;
        }
        else
        {
            try
            {
                partie.remplir_plateau(joueur);
                fin_remplissage = true;
            }
            catch (const SplendorException& except) //Si une erreur liee aux regles du jeu (et non au programme directement) est intercept�e, on l'affiche et on propose � nouveau au joueur d'utiliser un privilege
            {
                std::cout << except.what() << std::endl;
            }
            afficher_plateau(); //Affichage du plateau pour visualiser les changements apport�s par le remplissage
        }
    }

    //Actions obligatoires
    bool fin_actions_obligatoires = false;
    while(!fin_actions_obligatoires)
    {
        std::cout << "Quelle action obligatoire souhaitez-vous effectuer ?\n1 - Prendre jusqu'a 3 jetons Gemme et/ou Perle\n2 - Prendre 1 jeton Or pour reserver 1 carte Joaillerie\n3 - Acheter 1 carte Joaillerie" << std::endl;
        std::string reponse;
        std::cin >> reponse;
        try
        {
            if(reponse == "1")
            {
                fin_actions_obligatoires = action_prendre_jetons(joueur);
            }
            else if(reponse == "2")
            {
                fin_actions_obligatoires = action_reserver(joueur);
            }
            else if(reponse == "3")
            {
                fin_actions_obligatoires = action_acheter(joueur);
            }
            else
            {
                std::cout << "Saisie invalide, merci de rentrer 1, 2 ou 3 et d'appuyer sur la touche Entree de votre clavier" << std::endl;
            }
        }
        catch (const SplendorException& except) //Si une erreur previsible liee aux regles du jeu (et non au programme directement) est intercept�e, on l'affiche et on propose � nouveau au joueur d'utiliser un privilege
        {
            std::cout << except.what() << std::endl;
        }
    }

    //Verification des conditions de victoire pour le joueur actif
    int victoire = joueur.verifVictoire();
    //Passage au tour suivant, sauf en cas d'effet rejouer
    if(victoire == 0 && !effet_rejouer)
    {
        partie.fin_tour();
    }
    return victoire;
}

bool InterfaceConsole::action_prendre_jetons(Joueur& joueur)
{
    std::cout << "Entrez le nombre de jetons que vous souhaitez prendre sur le plateau (1, 2 ou 3) ou bien 0 pour revenir au choix des actions obligatoires" << std::endl;
    std::string nb_jetons;
    std::cin >> nb_jetons;

    //Possibilite de retour en arriere
    if(nb_jetons == "0")
    {
        return false;
    }
    //Verification de la validite du choix du nombre de jetons
    if(nb_jetons != "1" && nb_jetons != "2" && nb_jetons != "3")
    {
        std::cout << "Saisie invalide, merci de rentrer 1, 2 ou 3 et d'appuyer sur la touche Entree de votre clavier" << std::endl;
        return false;
    }

    //Saisie des coordonn�es du jeton 1
    afficher_plateau(); //Nouvel affichage du plateau � chaque privilege utilise, pour voir les changements
    unsigned int colonne1 = 0, ligne1 = 0;
    std::cout << "Entrez la colonne du premier jeton a retirer : ";
    std::cin >> colonne1;
    std::cout << "Entrez la ligne du premier jeton a retirer : ";
    std::cin >> ligne1;

    if(nb_jetons == "1")
    {
        partie.retirer_jetons({colonne1, ligne1});
        return true;
    }
    else
    {
        //Saisie des coordonn�es du jeton 2
        unsigned int colonne2 = 0, ligne2 = 0;
        std::cout << "Entrez la colonne du deuxi�me jeton a retirer : ";
        std::cin >> colonne2;
        std::cout << "Entrez la ligne du deuxi�me jeton a retirer : ";
        std::cin >> ligne2;

        if(nb_jetons == "2")
        {
            partie.retirer_jetons({colonne1, ligne1}, {colonne2, ligne2});
            return true;
        }
        else
        {
            //Saisie des coordonn�es du jeton 3
            unsigned int colonne3 = 0, ligne3 = 0;
            std::cout << "Entrez la colonne du troisi�me jeton a retirer : ";
            std::cin >> colonne3;
            std::cout << "Entrez la ligne du troisi�me jeton a retirer : ";
            std::cin >> ligne3;

            partie.retirer_jetons({colonne1, ligne1}, {colonne2, ligne2}, {colonne3, ligne3});
            return true;
        }
    }
}

bool InterfaceConsole::action_reserver(Joueur& joueur)
{
    afficher_plateau(); //Nouvel affichage du plateau a chaque privilege utilise, pour voir les changements
    unsigned int colonne_jeton = 0, ligne_jeton = 0, niveau_carte = 0, num_carte = 0;

    //Saisie des coordonn�es du jeton Or a retirer
    std::cout << "Entrez la colonne du jeton Or a retirer : ";
    std::cin >> colonne_jeton;
    std::cout << "Entrez la ligne du jeton Or a retirer : ";
    std::cin >> ligne_jeton;

    //Saisie des coordonn�es de la carte a reserver
    std::cout << "Entrez le niveau de la carte que vous souhaitez reserver : ";
    std::cin >> niveau_carte;
    std::cout << "Entrez le numero de la carte que vous souhaitez reserver (1 a 5 pour le niveau 1, 1 a 4 pour le niveau 2 et 1 a 3 pour le niveau 3) ou bien 0 si vous souhaitez reserver la carte non visible sur le dessus de la pioche du niveau choisi : ";
    std::cin >> num_carte;

    //partie.reserver({colonne_jeton, ligne_jeton}, niveau_carte, num_carte);

    std::cout << "Cette option n'est pas encore entierement implementee" << std::endl;

    return true;
}

bool InterfaceConsole::action_acheter(Joueur& joueur)
{
    std::cout << "Cette option n'est pas encore implementee" << std::endl;
    //A voir s'il ne vaut pas mieux renvoyer l'effet, la carte achet�e ou carrement ne pas faire de fonction en plus et tout mettre dans deroulement_tour
}
