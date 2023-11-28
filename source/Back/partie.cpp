#include "partie.h"

//M�thodes suivant le design pattern Singleton
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

Partie::~Partie(){//for (int i=0;i<67;i++){delete cartes[i];}
}


//Constucteur
Partie::Partie()
{
    //pour des questions de dépendances entre les objets statiques il faut initialiser cartes dès le constructeur
    std::vector<CarteJoaillerie> c(67,CarteJoaillerie());
    cartes=c;
    //Remplissage du sac. Il est effectu� ici plut�t que directement dans Sac dans le cas o� une extension ajouterait des jetons diff�rents
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
    remplir_plateau(joueur1);
    initCartes();
    Pyramide::initialiser(cartes);
}

void Partie::initCartes(){
    //lit depuis le fichier
    //version test :
    //for (int i = 0; i < 67; i++)
    //{
    //    cartes[i]=new CarteJoaillerie;
    //}
    std::cout<<"TOUTES LES CARTES\n";

    
    for (int i = 0; i<67 ; i++){
        if (i%3==0){
            cartes[i].setNiveau(1);
            cartes[i].setCout(StockGemmes());//coute 0
            cartes[i].setPointsPrestige(0);
            cartes[i].setNombreBonus(1);//donne 1 bonus
            cartes[i].setTypeBonus(StockGemmes(1));//bleu
            cartes[i].setEffet("none");

        }
        if (i%3==1){
            cartes[i].setNiveau(2);
            cartes[i].setCout(StockGemmes(2));//coute 2 bleu
            cartes[i].setPointsPrestige(1);//donne 1 pp
            cartes[i].setNombreBonus(2);//donne 2 bonus
            cartes[i].setTypeBonus(StockGemmes(0,1));//vert
            cartes[i].setEffet("none");
        }
        if (i%3==2){
            cartes[i].setNiveau(3);
            cartes[i].setCout(StockGemmes(2,2));//coute 2 bleu 2 vert
            cartes[i].setPointsPrestige(2);//donne 2 pp
            cartes[i].setNombreBonus(2);//donne 2 bonus
            cartes[i].setTypeBonus(StockGemmes(0,1));//vert
            cartes[i].setEffet("none");
        }
        std::cout<<cartes[i];
    }
    std::cout<<std::endl;

}

Joueur& Partie::get_joueur(unsigned int num_joueur)
{
    if(num_joueur == 1) {return joueur1;}
    if(num_joueur == 2) {return joueur2;}
    throw std::invalid_argument("La valeur du param�tre num_joueur dela m�thode get_joueur doit �tre 1 ou 2");
}

void Partie::prend_privilege(Joueur& joueur)
{
    if (privileges_disponibles > 0) {privileges_disponibles -= 1;}
    else
    {
        if ((&joueur == &joueur1) && (joueur2.getNbPrivileges() > 0)) {joueur2.setNbPrivileges(joueur2.getNbPrivileges() - 1);}
        else if (joueur1.getNbPrivileges() > 0){joueur1.setNbPrivileges(joueur1.getNbPrivileges() - 1);}
    }
    joueur.setNbPrivileges(joueur.getNbPrivileges()+1);
}

std::vector<std::array<unsigned int, 2>> Partie::remplir_plateau(Joueur& joueur)
{
    //V�rification que le plateau n'est pas vide
    if(plateau.get_nbCasesVides() == 0) {throw SplendorException("Le plateau est d�j� plein, impossible de le remplir");}

    //Initialisation de la liste des coordonn�es des cases modifi�es � renvoyer
    std::vector<std::array<unsigned int, 2>> coordonnees_modif;

    while ((plateau.get_nbCasesVides() > 0) && (total_stock(sac.get_gemmes())))
    {
        coordonnees_modif.push_back(remplir_case());
    }

    //Obtention d'un Privilege par l'adversaire
    if (&joueur == &joueur1) {prend_privilege(joueur2);}
    else {prend_privilege(joueur1);}

    return coordonnees_modif;
}

std::array<unsigned int, 2> Partie::remplir_case()
{
    return plateau.ajouterJeton(sac.retirer_jeton());
}

void Partie::retirer_jetons(Joueur& joueur, const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3)
{
    joueur.setGemmes(joueur.getGemmes() + plateau.actionRetirerJetons(coor_jeton1, coor_jeton2, coor_jeton3));
}

void Partie::retirer_jetons(Joueur& joueur, const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2)
{
    joueur.setGemmes(joueur.getGemmes() + plateau.actionRetirerJetons(coor_jeton1, coor_jeton2));
}

void Partie::retirer_jetons(Joueur& joueur, const std::array<unsigned int, 2>& coor_jeton)
{
    joueur.setGemmes(joueur.getGemmes() + plateau.actionRetirerJetons(coor_jeton));
}
