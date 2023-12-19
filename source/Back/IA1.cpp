#include "IA1.h"

bool IA1::prendre_3_jetons()
{
    int jetons_cible_max = -1; //Il est necessaire d'initialiser le compteur inférieur à 0 de manière a toujours avoir une combinaison de cases valides meme si elle ne contient aucun jeton vise
    unsigned int jetons_cible_temp = 0;
    std::array<unsigned int, 2> coor_jeton1;
    std::array<unsigned int, 2> coor_jeton2;
    std::array<unsigned int, 2> coor_jeton3;
    for (size_t i = 0 ; i < 3 ; i++)
    {
        for (size_t j = 0 ; j < 5 ; j++)
        {
            //Test des combinaisons horizontales
            jetons_cible_temp = 0;
            if (partie.get_plateau()[i][j] != Nul && partie.get_plateau()[i+1][j] != Nul && partie.get_plateau()[i+2][j] != Nul
                && partie.get_plateau()[i][j] != Or && partie.get_plateau()[i+1][j] != Or && partie.get_plateau()[i+2][j] != Or)
            {
                if (jetons_cible.inclus(partie.get_plateau()[i][j])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i+1][j])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i+2][j])) {jetons_cible_temp++;}

                if (jetons_cible_temp == 3 || jetons_cible_temp == total_stock(jetons_cible))
                {
                    getPartie().retirer_jetons({i, j}, {i+1, j}, {i+2, j});
                    return true;
                }
                if (jetons_cible_temp > jetons_cible_max)
                {
                    jetons_cible_max = jetons_cible_temp;
                    coor_jeton1 = {i, j};
                    coor_jeton2 = {i+1, j};
                    coor_jeton3 = {i+2, j};
                }
            }
            //Test des combinaisons verticales
            jetons_cible_temp = 0;
            if (partie.get_plateau()[j][i] != Nul && partie.get_plateau()[j][i+1] != Nul && partie.get_plateau()[j][i+2] != Nul
                && partie.get_plateau()[j][i] != Or && partie.get_plateau()[j][i+1] != Or && partie.get_plateau()[j][i+2] != Or)
            {
                if (jetons_cible.inclus(partie.get_plateau()[j][i])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[j][i+1])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[j][i+2])) {jetons_cible_temp++;}

                if (jetons_cible_temp == 3 || jetons_cible_temp == total_stock(jetons_cible))
                {
                    getPartie().retirer_jetons({j, i}, {j, i+1}, {j, i+2});
                    return true;
                }
                if (jetons_cible_temp > jetons_cible_max)
                {
                    jetons_cible_max = jetons_cible_temp;
                    coor_jeton1 = {j, i};
                    coor_jeton2 = {j, i+1};
                    coor_jeton3 = {j, i+2};
                }
            }
        }
        //Test des combinaisons diagonales
        jetons_cible_temp = 0;
        for (size_t j = 0 ; j < 3-i ; j++)
        {
            if (partie.get_plateau()[i][i+j] != Nul && partie.get_plateau()[i+1][i+j+1] != Nul && partie.get_plateau()[i+2][i+j+2] != Nul
                && partie.get_plateau()[i][i+j] != Or && partie.get_plateau()[i+1][i+j+1] != Or && partie.get_plateau()[i+2][i+j+2] != Or)
            {
                if (jetons_cible.inclus(partie.get_plateau()[i][i+j])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i+1][i+j+1])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i+2][i+j+2])) {jetons_cible_temp++;}

                if (jetons_cible_temp == 3 || jetons_cible_temp == total_stock(jetons_cible))
                {
                    getPartie().retirer_jetons({i, i+j}, {i+1, i+j+1}, {i+2, i+j+2});
                    return true;
                }
                if (jetons_cible_temp > jetons_cible_max)
                {
                    jetons_cible_max = jetons_cible_temp;
                    coor_jeton1 = {i, i+j};
                    coor_jeton2 = {i+1, i+j+1};
                    coor_jeton3 = {i+2, i+j+2};
                }
            }
            if (partie.get_plateau()[i+j][i] != Nul && partie.get_plateau()[i+j+1][i+1] != Nul && partie.get_plateau()[i+j+2][i+2] != Nul
                && partie.get_plateau()[i+j][i] != Or && partie.get_plateau()[i+j+1][i+1] != Or && partie.get_plateau()[i+j+2][i+2] != Or)
            {
                if (jetons_cible.inclus(partie.get_plateau()[i+j][i])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i+j+1][i+1])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i+j+2][i+2])) {jetons_cible_temp++;}

                if (jetons_cible_temp == 3 || jetons_cible_temp == total_stock(jetons_cible))
                {
                    getPartie().retirer_jetons({i+j, i}, {i+j+1, i+1}, {i+j+2, i+2});
                    return true;
                }
                if (jetons_cible_temp > jetons_cible_max)
                {
                    jetons_cible_max = jetons_cible_temp;
                    coor_jeton1 = {i+j, i};
                    coor_jeton2 = {i+j+1, i+1};
                    coor_jeton3 = {i+j+2, i+2};
                }
            }
        }
    }
    if (jetons_cible_temp == 2 || jetons_cible_temp == total_stock(jetons_cible))
    {
        getPartie().retirer_jetons(coor_jeton1, coor_jeton2, coor_jeton3);
        return true;
    }
    return false;
}

bool IA1::prendre_2_jetons()
{
    int jetons_cible_max = -1; //Il est necessaire d'initialiser le compteur inférieur à 0 de manière a toujours avoir une combinaison de cases valides meme si elle ne contient aucun jeton vise
    unsigned int jetons_cible_temp = 0;
    std::array<unsigned int, 2> coor_jeton1;
    std::array<unsigned int, 2> coor_jeton2;
    for (size_t i = 0 ; i < 4 ; i++)
    {
        for (size_t j = 0 ; j < 5 ; j++)
        {
            //Test des combinaisons horizontales
            jetons_cible_temp = 0;
            if (partie.get_plateau()[i][j] != Nul && partie.get_plateau()[i+1][j] != Nul
                && partie.get_plateau()[i][j] != Or && partie.get_plateau()[i+1][j] != Or)
            {
                if (jetons_cible.inclus(partie.get_plateau()[i][j])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i+1][j])) {jetons_cible_temp++;}

                if (jetons_cible_temp == 2 || jetons_cible_temp == total_stock(jetons_cible))
                {
                    //Prendre les jetons
                    getPartie().retirer_jetons({i, j}, {i+1, j});
                    return true;
                }
                if (jetons_cible_temp > jetons_cible_max)
                {
                    jetons_cible_max = jetons_cible_temp;
                    coor_jeton1 = {i, j};
                    coor_jeton2 = {i+1, j};
                }
            }
            //Test des combinaisons verticales
            jetons_cible_temp = 0;
            if (partie.get_plateau()[j][i] != Nul && partie.get_plateau()[j][i] != Nul
                && partie.get_plateau()[j][i] != Or && partie.get_plateau()[j][i] != Or)
            {
                if (jetons_cible.inclus(partie.get_plateau()[j][i])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[j][i+1])) {jetons_cible_temp++;}

                if (jetons_cible_temp == 2 || jetons_cible_temp == total_stock(jetons_cible))
                {
                    //Prendre les jetons
                    getPartie().retirer_jetons({j, i}, {j, i+1});
                    return true;
                }
                if (jetons_cible_temp > jetons_cible_max)
                {
                    jetons_cible_max = jetons_cible_temp;
                    coor_jeton1 = {j, i};
                    coor_jeton2 = {j, i+1};
                }
            }
        }
        //Test des combinaisons diagonales
        jetons_cible_temp = 0;
        for (size_t j = 0 ; j < 4-i ; j++)
        {
            if (partie.get_plateau()[i][i+j] != Nul && partie.get_plateau()[i+1][i+j+1] != Nul
                && partie.get_plateau()[i][i+j] != Or && partie.get_plateau()[i+1][i+j+1] != Or)
            {
                if (jetons_cible.inclus(partie.get_plateau()[i][i+j])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i+1][i+j+1])) {jetons_cible_temp++;}

                if (jetons_cible_temp == 2 || jetons_cible_temp == total_stock(jetons_cible))
                {
                    //Prendre les jetons
                    getPartie().retirer_jetons({i, i+j}, {i+1, i+j+1});
                    return true;
                }
                if (jetons_cible_temp > jetons_cible_max)
                {
                    jetons_cible_max = jetons_cible_temp;
                    coor_jeton1 = {i, i+j};
                    coor_jeton2 = {i+1, i+j+1};
                }
            }
            if (partie.get_plateau()[i+j][i] != Nul && partie.get_plateau()[i+j+1][i+1] != Nul
                && partie.get_plateau()[i+j][i] != Or && partie.get_plateau()[i+j+1][i+1] != Or)
            {
                if (jetons_cible.inclus(partie.get_plateau()[i+j][i])) {jetons_cible_temp++;}
                if (jetons_cible.inclus(partie.get_plateau()[i+j+1][i+1])) {jetons_cible_temp++;}

                if (jetons_cible_temp == 2 || jetons_cible_temp == total_stock(jetons_cible))
                {
                    //Prendre les jetons
                    getPartie().retirer_jetons({i+j, i}, {i+j+1, i+1});
                    return true;
                }
                if (jetons_cible_temp > jetons_cible_max)
                {
                    jetons_cible_max = jetons_cible_temp;
                    coor_jeton1 = {i+j, i};
                    coor_jeton2 = {i+j+1, i+1};
                }
            }
        }
    }
    if (jetons_cible_temp == 1 || jetons_cible_temp == total_stock(jetons_cible))
    {
        //Prendre les jetons
        getPartie().retirer_jetons(coor_jeton1, coor_jeton2);
        return true;
    }
    return false;
}

bool IA1::prendre_1_jetons()
{
    int jetons_cible_max = -1; //Il est necessaire d'initialiser le compteur inférieur à 0 de manière a toujours avoir une combinaison de cases valides meme si elle ne contient aucun jeton vise
    unsigned int jetons_cible_temp = 0;
    std::array<unsigned int, 2> coor_jeton1;
    for (size_t i = 0 ; i < 4 ; i++)
    {
        for (size_t j = 0 ; j < 5 ; j++)
        {
            //Test des combinaisons horizontales
            jetons_cible_temp = 0;
            if (partie.get_plateau()[i][j] != Nul && partie.get_plateau()[i][j] != Or)
            {
                if (jetons_cible.inclus(partie.get_plateau()[i][j]))
                {
                    //Prendre les jetons
                    getPartie().retirer_jetons({i, j});
                    return true;
                }
                if (0 > jetons_cible_max)
                {
                    jetons_cible_max = 0;
                    coor_jeton1 = {i, j};
                }
            }
        }
    }
    if (jetons_cible_temp == 0)
    {
        //Prendre les jetons
        getPartie().retirer_jetons(coor_jeton1);
        return true;
    }
    return false;
}

float IA1::valeur(CarteJoaillerie& carte)
{
    float n_valeur = 0;
    if (getPartie().get_joueur(num_joueur).getPointsPrestigeCouleur().max() == carte.get_typeBonus().max())
    {
        n_valeur += carte.get_pointsPrestige()*1.2;
    }
    else
    {
        n_valeur += carte.get_pointsPrestige();
    }
    for (size_t i = 0 ; i < carte.get_capacite().size() ; i++)
    {
        if (carte.get_capacite()[i] != couleur) {n_valeur += 0.75;}
    }
    n_valeur += carte.get_nbBonus()*0.5;
    n_valeur += carte.get_couronnes()*0.9;

    return n_valeur;
}

bool IA1::deroulement_tour(bool test)
{
    Joueur& joueur = getPartie().get_joueur(num_joueur);
    //Recherche de la carte Joaillerie cible
    float rapport_max = -1000;
    size_t niveau_max = 0;
    size_t num_max = 0;

    for (size_t niveau = 1 ; niveau < 4 ; niveau++)
    {
        for (size_t num = 1 ; num < 7-niveau ; num++)
        {
            CarteJoaillerie carte_temp = getPartie().get_pyramide().recupererCarteJoaillerie(niveau, num);
            //Verification de la validite de la carte
            bool valide = true;
            for (size_t i=0 ; i < carte_temp.get_capacite().size() ; i++)
            {
                if(carte_temp.get_capacite()[i] == couleur && joueur.getCartesJoailleriesPossedees().size() == 0)
                {
                    valide = false;
                    break;
                }
            }

            if (valide)
            {
                StockGemmes manque = (joueur.getGemmes()+joueur.getBonus())/carte_temp.get_cout();
                int prix = manque.total_gemmes();
                float rapport_temp = -1000;
                if(prix >= 10)
                {
                    rapport_temp = valeur(carte_temp)/(prix*10);
                }
                else
                {
                    rapport_temp = valeur(carte_temp)/prix;
                }

                if (rapport_temp > rapport_max)
                {
                    rapport_max = rapport_temp;
                    jetons_cible = manque;
                    niveau_max = niveau;
                    num_max = num;
                }
            }
        }
    }

    if (total_stock(jetons_cible) == 0)
    {
        gestion_effets(partie.acheter_carte(joueur, niveau_max, num_max));
    }
    else
    {
        //Utilisation systematique des privileges disponibles s'il y a des jetons disponibles sur le plateau
        while(joueur.getNbPrivileges() > 0)
        {
            if(!prendre_1_jetons())
                break;
            joueur.setNbPrivileges(joueur.getNbPrivileges() - 1);
        }

        //Prise de jetons de maniere optimisee selon la carte visee
        if(!prendre_3_jetons())
        {
            if(!prendre_2_jetons())
            {
                getPartie().remplir_plateau(joueur);
                if(!prendre_3_jetons())
                    if(!prendre_2_jetons())
                        prendre_1_jetons();
                        //Dans la situation improbable ou aucun jeton ne pourrait etre pris, l'IA passerait son tour ce qui est un comportement normalement interdit. Cela pourrait etre rendu encore davantage improbable en tentant de realiser un reservation si l'on ne peut prendre qu'un jeton.
            }
        }
    }

    //Verification du nombre de jetons possedes par le joueur actif
    while (total_stock(joueur.getGemmes()) > 10)
    {
        getPartie().remettre_jeton(joueur.getGemmes().random_pop());
    }

    //Verification de la possibilite d'obtenir une carte royale
    if (getPartie().get_cartes_royales().size() > 0 && (joueur.getNbCouronnes() >= 3 && joueur.getCartesRoyalesPossedees().size() == 0) && (joueur.getNbCouronnes() >= 6 && joueur.getCartesRoyalesPossedees().size() <= 1))
    {
        //Generation d'un nombre aleatoire
        std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count()); //Seed triviale base sur l'heure donne comme exemple par cplusplus.com
        std::uniform_int_distribution<size_t> distribution(0, getPartie().get_cartes_royales().size()-1);
        size_t num_carte = distribution(generator);

        CarteRoyale& carte_recup = partie.recupererCarteRoyale(num_carte);
        gestion_effets(carte_recup);
    }

    return true;
}

void IA1::gestion_effets(CarteJoaillerie& carte)
{
    Joueur& joueur = getPartie().get_joueur(num_joueur);

    for(unsigned int pos = 0 ; pos < carte.get_capacite().size() ; pos++)
    {
        switch (carte.get_capacite()[pos])
        {
        case rejouer:
            {
                getPartie().ajouter_rejouer();
            }
            break;

        case couleur:
            {
                Jeton type_bonus = joueur.getBonus().random_tirage();
                if(type_bonus == Bleu)
                {
                    StockGemmes nouveau_bonus = StockGemmes(carte.get_nbBonus());
                    carte.setTypeBonus(nouveau_bonus);
                    joueur.setBonus(joueur.getBonus()+nouveau_bonus);
                }
                else if(type_bonus == Vert)
                {
                    StockGemmes nouveau_bonus = StockGemmes(0, carte.get_nbBonus());
                    carte.setTypeBonus(nouveau_bonus);
                    joueur.setBonus(joueur.getBonus()+nouveau_bonus);
                }
                else if(type_bonus == Blanc)
                {
                    StockGemmes nouveau_bonus = StockGemmes(0, 0, carte.get_nbBonus());
                    carte.setTypeBonus(nouveau_bonus);
                    joueur.setBonus(joueur.getBonus()+nouveau_bonus);
                }
                else if(type_bonus == Rouge)
                {
                    StockGemmes nouveau_bonus = StockGemmes(0, 0, 0, carte.get_nbBonus());
                    carte.setTypeBonus(nouveau_bonus);
                    joueur.setBonus(joueur.getBonus()+nouveau_bonus);
                }
                else if(type_bonus == Noir)
                {
                    StockGemmes nouveau_bonus = StockGemmes(0, 0, 0, 0, carte.get_nbBonus());
                    carte.setTypeBonus(nouveau_bonus);
                    joueur.setBonus(joueur.getBonus()+nouveau_bonus);
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
                //Verification de la presence et prise si possible d'un jeton correspondant sur le plateau
                bool present = false;
                for (int i = 0 ; i < 5 ; i++)
                {
                    for (int j = 0 ; j < 5 ; j++)
                    {
                        if (partie.get_plateau()[j][i] == type_carte)
                        {
                            partie.retirer_jetons({j, i});
                            present = true;
                            break;
                        }
                    }
                    if (present == true)
                    {
                        break;
                    }
                }
            }
            break;

        case privilege:
            partie.prend_privilege(joueur);
            break;

        case voler:
            {
                Jeton gemme_volee = partie.get_joueur(partie.joueur_adverse()).getGemmes().random_tirage();
                while (gemme_volee == Or)
                {
                    gemme_volee = partie.get_joueur(partie.joueur_adverse()).getGemmes().random_tirage();
                }
                getPartie().capacite_voler(joueur, partie.get_joueur(partie.joueur_adverse()), gemme_volee);
            }
            break;
        }
    }
}

void IA1::gestion_effets(CarteRoyale& carte)
{
    Joueur& joueur = getPartie().get_joueur(num_joueur);

    switch (carte.getCapacite())
    {
    case rejouer:
        {
            getPartie().ajouter_rejouer();
        }
        break;

    case privilege:
        partie.prend_privilege(joueur);
        break;

    case voler:
        {
            Jeton gemme_volee = partie.get_joueur(partie.joueur_adverse()).getGemmes().random_tirage();
            while (gemme_volee == Or)
            {
                gemme_volee = partie.get_joueur(partie.joueur_adverse()).getGemmes().random_tirage();
            }
            getPartie().capacite_voler(joueur, partie.get_joueur(partie.joueur_adverse()), gemme_volee);
        }
        break;
    }
}
