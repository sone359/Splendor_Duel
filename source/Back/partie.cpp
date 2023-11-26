#include "partie.h"

//Méthodes suivant le design pattern Singleton
Partie* Partie::partie = nullptr;

Partie& Partie::get_partie()
{
    if (partie == nullptr)
    {
        partie = new Partie;
    }
    return *partie;
}

void Partie::delete_partie()
{
    delete partie;
    partie = nullptr;
}

Partie::~Partie(){for (int i=0;i<67;i++){delete cartes[i];}}


//Constucteur
Partie::Partie()
{
    //Remplissage du sac. Il est effectué ici plutôt que directement dans Sac dans le cas où une extension ajouterait des jetons différents
    for(unsigned int i = 0 ; i < 4 ; i++){
        sac.ajouter_jeton(Bleu);
        sac.ajouter_jeton(Vert);
        sac.ajouter_jeton(Blanc);
        sac.ajouter_jeton(Rouge);
        sac.ajouter_jeton(Noir);
    }
    sac.ajouter_jeton(Perle);
    sac.ajouter_jeton(Perle);
    for(unsigned int i = 0 ; i < 3 ; i++){
        sac.ajouter_jeton(Or);
    }
    remplir_plateau();

    //for (int i=0;i<67;i++){cartes[i]=new CarteJoaillerie(i,i);};
    initPyramide();
}

std::vector<std::array<unsigned int, 2>> Partie::remplir_plateau()
{
    //Vérification que le plateau n'est pas vide
    if(plateau.get_nbCasesVides() == 0) {throw SplendorException("Le plateau est déjà plein, impossible de le remplir");}

    //Initialisation de la liste des coordonnées des cases modifiées à renvoyer
    std::vector<std::array<unsigned int, 2>> coordonnees_modif;

    while (plateau.get_nbCasesVides() > 0)
    {
        coordonnees_modif.push_back(remplir_case());
    }

    return coordonnees_modif;
}

std::array<unsigned int, 2> Partie::remplir_case()
{
    return plateau.ajouterJeton(sac.retirer_jeton());
}

Joueur Partie::get_joueur(unsigned int num_joueur) const
{
    if(num_joueur == 1) {return joueur1;}
    if(num_joueur == 2) {return joueur2;}
    throw std::invalid_argument("La valeur du paramètre num_joueur dela méthode get_joueur doit être 1 ou 2");
}
