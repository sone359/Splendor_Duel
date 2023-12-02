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
    //Remplissage du sac. Il est effectue ici plutot que directement dans Sac dans le cas o� une extension ajouterait des jetons diff�rents
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
    pyramide = Pyramide::getInstance();
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
    if(joueur.getNbPrivileges() < 3)
    {
        if (privileges_disponibles > 0) {privileges_disponibles -= 1;}
        else
        {
            if (&joueur == &joueur1) {joueur2.setNbPrivileges(joueur2.getNbPrivileges() - 1);}
            else {joueur1.setNbPrivileges(joueur1.getNbPrivileges() - 1);}
        }
        joueur.setNbPrivileges(joueur.getNbPrivileges()+1);
    }
}

void Partie::utilise_privilege(Joueur& joueur, unsigned int colonne, unsigned int ligne)
{
    //Vérification de la validité des arguments passés en paramètre
    if(joueur.getNbPrivileges() == 0)
    {
        throw SplendorException("Ce joueur n'a pas de privilege a utiliser");
    }
    if ((colonne > 25) || (ligne > 25))
    {
        //Plus rapide et plus sûr mais n'a été ajouté qu'à partir de c++ 20 (qui ne semble pas supporté par le compilateur par défaut de Code Blocks)
        //throw SplendorException(std::format("La case ({}, {}) n'existe pas, impossible d'y retirer un jeton", coor_jeton[0], coor_jeton[1]));
        throw SplendorException("La case (" + std::to_string(colonne) + ", "  + std::to_string(ligne) + ") n'existe pas, impossible d'y retirer un jeton\n");
    }
    if (plateau[colonne][ligne] == Nul)
    {
        //Plus rapide et plus sûr mais n'a été ajouté qu'à partir de c++ 20 (qui ne semble pas supporté par le compilateur par défaut de Code Blocks)
        //throw SplendorException(std::format("La case ({}, {}) est vide, impossible d'y retirer un jeton", coor_jeton[0], coor_jeton[1]));
        throw SplendorException("La case (" + std::to_string(colonne) + ", "  + std::to_string(ligne) + ") est vide, impossible d'y retirer un jeton\n");
    }
    if (plateau[colonne][ligne] == Or)
    {
        //Plus rapide et plus sûr mais n'a été ajouté qu'à partir de c++ 20 (qui ne semble pas supporté par le compilateur par défaut de Code Blocks)
        //throw SplendorException(std::format("Case {} invalide : L'or ne peut pas être retiré avec cette action", coor_jeton));
        throw SplendorException("Case (" + std::to_string(colonne) + ", "  + std::to_string(ligne) + ") invalide : L'or ne peut pas etre retire avec cette action\n");
    }

    joueur.setGemmes(joueur.getGemmes().ajouter_jeton(plateau.retirerJeton({colonne, ligne})));

    joueur.setNbPrivileges(joueur.getNbPrivileges() - 1);
}

std::vector<std::array<unsigned int, 2>> Partie::remplir_plateau(Joueur& joueur)
{
    //Verification que le plateau n'est pas vide
    if(plateau.get_nbCasesVides() == 0) {throw SplendorException("Le plateau est deja plein, impossible de le remplir");}

    //Initialisation de la liste des coordonnees des cases modifiees a renvoyer
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

void Partie::retirer_jetons(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3)
{
    Joueur& joueur = get_joueur(joueur_actif());
    StockGemmes stock = plateau.actionRetirerJetons(coor_jeton1, coor_jeton2, coor_jeton3);
    if(stock.get_Bleu() == 3 || stock.get_Vert() == 3 || stock.get_Blanc() == 3 || stock.get_Rouge() == 3 || stock.get_Noir() == 3 || stock.get_Perle() == 2)
    {
        prend_privilege(get_joueur(joueur_adverse()));
    }
    joueur.setGemmes(joueur.getGemmes() + stock);
}

void Partie::retirer_jetons(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2)
{
    Joueur& joueur = get_joueur(joueur_actif());
    StockGemmes stock = plateau.actionRetirerJetons(coor_jeton1, coor_jeton2);
    if(stock.get_Perle() == 2)
    {
        prend_privilege(get_joueur(joueur_adverse()));
    }
    joueur.setGemmes(joueur.getGemmes() + stock);
}

void Partie::retirer_jetons(const std::array<unsigned int, 2>& coor_jeton)
{
    Joueur& joueur = get_joueur(joueur_actif());
    joueur.setGemmes(joueur.getGemmes() + plateau.actionRetirerJetons(coor_jeton));
}

void Partie::remettre_jeton(Jeton jeton)
{
    Joueur& joueur = get_joueur(joueur_actif());
    joueur.setGemmes(joueur.getGemmes().retirer_jeton(jeton));
    sac.ajouter_jeton(jeton);
}

void Partie::fin_tour()
{
    tour++;
}
