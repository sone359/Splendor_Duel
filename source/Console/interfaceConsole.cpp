#include "interfaceConsole.h"
#include "../Back/Joueur.h"
#include <iostream>
#include <vector>
#include <array>
#include <stdexcept>
#include <unistd.h>

#ifdef _WIN32
    // Code spécifique à Windows
    #include <cstdlib>  // Pour system("cls")
#endif

InterfaceConsole::InterfaceConsole() : IA_joueur1(1), IA_joueur2(2)
{
    std::cout << "\e[8;75;159t";
    titre();
    int fin_partie = 0;
    std::string reponse="";
    std::cout << "Souhaitez-vous charger la partie en sauvegarde ? (oui/non)" << std::endl;
    while(reponse!="oui"){
        std::cin >> reponse;
        if(reponse == "non"){
            std::cout<<"Nouvelle partie\n";
            partie = Partie::get_partie();
            break;
            }
        if(reponse != "oui")
        {
            std::cout << "Saisie invalide, merci de rentrer oui ou non et d'appuyer sur la touche Entree de votre clavier" << std::endl;
        }
        else
        {
            partie = Partie::get_partie("../data/sauvegarde");
        }
    }
    reponse = "";
    std::cout << "Souhaitez-vous remplacer le joueur 1 par une Intelligence Artificielle ? (oui/non)" << std::endl;
    while(reponse!="oui" && reponse != "non"){
        std::cin >> reponse;
        if(reponse == "non"){
            statut_joueur1 = false;
        }
        else if(reponse != "oui")
        {
            std::cout << "Saisie invalide, merci de rentrer oui ou non et d'appuyer sur la touche Entree de votre clavier" << std::endl;
        }
        else
        {
            statut_joueur1 = true;
        }
    }
    reponse = "";
    std::cout << "Souhaitez-vous remplacer le joueur 2 par une Intelligence Artificielle ? (oui/non)" << std::endl;
    while(reponse!="oui" && reponse != "non"){
        std::cin >> reponse;
        if(reponse == "non"){
            statut_joueur2 = false;
        }
        else if(reponse != "oui")
        {
            std::cout << "Saisie invalide, merci de rentrer oui ou non et d'appuyer sur la touche Entree de votre clavier" << std::endl;
        }
        else
        {
            statut_joueur2 = true;
        }
    }
    bool continuer = true;
    while(continuer && fin_partie == 0)
    {
        if(get_statut_joueur_actif())
        {
            std::cout << "test1" << std::endl;
            try{
                continuer = get_IA_joueur_actif().deroulement_tour();
            }
            catch (const SplendorException& e)
            {
                std::cout << "L'IA a du mal a trouver une action a jouer, elle passe son tour" << std::endl;
            }
        }
        else
        {
            std::cout << "test2" << std::endl;
            continuer = deroulement_tour();
        }
        fin_partie = partie->fin_tour();
    }
    if(fin_partie == 1)
    {
        std::cout << "Le joueur " << partie->joueur_actif() << " a plus de 20 points de prestige en tout et remporte la partie ! Felicitations !" << std::endl;
    }
    else if(fin_partie == 2)
    {
        std::cout << "Le joueur " << partie->joueur_actif() << " a plus de 10 couronnes et remporte la partie ! Felicitations !" << std::endl;
    }
    else if(fin_partie == 3)
    {
        std::cout << "Le joueur " << partie->joueur_actif() << " a plus de 10 points de prestige dans un type de gemme et remporte la partie ! Felicitations !" << std::endl;
    }
    else{partie->sauvegarder();}
}

bool InterfaceConsole::deroulement_tour()
{
    afficherConsole();

    Joueur& joueur = partie->get_joueur(partie->joueur_actif());

    std::cout << "\nTour " << partie->get_tour()+1 << ", au joueur " << partie->joueur_actif() << " de jouer !" << std::endl << std::endl;

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
            unsigned int colonne = 0, ligne = 0;
            std::cout << "Quelle est la colonne du jeton a retirer ?";
            std::cin >> colonne;
            std::cout << "Quelle est la ligne du jeton a retirer ?";
            std::cin >> ligne;
            try
            {
                partie->utilise_privilege(joueur, colonne, ligne);
                afficherConsole();
            }
            catch (const SplendorException& except) //Si une erreur liee aux regles du jeu (et non au programme directement) est intercept�e, on l'affiche et on propose � nouveau au joueur d'utiliser un privilege
            {
                std::cout << except.what() << std::endl;
            }
        }
    }

    //Remplissage optionnel du plateau
    bool fin_remplissage = (partie->get_plateau().get_nbCasesVides() == 0);
    while(!fin_remplissage && !partie->sac_vide())
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
                partie->remplir_plateau(joueur);
                fin_remplissage = true;
                afficherConsole();
            }
            catch (const SplendorException& except) //Si une erreur liee aux regles du jeu (et non au programme directement) est intercept�e, on l'affiche et on propose � nouveau au joueur d'utiliser un privilege
            {
                std::cout << except.what() << std::endl;
            }
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
            afficherConsole();
        }
        catch (const SplendorException& except) //Si une erreur previsible liee aux regles du jeu (et non au programme directement) est intercept�e, on l'affiche et on propose � nouveau au joueur d'utiliser un privilege
        {
            std::cout << except.what() << std::endl;
        }
    }

    //Verification du nombre de jetons possedes par le joueur actif
    while (total_stock(joueur.getGemmes()) > 10)
    {
        afficherJetonsPossedes(partie->joueur_actif());
        std::cout << "\nVous avez trop de jetons ! Entrez le type de jeton a remettre dans le sac (B, V, W, R, N, P ou O) : " << std::endl;
        std::string jeton_retire;
        std::cin >> jeton_retire;
        try
        {
            if(jeton_retire == "B" || jeton_retire == "b")
                partie->remettre_jeton(Bleu);
            else if(jeton_retire == "V" || jeton_retire == "v")
                partie->remettre_jeton(Vert);
            else if(jeton_retire == "W" || jeton_retire == "w")
                partie->remettre_jeton(Blanc);
            else if(jeton_retire == "R" || jeton_retire == "r")
                partie->remettre_jeton(Rouge);
            else if(jeton_retire == "N" || jeton_retire == "n")
                partie->remettre_jeton(Noir);
            else if(jeton_retire == "P" || jeton_retire == "p")
                partie->remettre_jeton(Perle);
            else if(jeton_retire == "O" || jeton_retire == "o")
                partie->remettre_jeton(Or);
            else
                std::cout << "Saisie invalide, merci de rentrer B, V, W, R, N, P ou O et d'appuyer sur la touche Entree de votre clavier" << std::endl;
        }
        catch (const SplendorException& except) //Si une erreur previsible liee aux regles du jeu (et non au programme directement) est intercept�e, on l'affiche et on propose � nouveau au joueur d'utiliser un privilege
        {
            std::cout << except.what() << std::endl;
        }
    }
    //Verification de la possibilite d'obtenir une carte royale
    if (partie->get_cartes_royales().size() > 0 && (joueur.getNbCouronnes() >= 3 && joueur.getCartesRoyalesPossedees().size() == 0) && (joueur.getNbCouronnes() >= 6 && joueur.getCartesRoyalesPossedees().size() <= 1))
    {
        try
        {
            size_t num_carte;
            std::cout << "Vous avez rempli les conditions pour obtenir une carte Royale ! Entrez le numero de la carte Royale que vous souhaitez recuperer (1 a 4)  : ";
            std::cin >> num_carte;
            CarteRoyale& carte_recup = partie->recupererCarteRoyale(num_carte);
            gestion_effets(carte_recup);
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
    Joueur& joueur = partie->get_joueur(num_joueur);
    std::cout << "    " << "B x " << joueur.getGemmes().get_Bleu() << ", V x " << joueur.getGemmes().get_Vert() << ", W x " << joueur.getGemmes().get_Blanc() << ", R x " << joueur.getGemmes().get_Rouge() << ", N x " << joueur.getGemmes().get_Noir() << ", P x " << joueur.getGemmes().get_Perle() << ", O x " << joueur.getGemmes().get_Or();
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
            switch (partie->get_plateau()[j][i])
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
    //afficherPlateau(); //Nouvel affichage du plateau � chaque privilege utilise, pour voir les changements
    unsigned int colonne1 = 0, ligne1 = 0;
    std::cout << "Entrez la colonne du premier jeton a retirer : ";
    std::cin >> colonne1;
    std::cout << "Entrez la ligne du premier jeton a retirer : ";
    std::cin >> ligne1;

    if(nb_jetons == "1")
    {
        partie->retirer_jetons({colonne1, ligne1});
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
            partie->retirer_jetons({colonne1, ligne1}, {colonne2, ligne2});
            return true;
        }
        else
        {
            //Saisie des coordonnees du jeton 3
            unsigned int colonne3 = 0, ligne3 = 0;
            std::cout << "Entrez la colonne du troisieme jeton a retirer : ";
            std::cin >> colonne3;
            std::cout << "Entrez la ligne du troisieme jeton a retirer : ";
            std::cin >> ligne3;

            partie->retirer_jetons({colonne1, ligne1}, {colonne2, ligne2}, {colonne3, ligne3});
            return true;
        }
    }
}

bool InterfaceConsole::action_reserver(Joueur& joueur)
{
    unsigned int colonne_jeton = 0, ligne_jeton = 0, niveau_carte = 0, num_carte = 0;

    //Saisie des coordonnees du jeton Or a retirer
    //afficherPlateau(); //Nouvel affichage du plateau pour permettre au joueur de plus facilement choisir son jeton Or
    std::cout << "Entrez la colonne du jeton Or a retirer : ";
    std::cin >> colonne_jeton;
    std::cout << "Entrez la ligne du jeton Or a retirer (ou un nombre qui ne correspond à aucune ligne pour retourner au choix des actions) : ";
    std::cin >> ligne_jeton;
    if(ligne_jeton<0 || colonne_jeton<0 ||ligne_jeton>4 ||colonne_jeton>4){
        std::cout<< "\nCes coordonnees ne sont pas valides. Retour au menu.\n\n";
        return false;
    }

    //Saisie des coordonnees de la carte a reserver
    //afficherPyramide(); //Nouvel affichage de la pyramide pour permettre au joueur de plus facilement choisir sa carte
    std::cout << "Entrez le niveau de la carte que vous souhaitez reserver : ";
    std::cin >> niveau_carte;
    std::cout << "Entrez le numero de la carte que vous souhaitez reserver (1 a 5 pour le niveau 1, 1 a 4 pour le niveau 2 et 1 a 3 pour le niveau 3) ou bien 0 si vous souhaitez reserver la carte non visible sur le dessus de la pioche du niveau choisi : ";
    std::cin >> num_carte;

    //partie->reserver({colonne_jeton, ligne_jeton}, niveau_carte, num_carte);
    partie->retirer_jetons_or({colonne_jeton,ligne_jeton});
    partie->reserver_carte(joueur, niveau_carte, num_carte);
    //afficherPlateau();
    //afficherJoueur(partie->joueur_actif());

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
        //afficherPyramide(); //Nouvel affichage de la pyramide pour permettre au joueur de plus facilement choisir sa carte
        //Saisie des coordonnees de la carte a reserver
        std::cout << "Entrez le niveau de la carte que vous souhaitez acheter (ou un nombre superieur a 3 pour retourner au choix des actions): ";
        std::cin >> niveau_carte;
        if(niveau_carte<=0 || niveau_carte>3){
            std::cout<< "\nLe niveau est compris entre 1 et 3. Retour au menu.\n\n";
            return false;
        }
        std::cout << "Entrez le numero de la carte que vous souhaitez acheter (1 a 5 pour le niveau 1, 1 a 4 pour le niveau 2 et 1 a 3 pour le niveau 3)  : ";
        std::cin >> num_carte;
        //Ajouter une vérification que le joueur n'achète pas une carte avec un bonus Couleur (<=> type de bonus nul) alors qu'il n'a pas encore d'autre cartes
        gestion_effets(partie->acheter_carte(joueur, niveau_carte, num_carte));
        return true;
    }
    else
    {
        std::cout << "Entrez le numero de la carte que vous souhaitez acheter (à partir de 1)  : ";
        std::cin >> num_carte;
        gestion_effets(joueur.acheterCarteReservee(num_carte));
        //gestion_effets(partie->acheter_carte(joueur, niveau_carte, num_carte));
        return true;
    }

}

void InterfaceConsole::gestion_effets(CarteJoaillerie& carte)
{
    Joueur& joueur = partie->get_joueur(partie->joueur_actif());

    for(unsigned int pos = 0 ; pos < carte.get_capacite().size() ; pos++)
    {
        switch (carte.get_capacite()[pos])
        {
        case rejouer:
            {
                std::cout << "Activation de l'effet Rejouer de la carte !" << std::endl;
                partie->ajouter_rejouer();
            }
            break;

        case couleur:
            {
                bool continuer = true;
                while (continuer == true)
                {
                    //afficherJoueur(partie->joueur_actif());
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
                        if (partie->get_plateau()[j][i] == type_carte)
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
                        //afficherPlateau(); //Nouvel affichage du plateau pour faciliter le choix de jeton du joueur
                        std::cout << "Entrez la colonne du jeton a retirer (il doit etre de la couleur de la carte que vous avez achetee) : ";
                        std::cin >> colonne;
                        std::cout << "Entrez la ligne du jeton a retirer (il doit etre de la couleur de la carte que vous avez achetee) : ";
                        std::cin >> ligne;
                        if(partie->get_plateau()[colonne][ligne] != type_carte)
                            std::cout << "Ce jeton n'est pas de la meme couleur que la carte que vous avez achetee !\n" << std::endl;
                    } while (partie->get_plateau()[colonne][ligne] != type_carte);
                    partie->retirer_jetons({colonne, ligne});
                }
                else{std::cout << "Aucun jeton du plateau ne correspond a la couleur de la carte que vous avez achetee, l'effet Gemme de la carte n'a pas pu etre active" << std::endl;}
            }
            break;

        case privilege:
            std::cout << "Activation de l'effet Privilege de la carte !" << std::endl;
            partie->prend_privilege(joueur);
            break;

        case voler:
            bool continuer = true;
            while (continuer == true)
            {
                afficherJetonsPossedes(partie->joueur_adverse());
                std::cout << "Activation de l'effet Voler de la carte ! Entrez le type de jeton a prendre a votre adversaire (B, V, W, R, N ou P) : " << std::endl;
                std::string jeton_retire;
                std::cin >> jeton_retire;
                try{
                    if(jeton_retire == "B" || jeton_retire == "b")
                    {
                        partie->capacite_voler(joueur, partie->get_joueur(partie->joueur_adverse()), Bleu);
                        continuer = false;
                    }
                    else if(jeton_retire == "V" || jeton_retire == "v")
                    {
                        partie->capacite_voler(joueur, partie->get_joueur(partie->joueur_adverse()), Vert);
                        continuer = false;
                    }
                    else if(jeton_retire == "W" || jeton_retire == "w")
                    {
                        partie->capacite_voler(joueur, partie->get_joueur(partie->joueur_adverse()), Blanc);
                        continuer = false;
                    }
                    else if(jeton_retire == "R" || jeton_retire == "r")
                    {
                        partie->capacite_voler(joueur, partie->get_joueur(partie->joueur_adverse()), Rouge);
                        continuer = false;
                    }
                    else if(jeton_retire == "N" || jeton_retire == "n")
                    {
                        partie->capacite_voler(joueur, partie->get_joueur(partie->joueur_adverse()), Noir);
                        continuer = false;
                    }
                    else if(jeton_retire == "P" || jeton_retire == "p")
                    {
                        partie->capacite_voler(joueur, partie->get_joueur(partie->joueur_adverse()), Perle);
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
    Joueur& joueur = partie->get_joueur(partie->joueur_actif());

    switch (carte.getCapacite())
    {
    case rejouer:
        {
            std::cout << "Activation de l'effet Rejouer de la carte !" << std::endl;
            partie->ajouter_rejouer();
        }
        break;

    case privilege:
        std::cout << "Activation de l'effet Privilege de la carte !" << std::endl;
        partie->prend_privilege(joueur);
        break;

    case voler:
        bool continuer = true;
        while (continuer == true)
        {
            afficherJetonsPossedes(partie->joueur_adverse());
            std::cout << "Activation de l'effet Voler de la carte ! Entrez le type de jeton a prendre a votre adversaire (B, V, W, R, N ou P) : " << std::endl;
            std::string jeton_retire;
            std::cin >> jeton_retire;
            try{
                if(jeton_retire == "B" || jeton_retire == "b")
                {
                    partie->capacite_voler(joueur, partie->get_joueur(partie->joueur_adverse()), Bleu);
                    continuer = false;
                }
                else if(jeton_retire == "V" || jeton_retire == "v")
                {
                    partie->capacite_voler(joueur, partie->get_joueur(partie->joueur_adverse()), Vert);
                    continuer = false;
                }
                else if(jeton_retire == "W" || jeton_retire == "w")
                {
                    partie->capacite_voler(joueur, partie->get_joueur(partie->joueur_adverse()), Blanc);
                    continuer = false;
                }
                else if(jeton_retire == "R" || jeton_retire == "r")
                {
                    partie->capacite_voler(joueur, partie->get_joueur(partie->joueur_adverse()), Rouge);
                    continuer = false;
                }
                else if(jeton_retire == "N" || jeton_retire == "n")
                {
                    partie->capacite_voler(joueur, partie->get_joueur(partie->joueur_adverse()), Noir);
                    continuer = false;
                }
                else if(jeton_retire == "P" || jeton_retire == "p")
                {
                    partie->capacite_voler(joueur, partie->get_joueur(partie->joueur_adverse()), Perle);
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

void InterfaceConsole::afficherConsole() const{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    afficherJoueur(partie->joueur_adverse());
    for(unsigned int i=1;i<=22;i++){
        afficherPyramideparLigne(i,std::cout);
        if(i<14) afficherPlateauparLigne(i,std::cout);
        if(i==15||i==14) std::cout<<"                                         ";
        if(i>15) {
            for(int j=1;j<=4;j++){
            afficherCarteRoyaleparLigne(i-15,j,std::cout);
            std::cout<<" ";
            }
            std::cout<<"     ";
        }
        afficherReglesparLigne(i,std::cout);
        std::cout<<"\n";
    }
    afficherJoueur(partie->joueur_actif());
    std::cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

}

void InterfaceConsole::afficherPyramide() const{
    std::cout<<"-------------------------PYRAMIDE--------------------------\n";
    for(int j=3;j>=1;j--){//niveau
        for(int l=1;l<8;l++){//ligne de la carte
            for(int p=0;p<j*4;p++)std::cout<<" ";
            for (int i = 1; i <= partie->get_pyramide().getCartesRestantes(j); i++)
            {
                afficherCarteparligne(partie->get_pyramide().recupererCarteJoaillerie(j,i),l,std::cout);
                std::cout<<' ';
            }
        std::cout<<'\n';
        }
        std::cout<<'\n';
    }
}

void InterfaceConsole::afficherPyramideparLigne(unsigned int ligne, std::ostream& os) const{
    if (ligne<1 || ligne>22) throw SplendorException("La pyramide s'affiche en 22 lignes.\n");
    switch(ligne){
        case 1:
        os<<"----------------------------------PYRAMIDE----------------------------------";
        return;
    }
    if (ligne>1 && ligne<=8){
        os<<"                         ";
        for (int i = 1; i <= partie->get_pyramide().getCartesRestantes(3); i++)
            {
                afficherCarteparligne(partie->get_pyramide().recupererCarteJoaillerie(3,i),ligne-1,os);
            }
            os<<"                         ";
    }
    if (ligne>8 && ligne<=15){
        os<<"                     ";
        for (int i = 1; i <= partie->get_pyramide().getCartesRestantes(2); i++)
            {
                afficherCarteparligne(partie->get_pyramide().recupererCarteJoaillerie(2,i),(ligne-8),os);
            }
        os<<"                     ";
    }
    if (ligne>15 && ligne<=22){
        os<<"                 ";
        for (int i = 1; i <= partie->get_pyramide().getCartesRestantes(1); i++)
            {
                afficherCarteparligne(partie->get_pyramide().recupererCarteJoaillerie(1,i),(ligne-15),os);
            }
        os<<"                 ";
    }
}

void InterfaceConsole::afficherCarteparligne(const CarteJoaillerie& c,unsigned int ligne,std::ostream& os)const {
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
            if (c.get_capacite().size()>=2){
                os<<"|";
                for(int ca : c.get_capacite()){
                    switch (c.get_capacite()[ca])
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
                }
                os<<"|";
            }else{
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
            }
        return;
        case 5:
            os<<"|BVWRNP|";
            return;
        case 6:
            os<<c.get_cout();
            return;
        case 7:
        os<<"--------";
        return;
    }
}

void InterfaceConsole::afficherCarteRoyaleparLigne(unsigned int ligne, unsigned int carte,std::ostream& os)const{
    if (ligne<1 || ligne>7) throw SplendorException("Une carte s'affiche en 7 lignes.\n");
    if (carte<1 || carte>7) throw SplendorException("Il y a 4 cartes royales.\n");
    switch (ligne){
        case 1 :
            os<<"--|VV|--";
            return;
        case 2:
            switch (carte)
            {
            case 1:
                os<<"| .==- |";
                return;

            case 2:
                os<<"|.o88o.|";
                return;
            case 3:
                os<<"| |^^^||";
                return;
            case 4:
                os<<"| nnnn |";
                return;
            }
        case 3:
            switch (carte)
            {
            case 1:
                os<<"|//oo\\\\|";
                return;

            case 2:
                os<<"|8|u uB|";
                return;
            case 3:
                os<<"| (|\"|)|";
                return;
            case 4:
                os<<"|(/66\\)|";
                return;
            }
        case 4:
            switch (carte)
            {
            case 1:
                os<<"|\\|^./\\|";
                return;

            case 2:
                os<<"|8(°û )|";
                return;
            case 3:
                os<<"| /°I°\\|";
                return;
            case 4:
                os<<"|(;_-;)|";
                return;
            }
        case 5:
            switch (carte)
            {
            case 1:
                os<<"|//-V-||";
                return;

            case 2:
                os<<"|<//|\\\\|";
                return;
            case 3:
                os<<"|(!)--)|";
                return;
            case 4:
                os<<"|/|`*'||";
                return;
            }
        case 6:
            switch (carte)
            {
            case 1:
                os<<"|  GEM |";
                return;

            case 2:
                os<<"|  PRV |";
                return;
            case 3:
                os<<"|  REJ |";
                return;
            case 4:
                os<<"|      |";
                return;
            }
        case 7 :
        if (carte==4){os<<"----3---";return;}
        os<<"----2---";
        return;

    }
}


void InterfaceConsole::afficherPlateauparLigne(unsigned int ligne,std::ostream& os)const {
    if (ligne<1 || ligne>13) throw SplendorException("Le plateau s'affiche en 13 lignes.\n");
    switch (ligne){
        case 1:
        os<<"-----------------PLATEAU-----------------";
        return;
        break;
        case 2:
        os << "            0   1   2   3   4            " ;
        return;
        break;
        case 3:
        os << "          .-------------------.          " ;
        return;
        case 13 :
        os << "          °-------------------°          " ;
        return;

    }
    if (ligne>=4 && ligne%2==0){
        std::cout << "        " << (ligne-4)/2 << " | ";
        for (int j = 0 ; j < 5 ; j++)
        {
            switch (partie->get_plateau()[j][(ligne-4)/2])
            {
            case Nul:
                os << "-";
                break;
            case Bleu:
                os << "B";
                break;
            case Vert:
                os << "V";
                break;
            case Blanc:
                os << "W";
                break;
            case Rouge:
                os << "R";
                break;
            case Noir:
                os << "N";
                break;
            case Perle:
                os << "P";
                break;
            case Or:
                os << "O";
                break;
            }
        os << " | ";
        }
        os<<"         ";
        return;
    }
    if (ligne >=5) os<<"          |---+---+---+---+---|          ";
    return;
}
void InterfaceConsole::afficherReglesparLigne(unsigned int ligne,std::ostream& os)const{
    if (ligne<1 || ligne>22) throw SplendorException("La pyramide s'affiche en 22 lignes.\n");
    switch(ligne){
        case 1: os<<"-------------------REGLES----------------";return;
        case 3: os<<"|   - Le BUT DU JEU est d'avoir 20 points";return;
        case 4: os<<"|   de prestige, 10 couronnes, ou 10 po- ";return;
        case 5: os<<"|   ints de prestige d'une meme couleur, ";return;
        case 6: os<<"|   achetez des cartes pour y arriver    ";return;
        case 8: os<<"|   - Pendant un tour, vous pouvez d'ab- ";return;
        case 9: os<<"|   ord remplir le plateau ou utiliser   ";return;
        case 10: os<<"|   un privilege, puis realiser une des  ";return;
        case 11: os<<"|   4 actions obligatoires               ";return;
        case 13: os<<"|   - Les jetons que vous recuperez doi- ";return;
        case 14: os<<"|   vent etre adjacents sur une ligne    ";return;
        case 16: os<<"|   - Interdit d'avoir plus de 3 cartes  ";return;
        case 17: os<<"|   reservees ou plus de 10 jetons       ";return;
        case 19: os<<"|   - Vous obtenez 1 cartes royale quand ";return;
        case 20: os<<"|   vous avez 3 couronnes et une deuxi-  ";return;
        case 21: os<<"|   eme a 6 couronnes                    ";return;
    }
    std::cout<<"|                                        ";
}


void InterfaceConsole::afficherJoueur(unsigned int joueur) const{
    std::cout<<"------Joueur "<<joueur<<"-----------------------------------------------------------------------------------------------------------------------------------------------\n";
    if(joueur==partie->joueur_actif()){
        std::cout<<"    Cartes Reservees \n";
        for(CarteJoaillerie carte : partie->get_joueur(joueur).getCartesJoailleriesReservees()){
            for(int l=1;l<8;l++){
                    afficherCarteparligne(carte,l,std::cout);
                    std::cout<<' ';
            }
        }
        std::cout<<'\n';
    }
    std::cout<<"    Cartes Possedees \n";
    for(CarteJoaillerie carte : partie->get_joueur(joueur).getCartesJoailleriesPossedees()){
        for(int l=1;l<8;l++){
            afficherCarteparligne(carte,l,std::cout);
            std::cout<<' ';
            std::cout<<'\n';
        }
    }
    std::cout<<"\n    Jetons Possedes                                                                  Points Prestige                                  Couronnes           \n";
    std::cout<<' ';afficherJetonsPossedes(joueur);std::cout<<"                 "; afficherPrestige(joueur);std::cout<<"               ";partie->get_joueur(joueur).getNbCouronnes();std::cout<<"                         \n\n";
    std::cout<<'+';afficherBonus(joueur);std::cout<<"                                    Total Points Prestige :"<<partie->get_joueur(joueur).getNbPointsPrestige()<<'\n';
}

void InterfaceConsole::afficherPrestige(unsigned int num_joueur) const
{
    Joueur& joueur = partie->get_joueur(num_joueur);
    std::cout << "    " << "B x " << joueur.getPointsPrestigeCouleur().get_Bleu() << ", V x " << joueur.getPointsPrestigeCouleur().get_Vert() << ", W x " << joueur.getPointsPrestigeCouleur().get_Blanc() << ", R x " << joueur.getPointsPrestigeCouleur().get_Rouge() << ", N x " << joueur.getPointsPrestigeCouleur().get_Noir() << ", P x " << joueur.getPointsPrestigeCouleur().get_Perle();
}

void InterfaceConsole::afficherBonus(unsigned int num_joueur) const
{
    Joueur& joueur = partie->get_joueur(num_joueur);
    std::cout << "    " << "B x " << joueur.getBonus().get_Bleu() << ", V x " << joueur.getBonus().get_Vert() << ", W x " << joueur.getBonus().get_Blanc() << ", R x " << joueur.getBonus().get_Rouge() << ", N x " << joueur.getBonus().get_Noir() << ", P x " << joueur.getBonus().get_Perle();
}

void InterfaceConsole::titre()const{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    std::cout<<"\n\n\n\n\n\n\n\n";
    usleep(50000);
    std::cout<<"                               _#######             ###                             ##        "<<std::endl;
    usleep(50000);
    std::cout<<"                              /       ###            ###                             ##                        "<<std::endl;
    usleep(50000);
    std::cout<<"                             /         ##             ##                             ##                        "<<std::endl;
    usleep(50000);
    std::cout<<"                             ##        #              ##                             ##                        "<<std::endl;
    usleep(50000);
    std::cout<<"                              ###                     ##                             ##                        "<<std::endl;
    usleep(50000);
    std::cout<<"                             ## ###           /###    ##      /##  ###  /###     ### ##    /###   ###  /###    "<<std::endl;
    usleep(50000);
    std::cout<<"                              ### ###        / ###  / ##     / ###  ###/ #### / ######### / ###  / ###/ #### / "<<std::endl;
    usleep(50000);
    std::cout<<"                                ### ###     /   ###/  ##    /   ###  ##   ###/ ##   #### /   ###/   ##   ###/  "<<std::endl;
    usleep(50000);
    std::cout<<"                                  ### /##  ##    ##   ##   ##    ### ##    ##  ##    ## ##    ##    ##         "<<std::endl;
    usleep(50000);
    std::cout<<"                                    #/ /## ##    ##   ##   ########  ##    ##  ##    ## ##    ##    ##         "<<std::endl;
    usleep(50000);
    std::cout<<"                                     #/ ## ##    ##   ##   #######   ##    ##  ##    ## ##    ##    ##         "<<std::endl;
    usleep(50000);
    std::cout<<"                                      # /  ##    ##   ##   ##        ##    ##  ##    ## ##    ##    ##         "<<std::endl;
    usleep(50000);
    std::cout<<"                            /##        /   ##    ##   ##   ####    / ##    ##  ##    /# ##    ##    ##         "<<std::endl;
    usleep(50000);
    std::cout<<"                           /  ########/    #######    ### / ######/  ###   ###  ####/    ######     ###        "<<std::endl;
    usleep(50000);
    std::cout<<"                          /     #####      ######      ##/   #####    ###   ###  ###      ####       ###       "<<std::endl;
    usleep(50000);
    std::cout<<"                          |                ##                                                                  "<<std::endl;
    usleep(50000);
    std::cout<<"                           \\)              ##                                ##### ##                         ###     "<<std::endl;
    usleep(50000);
    std::cout<<"                                           ##                              /#####  /##                         ###    "<<std::endl;
    usleep(50000);
    std::cout<<"                                            ##                           //    /  / ###                         ##    "<<std::endl;
    usleep(50000);
    std::cout<<"                                                                        /     /  /   ###                        ##    "<<std::endl;
    usleep(50000);
    std::cout<<"                                                                             /  /     ###                       ##    "<<std::endl;
    usleep(50000);
    std::cout<<"                                                                            ## ##      ## ##    ###      /##    ##    "<<std::endl;
    usleep(50000);
    std::cout<<"                                                                            ## ##      ##  ##     ##  / / ###   ##    "<<std::endl;
    usleep(50000);
    std::cout<<"                                                                            ## ##      ##  ##      ##/ /   ###  ##    "<<std::endl;
    usleep(50000);
    std::cout<<"                                                                            ## ##      ##  ##      ## ##    ### ##    "<<std::endl;
    usleep(50000);
    std::cout<<"                                                                            ## ##      ##  ##      ## ########  ##    "<<std::endl;
    usleep(50000);
    std::cout<<"                                                                            #  ##      ##  ##      ## #######   ##    "<<std::endl;
    usleep(50000);
    std::cout<<"                                                                               /       /   ##      ## ##        ##    "<<std::endl;
    usleep(50000);
    std::cout<<"                                                                          /###/       /    ##      /# ####    / ##    "<<std::endl;
    usleep(50000);
    std::cout<<"                                                                         /   ########/      ######/ ## ######/  ### / "<<std::endl;
    usleep(50000);
    std::cout<<"                                                                        /       ####         #####   ## #####    ##/  "<<std::endl;
    usleep(50000);
    std::cout<<"                                                                        #  "<<std::endl;
    usleep(50000);
    std::cout<<"                                                                         ## \n\n\n"<<std::endl;
    sleep(2);
    std::cout<<"Adaptation par Simon Biffe, Ahmed Bouzidi, Ismail Essagar et Marie Herminie Blondy.\n\n";
    sleep(3);
}

bool InterfaceConsole::get_statut_joueur_actif()
{
    if(partie->joueur_actif() == 1)
        return statut_joueur1;
    return statut_joueur2;
}

IA1& InterfaceConsole::get_IA_joueur_actif()
{
    if(partie->joueur_actif() == 1)
        return IA_joueur1;
    return IA_joueur2;
}
