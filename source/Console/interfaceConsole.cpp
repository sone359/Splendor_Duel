#include "interfaceConsole.h"
#include "../Back/Joueur.h"
#include <iostream>
#include <vector>
#include <array>
#include <stdexcept>

void InterfaceConsole::main()
{
    int fin_partie = 0;
    //pour test
    partie.get_joueur(1).setGemmes(StockGemmesOr(2,2,3,0,0,0,3));
    partie.get_joueur(2).setGemmes(StockGemmesOr(1,1,0,0,1,1,3));
    while(deroulement_tour() == true && fin_partie == 0)
    {
        fin_partie = partie.fin_tour();
    }
    if(fin_partie == 1)
    {
        std::cout << "Le joueur " << partie.joueur_actif() << " a plus de 20 points de prestige en tout et remporte la partie ! Felicitations !" << std::endl;
    }
    else if(fin_partie == 2)
    {
        std::cout << "Le joueur " << partie.joueur_actif() << " a plus de 10 couronnes et remporte la partie ! Felicitations !" << std::endl;
    }
    else if(fin_partie == 3)
    {
        std::cout << "Le joueur " << partie.joueur_actif() << " a plus de 10 points de prestige dans un type de gemme et remporte la partie ! Felicitations !" << std::endl;
    }
}

bool InterfaceConsole::deroulement_tour()
{
    //Affichage de l'etat de la partie
    afficherJoueur(partie.joueur_adverse());
    afficherPyramide();
    afficherPlateau();
    afficherJoueur(partie.joueur_actif());

    Joueur& joueur = partie.get_joueur(partie.joueur_actif());

    std::cout << "\nTour " << partie.get_tour()+1 << ", au joueur " << partie.joueur_actif() << " de jouer !" << std::endl << std::endl;

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
            afficherPlateau(); //Nouvel affichage du plateau � chaque privilege utilise, pour voir les changements
            unsigned int colonne = 0, ligne = 0;
            std::cout << "Quelle est la colonne du jeton a retirer ?";
            std::cin >> colonne;
            std::cout << "Quelle est la ligne du jeton a retirer ?";
            std::cin >> ligne;
            try
            {
                partie.utilise_privilege(joueur, colonne, ligne);
                afficherJetonsPossedes(partie.joueur_actif());
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
            afficherPlateau(); //Affichage du plateau pour visualiser les changements apport�s par le remplissage
        }
    }

    //Actions obligatoires
    bool fin_actions_obligatoires = false;
    while(!fin_actions_obligatoires)
    {
        std::cout << "Quelle action obligatoire souhaitez-vous effectuer ?\n1 - Prendre jusqu'a 3 jetons Gemme et/ou Perle\n2 - Prendre 1 jeton Or pour reserver 1 carte Joaillerie\n3 - Acheter 1 carte Joaillerie\n4 - Quitter la partie" << std::endl;
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
            else if(reponse == "4")
            {
                return false;
            }
            else
            {
                std::cout << "Saisie invalide, merci de rentrer 1, 2, 3 ou 4 et d'appuyer sur la touche Entree de votre clavier" << std::endl;
            }
        }
        catch (const SplendorException& except) //Si une erreur previsible liee aux regles du jeu (et non au programme directement) est intercept�e, on l'affiche et on propose � nouveau au joueur d'utiliser un privilege
        {
            std::cout << except.what() << std::endl;
        }
    }

    //Verification du nombre de jetons poss�d�s par le joueur actif
    while (total_stock(joueur.getGemmes()) > 10)
    {
        afficherJetonsPossedes(partie.joueur_actif());
        std::cout << "\nVous avez trop de jetons ! Entrez le type de jeton a remettre dans le sac (B, V, W, R, N, P ou O) : " << std::endl;
        std::string jeton_retire;
        std::cin >> jeton_retire;
        try
        {
            if(jeton_retire == "B" || jeton_retire == "b")
                partie.remettre_jeton(Bleu);
            else if(jeton_retire == "V" || jeton_retire == "v")
                partie.remettre_jeton(Vert);
            else if(jeton_retire == "W" || jeton_retire == "w")
                partie.remettre_jeton(Blanc);
            else if(jeton_retire == "R" || jeton_retire == "r")
                partie.remettre_jeton(Rouge);
            else if(jeton_retire == "N" || jeton_retire == "n")
                partie.remettre_jeton(Noir);
            else if(jeton_retire == "P" || jeton_retire == "p")
                partie.remettre_jeton(Perle);
            else if(jeton_retire == "O" || jeton_retire == "o")
                partie.remettre_jeton(Or);
            else
                std::cout << "Saisie invalide, merci de rentrer B, V, W, R, N, P ou O et d'appuyer sur la touche Entree de votre clavier" << std::endl;
        }
        catch (const SplendorException& except) //Si une erreur previsible liee aux regles du jeu (et non au programme directement) est intercept�e, on l'affiche et on propose � nouveau au joueur d'utiliser un privilege
        {
            std::cout << except.what() << std::endl;
        }
    }
    return true;
}

void InterfaceConsole::afficherJetonsPossedes(unsigned int num_joueur) const
{
    Joueur& joueur = partie.get_joueur(num_joueur);
    std::cout << "    " << "B x " << joueur.getGemmes().get_Bleu() << ", V x " << joueur.getGemmes().get_Vert() << ", W x " << joueur.getGemmes().get_Blanc() << ", R x " << joueur.getGemmes().get_Rouge() << ", N x " << joueur.getGemmes().get_Noir() << ", P x " << joueur.getGemmes().get_Perle() << ", O x " << joueur.getGemmes().get_Or() << std::endl << std::endl;
}

void InterfaceConsole::afficherPlateau() const
{
    std::cout<<"-------------------------PLATEAU--------------------------\n";
    std::cout << "        0 1 2 3 4 " << std::endl;
    std::cout << "        _ _ _ _ _ " << std::endl;
    for (int i = 0 ; i < 5 ; i++)
    {
        std::cout << "    " << i << " | ";
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
    std::cout << "        _ _ _ _ _ " << std::endl << std::endl;
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

    //Saisie des coordonnees du jeton 1
    afficherPlateau(); //Nouvel affichage du plateau � chaque privilege utilise, pour voir les changements
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
        //Saisie des coordonnees du jeton 2
        unsigned int colonne2 = 0, ligne2 = 0;
        std::cout << "Entrez la colonne du deuxieme jeton a retirer : ";
        std::cin >> colonne2;
        std::cout << "Entrez la ligne du deuxieme jeton a retirer : ";
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
            std::cout << "Entrez la colonne du troisieme jeton a retirer : ";
            std::cin >> colonne3;
            std::cout << "Entrez la ligne du troisieme jeton a retirer : ";
            std::cin >> ligne3;

            partie.retirer_jetons({colonne1, ligne1}, {colonne2, ligne2}, {colonne3, ligne3});
            return true;
        }
    }
}

bool InterfaceConsole::action_reserver(Joueur& joueur)
{
    unsigned int colonne_jeton = 0, ligne_jeton = 0, niveau_carte = 0, num_carte = 0;

    //Saisie des coordonnees du jeton Or a retirer
    afficherPlateau(); //Nouvel affichage du plateau pour permettre au joueur de plus facilement choisir son jeton Or
    std::cout << "Entrez la colonne du jeton Or a retirer : ";
    std::cin >> colonne_jeton;
    std::cout << "Entrez la ligne du jeton Or a retirer : ";
    std::cin >> ligne_jeton;

    //Saisie des coordonnees de la carte a reserver
    afficherPyramide(); //Nouvel affichage de la pyramide pour permettre au joueur de plus facilement choisir sa carte
    std::cout << "Entrez le niveau de la carte que vous souhaitez reserver : ";
    std::cin >> niveau_carte;
    std::cout << "Entrez le numero de la carte que vous souhaitez reserver (1 a 5 pour le niveau 1, 1 a 4 pour le niveau 2 et 1 a 3 pour le niveau 3) ou bien 0 si vous souhaitez reserver la carte non visible sur le dessus de la pioche du niveau choisi : ";
    std::cin >> num_carte;

    //partie.reserver({colonne_jeton, ligne_jeton}, niveau_carte, num_carte);
    partie.retirer_jetons_or({colonne_jeton,ligne_jeton});
    partie.reserver_carte(joueur, niveau_carte, num_carte);
    afficherPlateau();
    afficherJoueur(partie.joueur_actif());

    return true;
}

bool InterfaceConsole::action_acheter(Joueur& joueur)
{
    unsigned int niveau_carte,num_carte;

    std::string reponse="non";
    if(joueur.getCartesJoailleriesReservees().size()){
        std::cout<<"Souhaitez vous acheter une des cartes que vous avez reservees? (oui/non)";
        std::cin >> reponse;
    }
    while(reponse != "oui" && reponse!="non")
    {
        std::cout << "Saisie invalide, merci de rentrer oui ou non et d'appuyer sur Entree." << std::endl;   
        std::cin >> reponse;
    }
    if(reponse == "non"){
        afficherPyramide(); //Nouvel affichage de la pyramide pour permettre au joueur de plus facilement choisir sa carte
        //Saisie des coordonnees de la carte a reserver
        std::cout << "Entrez le niveau de la carte que vous souhaitez acheter : ";
        std::cin >> niveau_carte;
        std::cout << "Entrez le numero de la carte que vous souhaitez acheter (1 a 5 pour le niveau 1, 1 a 4 pour le niveau 2 et 1 a 3 pour le niveau 3)  : ";
        std::cin >> num_carte;
        //Ajouter une vérification que le joueur n'achète pas une carte avec un bonus Couleur (<=> type de bonus nul) alors qu'il n'a pas encore d'autre cartes
        gestion_effets(partie.acheter_carte(joueur, niveau_carte, num_carte));
        return true;
        //A voir s'il ne vaut pas mieux renvoyer l'effet, la carte achetee ou carrement ne pas faire de fonction en plus et tout mettre dans deroulement_tour
    }
    else
    {
        std::cout << "Entrez le numero de la carte que vous souhaitez acheter (à partir de 1)  : ";
        std::cin >> num_carte;
        gestion_effets(joueur.acheterCarteReservee(num_carte));        
        //gestion_effets(partie.acheter_carte(joueur, niveau_carte, num_carte));
        return true;
    }
    
}

void InterfaceConsole::gestion_effets(CarteJoaillerie& carte)
{
    Joueur& joueur = partie.get_joueur(partie.joueur_actif());

    for(unsigned int pos = 0 ; pos < carte.get_capacite().size() ; pos++)
    {
        switch (carte.get_capacite()[pos])
        {
        case rejouer:
            {
                std::cout << "Activation de l'effet Rejouer de la carte !" << std::endl;
                partie.ajouter_rejouer();
            }
            break;

        case couleur:
            {
                bool continuer = true;
                while (continuer == true)
                {
                    afficherJoueur(partie.joueur_actif());
                    std::cout << "Activation de l'effet Couleur de la carte ! Entrez le type de bonus que la carte achetee doit prendre (B, V, W, R ou N) (il doit correspondre a l'une de vos cartes) : " << std::endl;
                    std::string type_bonus;
                    std::cin >> type_bonus;
                    if(type_bonus == "B" || type_bonus == "b")
                    {
                        if(joueur.getBonus().get_Bleu() == 0)
                        {
                            std::cout << "Vous n'avez pas de carte bleue ! Veuillez choisir un type de bonus que vous possedez." << std::endl;
                        }
                        else
                        {
                            StockGemmes nouveau_bonus = StockGemmes(carte.get_nbBonus());
                            carte.setTypeBonus(nouveau_bonus);
                            joueur.setBonus(joueur.getBonus()+nouveau_bonus);
                            continuer = false;
                        }
                    }
                    else if(type_bonus == "V" || type_bonus == "v")
                    {
                        if(joueur.getBonus().get_Vert() == 0)
                        {
                            std::cout << "Vous n'avez pas de carte verte ! Veuillez choisir un type de bonus que vous possedez." << std::endl;
                        }
                        else
                        {
                            StockGemmes nouveau_bonus = StockGemmes(0, carte.get_nbBonus());
                            carte.setTypeBonus(nouveau_bonus);
                            joueur.setBonus(joueur.getBonus()+nouveau_bonus);
                            continuer = false;
                        }
                    }
                    else if(type_bonus == "W" || type_bonus == "w")
                    {
                        if(joueur.getBonus().get_Blanc() == 0)
                        {
                            std::cout << "Vous n'avez pas de carte blanche ! Veuillez choisir un type de bonus que vous possedez." << std::endl;
                        }
                        else
                        {
                            StockGemmes nouveau_bonus = StockGemmes(0, 0, carte.get_nbBonus());
                            carte.setTypeBonus(nouveau_bonus);
                            joueur.setBonus(joueur.getBonus()+nouveau_bonus);
                            continuer = false;
                        }
                    }
                    else if(type_bonus == "R" || type_bonus == "r")
                    {
                        if(joueur.getBonus().get_Rouge() == 0)
                        {
                            std::cout << "Vous n'avez pas de carte rouge ! Veuillez choisir un type de bonus que vous possedez." << std::endl;
                        }
                        else
                        {
                            StockGemmes nouveau_bonus = StockGemmes(0, 0, 0, carte.get_nbBonus());
                            carte.setTypeBonus(nouveau_bonus);
                            joueur.setBonus(joueur.getBonus()+nouveau_bonus);
                            continuer = false;
                        }
                    }
                    else if(type_bonus == "N" || type_bonus == "n")
                    {
                        if(joueur.getBonus().get_Noir() == 0)
                        {
                            std::cout << "Vous n'avez pas de carte noire ! Veuillez choisir un type de bonus que vous possedez." << std::endl;
                        }
                        else
                        {
                            StockGemmes nouveau_bonus = StockGemmes(0, 0, 0, 0, carte.get_nbBonus());
                            carte.setTypeBonus(nouveau_bonus);
                            joueur.setBonus(joueur.getBonus()+nouveau_bonus);
                            continuer = false;
                        }
                    }
                    else
                        std::cout << "Saisie invalide, merci de rentrer B, V, W, R ou N et d'appuyer sur la touche Entree de votre clavier" << std::endl;
                }
            }
            break;

        case gemme:
            {
                Jeton type_carte = Nul;
                StockGemmes stockBonus = carte.get_typeBonus();
                if (stockBonus.get_Bleu() > 0) {type_carte = Bleu;}
                else if (stockBonus.get_Vert() > 0) {type_carte = Vert;}
                else if (stockBonus.get_Blanc() > 0) {type_carte = Blanc;}
                else if (stockBonus.get_Rouge() > 0) {type_carte = Rouge;}
                else if (stockBonus.get_Noir() > 0) {type_carte = Noir;}
                else {throw std::logic_error("La carte passee en parametre possède un type de bonus incorrect (Or ou Perle) ou nul ce qui empeche le traitement de l'effet gemme et traduit sans doute une erreur de conception des cartes. Peut-etre l'erreur vient-elle d'un effet gemme place avant un effet couleur.");}
                //Verification de la presence d'un jeton correspondant sur le plateau
                bool present = false;
                for (int i = 0 ; i < 5 ; i++)
                {
                    for (int j = 0 ; j < 5 ; j++)
                    {
                        if (partie.get_plateau()[j][i] == type_carte)
                        {
                            present = true;
                            break;
                        }
                    }
                    if (present == true)
                    {
                        break;
                    }
                }
                if(present)
                {
                    std::cout << "Activation de l'effet Gemme de la carte !" << std::endl;
                    unsigned int colonne = 0, ligne = 0;
                    do
                    {
                        //Saisie des coordonnees du jeton à récupérer
                        afficherPlateau(); //Nouvel affichage du plateau pour faciliter le choix de jeton du joueur
                        std::cout << "Entrez la colonne du jeton a retirer (il doit etre de la couleur de la carte que vous avez achetee) : ";
                        std::cin >> colonne;
                        std::cout << "Entrez la ligne du jeton a retirer (il doit etre de la couleur de la carte que vous avez achetee) : ";
                        std::cin >> ligne;
                        if(partie.get_plateau()[colonne][ligne] != type_carte)
                            std::cout << "Ce jeton n'est pas de la meme couleur que la carte que vous avez achetee !\n" << std::endl;
                    } while (partie.get_plateau()[colonne][ligne] != type_carte);
                    partie.retirer_jetons({colonne, ligne});
                }
                else{std::cout << "Aucun jeton du plateau ne correspond a la couleur de la carte que vous avez achetee, l'effet Gemme de la carte n'a pas pu etre active" << std::endl;}
            }
            break;

        case privilege:
            std::cout << "Activation de l'effet Privilege de la carte !" << std::endl;
            partie.prend_privilege(joueur);
            break;

        case voler:
            bool continuer = true;
            while (continuer == true)
            {
                afficherJetonsPossedes(partie.joueur_adverse());
                std::cout << "Activation de l'effet Voler de la carte ! Entrez le type de jeton a prendre a votre adversaire (B, V, W, R, N ou P) : " << std::endl;
                std::string jeton_retire;
                std::cin >> jeton_retire;
                try{
                    if(jeton_retire == "B" || jeton_retire == "b")
                    {
                        partie.voler(joueur, partie.get_joueur(partie.joueur_adverse()), Bleu);
                        continuer = false;
                    }
                    else if(jeton_retire == "V" || jeton_retire == "v")
                    {
                        partie.voler(joueur, partie.get_joueur(partie.joueur_adverse()), Vert);
                        continuer = false;
                    }
                    else if(jeton_retire == "W" || jeton_retire == "w")
                    {
                        partie.voler(joueur, partie.get_joueur(partie.joueur_adverse()), Blanc);
                        continuer = false;
                    }
                    else if(jeton_retire == "R" || jeton_retire == "r")
                    {
                        partie.voler(joueur, partie.get_joueur(partie.joueur_adverse()), Rouge);
                        continuer = false;
                    }
                    else if(jeton_retire == "N" || jeton_retire == "n")
                    {
                        partie.voler(joueur, partie.get_joueur(partie.joueur_adverse()), Noir);
                        continuer = false;
                    }
                    else if(jeton_retire == "P" || jeton_retire == "p")
                    {
                        partie.voler(joueur, partie.get_joueur(partie.joueur_adverse()), Perle);
                        continuer = false;
                    }
                    else
                        std::cout << "Saisie invalide, merci de rentrer B, V, W, R, N ou P et d'appuyer sur la touche Entree de votre clavier" << std::endl;
                }
                catch (const SplendorException& except) //Si le jeton demande n'est pas possede par le joueur adverse, il faut l'intercepter des maintenant pour rester dans la boucle
                {
                    std::cout << except.what() << std::endl;
                }
            }
        }
    }
}

void InterfaceConsole::gestion_effets(CarteRoyale& carte)
{
    Joueur& joueur = partie.get_joueur(partie.joueur_actif());

    switch (carte.getCapacite())
    {
    case rejouer:
        {
            std::cout << "Activation de l'effet Rejouer de la carte !" << std::endl;
            partie.ajouter_rejouer();
        }
        break;

    case privilege:
        std::cout << "Activation de l'effet Privilege de la carte !" << std::endl;
        partie.prend_privilege(joueur);
        break;

    case voler:
        bool continuer = true;
        while (continuer == true)
        {
            afficherJetonsPossedes(partie.joueur_adverse());
            std::cout << "Activation de l'effet Voler de la carte ! Entrez le type de jeton a prendre a votre adversaire (B, V, W, R, N ou P) : " << std::endl;
            std::string jeton_retire;
            std::cin >> jeton_retire;
            try{
                if(jeton_retire == "B" || jeton_retire == "b")
                {
                    partie.voler(joueur, partie.get_joueur(partie.joueur_adverse()), Bleu);
                    continuer = false;
                }
                else if(jeton_retire == "V" || jeton_retire == "v")
                {
                    partie.voler(joueur, partie.get_joueur(partie.joueur_adverse()), Vert);
                    continuer = false;
                }
                else if(jeton_retire == "W" || jeton_retire == "w")
                {
                    partie.voler(joueur, partie.get_joueur(partie.joueur_adverse()), Blanc);
                    continuer = false;
                }
                else if(jeton_retire == "R" || jeton_retire == "r")
                {
                    partie.voler(joueur, partie.get_joueur(partie.joueur_adverse()), Rouge);
                    continuer = false;
                }
                else if(jeton_retire == "N" || jeton_retire == "n")
                {
                    partie.voler(joueur, partie.get_joueur(partie.joueur_adverse()), Noir);
                    continuer = false;
                }
                else if(jeton_retire == "P" || jeton_retire == "p")
                {
                    partie.voler(joueur, partie.get_joueur(partie.joueur_adverse()), Perle);
                    continuer = false;
                }
                else
                    std::cout << "Saisie invalide, merci de rentrer B, V, W, R, N ou P et d'appuyer sur la touche Entree de votre clavier" << std::endl;
            }
            catch (const SplendorException& except) //Si le jeton demande n'est pas possede par le joueur adverse, il faut l'intercepter des maintenant pour rester dans la boucle
            {
                std::cout << except.what() << std::endl;
            }
        }
    }
}

void InterfaceConsole::afficherPyramide() const{
    std::cout<<"-------------------------PYRAMIDE--------------------------\n";
    for(int j=3;j>=1;j--){
        for(int l=1;l<8;l++){
            for(int p=0;p<j*4;p++)std::cout<<" ";
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
            os << "| PP:"<<c.get_pointsPrestige()<<" |" ;
            return;
        case 4:
            os<<"| ";
            switch (c.get_capacite()[0])
            {
            case 0:
                os<<"REJ";
                break;
            case 1:
                os<<"PRV";
                break;
            case 2:
                os<<"CLR";
                break;
            case 3:
                os<<"GEM";
                break;
            case 4:
                os<<"VOL";
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

void InterfaceConsole::afficherJoueur(unsigned int joueur) const{
    size_t nbresa=partie.get_joueur(joueur).getCartesJoailleriesReservees().size();
    size_t nbposs=partie.get_joueur(joueur).getCartesJoailleriesPossedees().size();
    std::cout<<"------Joueur "<<joueur<<"---------------------------------------------------\n";
    std::cout<<"    Cartes Reservees \n";
    for(CarteJoaillerie carte : partie.get_joueur(joueur).getCartesJoailleriesReservees()){
        for(int l=1;l<8;l++){
            for (int i = 1; i <= nbresa; i++)
            {
                afficherCarteparligne(carte,l,std::cout);
                std::cout<<' ';
            }
        std::cout<<'\n';
        }
    }
    std::cout<<"    Cartes Possedees \n";
    for(CarteJoaillerie carte : partie.get_joueur(joueur).getCartesJoailleriesPossedees()){
        for(int l=1;l<8;l++){
            for (int i = 1; i <= nbposs; i++)
            {
                afficherCarteparligne(carte,l,std::cout);
                std::cout<<' ';
            }
        std::cout<<'\n';
        }
    }
    std::cout<<"\n    Jetons Possedes \n";
    afficherJetonsPossedes(joueur);
    /*
    for (int i=0;i<partie.get_joueur(joueur).getGemmes().get_Bleu();i++) std::cout<<'B';
    for (int i=0;i<partie.get_joueur(joueur).getGemmes().get_Blanc();i++) std::cout<<'W';
    for (int i=0;i<partie.get_joueur(joueur).getGemmes().get_Vert();i++) std::cout<<'V';
    for (int i=0;i<partie.get_joueur(joueur).getGemmes().get_Rouge();i++) std::cout<<'R';
    for (int i=0;i<partie.get_joueur(joueur).getGemmes().get_Noir();i++) std::cout<<'N';
    for (int i=0;i<partie.get_joueur(joueur).getGemmes().get_Perle();i++) std::cout<<'P';
    for (int i=0;i<partie.get_joueur(joueur).getGemmes().get_Or();i++) std::cout<<'O';
    std::cout<<"\n"<<partie.get_joueur(joueur).getNbPrivileges()<<" privileges, ";
    std::cout<<partie.get_joueur(joueur).getNbCouronnes()<<" couronnes\n";*/




    //std::cout <<"\nPrivileges : "<< j.getNbPrivileges() << "\nCouronnes : " << j.getNbCouronnes()<<'\n';
    //    os << "  Cartes Joailleries Possedees:\n";
    //    for (const auto& carte : j.getCartesJoailleriesPossedees()) {
    //        os << "    " << carte << "\n";
    //    }
    //    os << "  Cartes Joailleries Reservees:\n";
    //    for (const auto& carte : j.getCartesJoailleriesReservees()) {
    //        os << "    " << carte << "\n";
    //    }
    //    return os;
}

