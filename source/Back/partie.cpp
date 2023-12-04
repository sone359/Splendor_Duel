#include "partie.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

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
    lire_fichier("../data/info_cartejoaillerie");
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
    std::vector<Effet> e1,e2,e3;
    Effet e= Effet(5);
    e1.push_back(e);
    e2.push_back(e);
    e3.push_back(e);
    e = Effet(2);
    e3.push_back(e);


    
    for (int i = 0; i<67 ; i++){
        if (i%3==0){
            cartes[i].setNiveau(1);
            cartes[i].setCout(StockGemmes());//coute 0
            cartes[i].setPointsPrestige(0);
            cartes[i].setNombreBonus(1);//donne 1 bonus
            cartes[i].setTypeBonus(StockGemmes(1));//bleu
            cartes[i].setCapacite(e1);

        }
        if (i%3==1){
            cartes[i].setNiveau(2);
            cartes[i].setCout(StockGemmes(2));//coute 2 bleu
            cartes[i].setPointsPrestige(1);//donne 1 pp
            cartes[i].setNombreBonus(2);//donne 2 bonus
            cartes[i].setTypeBonus(StockGemmes(0,1));//vert
            cartes[i].setCapacite(e2);
        }
        if (i%3==2){
            cartes[i].setNiveau(3);
            cartes[i].setCout(StockGemmes(2,2));//coute 2 bleu 2 vert
            cartes[i].setPointsPrestige(2);//donne 2 pp
            cartes[i].setNombreBonus(2);//donne 2 bonus
            cartes[i].setTypeBonus(StockGemmes(0,1));//vert
            cartes[i].setCapacite(e3);
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

void Partie::acheter_carte(int numjoueur, int niv, int colonne){
    try{
        if (colonne == 0){
            throw SplendorException("Impossible d'acheter une carte de la pioche.\n"); 
            return;
        }
        CarteJoaillerie piochee = pyramide->acheterCarteJoaillerie(niv,colonne);
        switch (numjoueur)
        {
        case 1:
            joueur1.addCartesJoailleriesPossedees(piochee);
            break;
        case 2:
            joueur2.addCartesJoailleriesPossedees(piochee);
        default:
            throw SplendorException("Erreur numero joueur actif");
        }
    }catch (const SplendorException& e) {
        //oh mon dieu ca marche quelle emotion
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}

void Partie::reserver_carte(int numjoueur, int niv, int colonne){
    CarteJoaillerie piochee = pyramide->reserverCarteJoaillerie(niv,colonne);
    switch (numjoueur)
    {
    case 1:
        joueur1.addCartesJoailleriesReservees(piochee);
        break;
    case 2:
        joueur2.addCartesJoailleriesReservees(piochee);
    default:
        throw SplendorException("Erreur numero joueur actif");
    }
}

int Partie::lire_fichier(const char* fichier){
    // Rcupration du fichier ou les cartes ton stock
    std::ifstream inputFile(fichier);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }
        std::string line;
        //compte cartes
        int cartes_lues=0;
        //var temp
        int tempniveau, temppointsPrestige, tempnombreBonus, tempcouronnes, step;
        Effet tempeffet;
        std::vector<Effet> tempcapacite;
        StockGemmes tempcout;
        StockGemmes temptype;
        // saute les 2 1eres lignes
        std::getline(inputFile, line);
        std::getline(inputFile, line);
        //pour ignorer la premiere ligne
        bool isFirstLine = true;
        //tant qu'on est pas a la fin du fichier
        while (!inputFile.eof()) {
            if (cartes_lues==67) break;
            std::getline(inputFile, line);
            std::cout<<"--------------CARTE "<<cartes_lues<<"---------------\n";
            std::cout<<line<<std::endl;

            std::istringstream iss(line);
            std::string token,token1;

            if (std::getline(iss, token, ';')) {
                tempniveau=stoi(token);
                std::cout<<tempniveau<<"  ";
            }
            if (std::getline(iss, token, ';')) {
                temppointsPrestige=stoi(token);
                std::cout<<temppointsPrestige<<"  ";
            }
            if (std::getline(iss, token, ';')) {
                tempnombreBonus=stoi(token);
                std::cout<<tempnombreBonus<<"\n";
            }
            if (std::getline(iss, token, ';')) {
                if(token=="blanc") temptype.set_Blanc(1);
                if(token=="bleu") temptype.set_Bleu(1);
                if(token=="vert") temptype.set_Vert(1);
                if(token=="rouge") temptype.set_Rouge(1);
                if(token=="noir") {temptype.set_Noir(1);}
                if(token=="perle") temptype.set_Perle(1);
                std::cout<<"       type :"<<temptype<<std::endl;
            }
            if (std::getline(iss, token, ';')) {
                tempcouronnes=stoi(token);
                std::cout<<tempcouronnes<<"\n";
            }
            if (std::getline(iss, token, ';')) {
                std::istringstream iss1(token);
                std::cout<<"\n->"<<token<<"<-\n";
                if (std::getline(iss1, token1, ',')) {
                    tempcout.set_Blanc(stoi(token1));
                    //std::cout<<"\n->"<<token1<<"<-\n";
                }
                if (std::getline(iss1, token1, ',')) {
                    tempcout.set_Bleu(stoi(token1));
                }
                if (std::getline(iss1, token1, ',')) {
                    tempcout.set_Vert(stoi(token1));
                }
                if (std::getline(iss1, token1, ',')) {
                    tempcout.set_Rouge(stoi(token1));
                }
                if (std::getline(iss1, token1, ',')) {
                    tempcout.set_Noir(stoi(token1));
                }
                if (std::getline(iss1, token1, ',')) {
                    tempcout.set_Perle(stoi(token1));
                }
                std::cout<<"       cout :"<<tempcout<<std::endl;
            }
            if (std::getline(iss, token, '\n')) {
            std::cout<<"    capacite :";
            std::istringstream iss1(token);
    
                if (std::getline(iss1, token1, ',')) {
                    if(token1=="rejouer") tempeffet=Effet(0);
                    if(token1=="voler") tempeffet=Effet(4);
                    if(token1=="privilege") tempeffet=Effet(1);;
                    if(token1=="couleur") tempeffet=Effet(2);
                    if(token1=="gemme") tempeffet=Effet(3);
                    if(token1=="none") tempeffet=Effet(5);
                    std::cout<<tempeffet<<"\n";
                }
                    tempcapacite.push_back(tempeffet);
                if (std::getline(iss1, token1, ',')) {
                    if(token1=="rejouer") tempeffet=Effet(0);
                    if(token1=="voler") tempeffet=Effet(4);
                    if(token1=="privilege") tempeffet=Effet(1);;
                    if(token1=="couleur") tempeffet=Effet(2);
                    if(token1=="gemme") tempeffet=Effet(3);
                    if(token1=="none") tempeffet=Effet(5);
                    std::cout<<tempeffet<<"\n";
                    tempcapacite.push_back(tempeffet);
                }
            }
            //ajouter à cartes
            cartes[cartes_lues]=CarteJoaillerie(tempniveau,temppointsPrestige,tempnombreBonus,temptype,tempcouronnes,tempcout,tempcapacite);
            //reset prochain tour
            tempcapacite.clear();
            tempcout=0;
            temptype=0;
            cartes_lues++;
        }
        // fermeture du fichier
        inputFile.close();
        //verif
        for(CarteJoaillerie  carte : cartes){        
            std::cout<<carte<<std::endl;
        }
        return 0;
    }
//}