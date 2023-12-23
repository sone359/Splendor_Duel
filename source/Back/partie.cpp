#include "partie.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <random>
#include <ctime>
#include <map>

//Methodes suivant le design pattern Singleton
Partie* Partie::partie = nullptr;

Partie* Partie::get_partie()
{
    if (partie == nullptr)
    {
        partie = new Partie;
    }
    return partie;
}
Partie* Partie::get_partie(std::string s)
{
    if (partie == nullptr)
    {
        partie = new Partie(s);
    }
    return partie;
}

void Partie::delete_partie()
{
    delete partie;
    partie = nullptr;
}

Partie::~Partie(){
    delete pyramide;
}


//Constucteur
Partie::Partie()
{
    tour=0;
    plateau= Plateau::get_plateau();
    //Remplissage du sac. Il est effectue ici plutot que directement dans Sac dans le cas ou une extension ajouterait des jetons differents
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
    //Initialisation des cartes royales
    cartesRoyales.push_back(CarteRoyale(2, voler, "../data/Cartes_royales/CartesRoyales_voler.png"));
    cartesRoyales.push_back(CarteRoyale(2, privilege, "../data/Cartes_royales/CartesRoyales_privilege.png"));
    cartesRoyales.push_back(CarteRoyale(2, rejouer, "../data/Cartes_royales/CartesRoyales_rejouer.png"));
    cartesRoyales.push_back(CarteRoyale(3, sans, "../data/Cartes_royales/CartesRoyales_sans.png"));
    remplir_plateau(joueur1);
//
//
try {
        lire_fichier("../data/info_cartejoaillerie");
        //std::cout<<"../data/info_cartejoaillerie";
    } catch (const std::exception& e) {

    try{
            // Chemin de Ismail
  lire_fichier("D:\\LO21\\lo21_splendor-main\\data\\info_cartejoaillerie_1");
            //std::cout<<"D:\\LO21\\lo21_splendor-main\\source\\Front\\info_cartejoaillerie";
        } catch (const std::exception& e) {
            const char* cheminSubstitut2="";
            //chemin de Ahmed
                lire_fichier(cheminSubstitut2);
        }
    }


    pyramide = Pyramide::getInstance(cartes);
 //   pyramide->afficherPyramide();
}

void Partie::initCartes(){
    //version test :


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
    throw std::invalid_argument("La valeur du parametre num_joueur dela methode get_joueur doit etre 1 ou 2");
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
    if ((*plateau)[colonne][ligne] == Nul)
    {
        //Plus rapide et plus sûr mais n'a été ajouté qu'à partir de c++ 20 (qui ne semble pas supporté par le compilateur par défaut de Code Blocks)
        //throw SplendorException(std::format("La case ({}, {}) est vide, impossible d'y retirer un jeton", coor_jeton[0], coor_jeton[1]));
        throw SplendorException("La case (" + std::to_string(colonne) + ", "  + std::to_string(ligne) + ") est vide, impossible d'y retirer un jeton\n");
    }
    if ((*plateau)[colonne][ligne] == Or)
    {
        //Plus rapide et plus sûr mais n'a été ajouté qu'à partir de c++ 20 (qui ne semble pas supporté par le compilateur par défaut de Code Blocks)
        //throw SplendorException(std::format("Case {} invalide : L'or ne peut pas être retiré avec cette action", coor_jeton));
        throw SplendorException("Case (" + std::to_string(colonne) + ", "  + std::to_string(ligne) + ") invalide : L'or ne peut pas etre retire avec cette action\n");
    }

    joueur.setGemmes(joueur.getGemmes().ajouter_jeton(plateau->retirerJeton({colonne, ligne})));

    joueur.setNbPrivileges(joueur.getNbPrivileges() - 1);
}

std::vector<std::array<unsigned int, 2>> Partie::remplir_plateau(Joueur& joueur)
{
    //Verification que le plateau n'est pas vide
    if(plateau->get_nbCasesVides() == 0) {throw SplendorException("Le plateau est deja plein, impossible de le remplir");}

    //Initialisation de la liste des coordonnees des cases modifiees a renvoyer
    std::vector<std::array<unsigned int, 2>> coordonnees_modif;

        while ((plateau->get_nbCasesVides() > 0) && (total_stock(sac.get_gemmes())))
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
    return plateau->ajouterJeton(sac.retirer_jeton());
}

void Partie::retirer_jetons(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2, const std::array<unsigned int, 2>& coor_jeton3)
{
    Joueur& joueur = get_joueur(joueur_actif());
    StockGemmes stock = plateau->actionRetirerJetons(coor_jeton1, coor_jeton2, coor_jeton3);
    if(stock.get_Bleu() == 3 || stock.get_Vert() == 3 || stock.get_Blanc() == 3 || stock.get_Rouge() == 3 || stock.get_Noir() == 3 || stock.get_Perle() == 2)
    {
        prend_privilege(get_joueur(joueur_adverse()));
    }
    joueur.setGemmes(joueur.getGemmes() + stock);
}

void Partie::retirer_jetons(const std::array<unsigned int, 2>& coor_jeton1, const std::array<unsigned int, 2>& coor_jeton2)
{
    Joueur& joueur = get_joueur(joueur_actif());
    StockGemmes stock = plateau->actionRetirerJetons(coor_jeton1, coor_jeton2);
    if(stock.get_Perle() == 2)
    {
        prend_privilege(get_joueur(joueur_adverse()));
    }
    joueur.setGemmes(joueur.getGemmes() + stock);
}

void Partie::retirer_jetons(const std::array<unsigned int, 2>& coor_jeton)
{
    Joueur& joueur = get_joueur(joueur_actif());
    joueur.setGemmes(joueur.getGemmes() + plateau->actionRetirerJetons(coor_jeton));
}

void Partie::retirer_jetons_or(const std::array<unsigned int, 2>& coor_jeton)
{
    Joueur& joueur = get_joueur(joueur_actif());
    joueur.setGemmes(joueur.getGemmes() + plateau->actionRetirerJetonsOr(coor_jeton));
}

void Partie::remettre_jeton(Jeton jeton)
{
    Joueur& joueur = get_joueur(joueur_actif());
    joueur.setGemmes(joueur.getGemmes().retirer_jeton(jeton));
    sac.ajouter_jeton(jeton);
}

int Partie::fin_tour()
{
    //Verification des conditions de victoire pour le joueur actif
    int fin_partie = get_joueur(joueur_actif()).verifVictoire();

    //Passage au tour suivant
    if(fin_partie == 0 && !effet_rejouer)
        tour++;
    else
        effet_rejouer--;

    return fin_partie;
}

void Partie::capacite_voler(Joueur& joueur1, Joueur& joueur2, Jeton jeton)
{
    joueur2.setGemmes(joueur2.getGemmes().retirer_jeton(jeton));
    joueur1.setGemmes(joueur1.getGemmes().ajouter_jeton(jeton));
}

CarteJoaillerie& Partie::acheter_carte(Joueur& joueur, int niv, int colonne){
    StockGemmesOr avant_achat = joueur.getGemmes();//retiens le nombre de gemmes avant l'achat
    if (joueur.peutAcheter(pyramide->recupererCarteJoaillerie(niv,colonne))){// std::cout<<"achetee\n";
        if (colonne == 0){
            throw SplendorException("Impossible d'acheter une carte de la pioche.\n");
        }
        else{
            //Vérification que le joueur n'achète pas une carte avec un bonus Couleur (<=> type de bonus nul) alors qu'il n'a pas encore d'autre cartes
            std::vector<Effet> effets = pyramide->recupererCarteJoaillerie(niv,colonne).get_capacite();
            for (size_t i = 0 ; i < effets.size() ; i++)
            {
                if(effets[i] == couleur && joueur.getCartesJoailleriesPossedees().size() == 0)
                {
                    throw SplendorException("Vous ne pouvez pas acheter une carte avec la capacite Couleur sans avoir de carte a laquelle l'associer");
                }
            }
            joueur.addCartesJoailleriesPossedees(pyramide->acheterCarteJoaillerie(niv,colonne));
            sac.ajouter_stock(joueur.getGemmes()/avant_achat);
            return joueur.getCartesJoailleriesPossedees().back();
        }
    }
    else throw SplendorException("Cette carte est trop chere, recuperez plus de jetons.\n");


    //}catch (const SplendorException& e) {
        //oh mon dieu ca marche quelle emotion
    //    std::cerr << "Erreur : " << e.what() << std::endl;
    //}
}

CarteJoaillerie& Partie::acheterCarteReservee(unsigned int num){
    Joueur& joueur=get_joueur(joueur_actif());
    StockGemmesOr avant_achat = joueur.getGemmes();//retiens le nombre de gemmes avant l'achat
    CarteJoaillerie & res=joueur.acheterCarteReservee(num);
    sac.ajouter_stock(joueur.getGemmes()/avant_achat);
    return res;
}

void Partie::reserver_carte(Joueur& joueur, int niv, int colonne){
    if(joueur.getCartesJoailleriesReservees().size()==3) throw SplendorException("Impossible de reserver plus de 3 cartes.\n");
    CarteJoaillerie piochee = pyramide->reserverCarteJoaillerie(niv,colonne);
    joueur.addCartesJoailleriesReservees(piochee);
}

CarteRoyale& Partie::recupererCarteRoyale(size_t numero)
{
    if (cartesRoyales.size() <= numero-1) {throw SplendorException("Le numero entre ne correspond pas ou plus a aucune carte royale");}

    CarteRoyale& carte_recup = cartesRoyales[numero-1];
    Joueur& joueur = get_joueur(joueur_actif());

    cartesRoyales.erase(cartesRoyales.begin() + numero-1); //Méthode peu performante. Pourrait être remplacée par un échange entre le dernier élément et l'élément retiré mais la faible taille du vecteur fait privilégier la cohérence à l'affichage et donc la préservation de l'ordre.

    joueur.addCartesRoyalesPossedees(carte_recup);
    joueur.addPointsPrestiges(carte_recup.getPointsPrestige());

    return carte_recup;
}

bool Partie::get_statut_joueur_actif() const
{
    if(joueur_actif() == 1)
        return statut_joueur1;
    return statut_joueur2;
}

void Partie::set_statut_joueur(unsigned int joueur, bool statut)
{
    if(joueur == 1)
        statut_joueur1 = statut;
    else
        statut_joueur2 = statut;
}

int Partie::lire_fichier(const char* fichier){
    // ouverture du fichier ou les cartes sont stockees
    std::ifstream inputFile(fichier);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Error opening the file: " + std::string(strerror(errno)));
        return 1;
    }
        std::string line;
        //compte cartes
        int cartes_lues=0;
        // saute les 2 1eres lignes
        std::getline(inputFile, line);
        std::getline(inputFile, line);
        //pour ignorer la premiere ligne
        bool isFirstLine = true;
        //tant qu'on est pas a la fin du fichier
        while (!inputFile.eof()) {
            if (cartes_lues==67) break;
            std::getline(inputFile, line);
            cartes.push_back(CarteJoaillerie(line));
            cartes_lues++;
        }
        // fermeture du fichier
        inputFile.close();

        //melanger les cartes:
        std::shuffle(cartes.begin(),cartes.end(),std::default_random_engine(std::random_device()()));

        ////verif
        //for(CarteJoaillerie  carte : cartes){
        //    std::cout<<carte<<std::endl;
        //    std::cout<<carte.getChemin()<<'\n';
        //}
        return 0;
    }

std::string Partie::getTime()const{
        std::time_t now = std::time(0);
        std::tm* dateheure = std::localtime(&now);
        char buffer[50];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", dateheure);

        return buffer;
    }

int Partie::sauvegarder(const std::string fichier)const{
    std::cout<<"sauvegarde en cours...\n";
    int cartes_en_jeu=0;
    std::ofstream fsauvegarde(fichier);

    if(!fsauvegarde.is_open()) throw ("Erreur a l'ouverture du fichier de sauvegarde.\n");

    //date
    fsauvegarde<<getTime()<<"\n";


    //nom
    fsauvegarde<<"sauvegarde automatique"<<"\n";
    //cartes dans les pioches
    for (int i =1;i<4;i++){
        while (!pyramide->getPioche(i).empty())
        {
            fsauvegarde<<pyramide->getPioche(i).top().sauvegarder();
            pyramide->getPioche(i).pop();
        }
    }

    fsauvegarde<<"\n";
    //cartes de la pyramide
    for(int i =1; i<6 ;i++){
            fsauvegarde<<pyramide->recupererCarteJoaillerie(1,i).sauvegarder();
        }
        for(int i =1; i<5 ;i++){
            fsauvegarde<<pyramide->recupererCarteJoaillerie(2,i).sauvegarder();
        }
        for(int i =1; i<4 ;i++){
            fsauvegarde<<pyramide->recupererCarteJoaillerie(3,i).sauvegarder();
        }

    //joueurs
    fsauvegarde<<joueur1.sauvegarder();
    fsauvegarde<<joueur2.sauvegarder();
    fsauvegarde<<"\n";

    //jetons du sac
    fsauvegarde<<sac.get_gemmes().sauvegarder();
    //joueur actif
    fsauvegarde<<tour<<'\n';
    //jetons du plateau
    fsauvegarde<<plateau->sauvegarder();

    fsauvegarde.close();
    std::cout<<"saved!\n";
    return 0;
}

Partie::Partie(const std::string fichier){
    // ouverture du fichier de sauvegarde
    std::ifstream inputFile(fichier);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Error opening the file: " + std::string(strerror(errno)));
        return;
    }
        std::string line;
        //compte cartes
        int cartes_lues=0;
        int nbline=0;
        //var temp
        int tempniveau, temppointsPrestige, tempnombreBonus, tempcouronnes, step;
        Effet tempeffet;
        std::vector<Effet> tempcapacite;
        StockGemmes tempcout;
        StockGemmes temptype;
        std::string chemin;
        // saute les 2 1eres lignes
        std::getline(inputFile, line);
        std::getline(inputFile, line);

        while(!inputFile.eof()){//pioches
            std::getline(inputFile, line);
            if(line=="\0"||line=="\n") break;
            cartes.push_back(CarteJoaillerie(line));
            cartes_lues++;
        }
        //std::getline(inputFile, line);
        while(!inputFile.eof()){//Pyramide
            std::getline(inputFile, line);
            if(line=="{\0") {
                break;
            }
            cartes.push_back(CarteJoaillerie(line));
            cartes_lues++;
        }
        std::vector<CarteJoaillerie> cartesPossedeestemp;
        std::deque<CarteJoaillerie> cartesReserveestemp;

        //std::cout<<"------LECTURE JOUEUR1-------\n";
        while(!inputFile.eof()){//Joueur1
            std::getline(inputFile, line);
            //std::cout<<"cartes possedees :" <<line<<'\n';
            if(line=="\0") {
                break;
            }
            cartesPossedeestemp.push_back(CarteJoaillerie(line));
            cartes_lues++;
        }
        std::getline(inputFile,line);
        std::istringstream iss(line);
        std::string token,token1;

        if (std::getline(iss, token, ';')) {
            //std::cout<<"jetons :" <<token<<'\n';

            joueur1.setGemmes(StockGemmesOr(token));
        }
        while(!inputFile.eof()){
            std::getline(inputFile, line);
            //std::cout<<"cartes reservees :" <<line<<'\n';
            if(line=="\0") {
                break;
            }
            cartesReserveestemp.push_back(CarteJoaillerie(line));
            cartes_lues++;
        }
        joueur1.setCartesJoailleriesReservees(cartesReserveestemp);
        joueur1.setCartesJoailleriesPossedees(cartesPossedeestemp);
        std::getline(inputFile,line);
        //std::cout<<"where1 :" <<line<<'\n';
        iss.clear();
        iss.str(line);
        if (std::getline(iss, token, ';')) {
            //std::cout<<"couronnes :" <<token<<'\n';
            joueur1.setNbCouronnes(stoi(token));
            //std::cout<<"  "<<token<<"\n";
        }
        if (std::getline(iss, token, ';')) {
            //std::cout<<"privileges :" <<token<<'\n';
            joueur1.setNbPrivileges(stoi(token));
            //std::cout<<"  "<<token<<"\n";
        }
        if (std::getline(iss, token, ';')) {
            joueur1.setPointsPrestigeCouleur(StockGemmes(token));
        }

        std::getline(inputFile, line);
        cartesPossedeestemp.clear();
        cartesReserveestemp.clear();

        //std::cout<<"------LECTURE JOUEUR2-------\n";

        while(!inputFile.eof()){//Joueur2
            std::getline(inputFile, line);
            //std::cout<<"cartes possedees :" <<line<<'\n';
            if(line=="\0") {
                break;
            }
            cartesPossedeestemp.push_back(CarteJoaillerie(line));
            cartes_lues++;
        }
        std::getline(inputFile,line);
        iss.clear();
        iss.str(line);
        if (std::getline(iss, token, ';')) {
            //std::cout<<"jetons :" <<token<<'\n';
            joueur2.setGemmes(StockGemmesOr(token));
        }
        while(!inputFile.eof()){
            std::getline(inputFile, line);
            //std::cout<<"cartes reservees :" <<line<<'\n';
            if(line=="\0") {
                break;
            }
            cartesReserveestemp.push_back(CarteJoaillerie(line));
            cartes_lues++;
        }
        joueur2.setCartesJoailleriesReservees(cartesReserveestemp);
        joueur2.setCartesJoailleriesPossedees(cartesPossedeestemp);
        std::getline(inputFile,line);
        //std::cout<<"where1 :" <<line<<'\n';
        iss.clear();
        iss.str(line);
        if (std::getline(iss, token, ';')) {
            //std::cout<<"couronnes :" <<token<<'\n';
            joueur2.setNbCouronnes(stoi(token));
            //std::cout<<"  "<<token<<"\n";
        }
        if (std::getline(iss, token, ';')) {
            //std::cout<<"privileges :" <<token<<'\n';
            joueur2.setNbPrivileges(stoi(token));
            //std::cout<<"  "<<token<<"\n";
        }
        if (std::getline(iss, token, ';')) {

            joueur2.setPointsPrestigeCouleur(StockGemmes(token));
        }
        std::getline(inputFile,line);
        std::getline(inputFile,line);
        //std::cout<<"line3 :"<<line<<"\n";
        iss.clear();
        iss.str(line);
        if (std::getline(iss, token, ';')) {

            sac.ajouter_stock(StockGemmesOr(token));
            //std::cout<<token<<"toksac\n";

        }
        if (std::getline(iss, token, ';')) {//tour
            tour=stoi(token);
            //std::cout<<token<<"toktour\n";
        }
        std::getline(inputFile,line);
        plateau=Plateau::get_plateau(line);
        // fermeture du fichier
        inputFile.close();

        joueur1.initBonus();
        joueur2.initBonus();
        joueur1.initPrestige();
        joueur2.initPrestige();

        //for(CarteJoaillerie carte : cartes)
        //    std::cout<<carte;
        //std::cout<<"\n\n";

        pyramide = Pyramide::getInstance(cartes);
        //pyramide->afficherPyramide();

        ////verif
        //for(CarteJoaillerie  carte : cartes){
        //    std::cout<<carte<<std::endl;
        //    std::cout<<carte.getChemin()<<'\n';
        //}
}

void Partie::inscrireGagnant(unsigned int joueur){
    std::map<std::string,unsigned int> scores=recupererGagnants();
    for(std::pair<std::string,unsigned int> score : scores){//si il y est deja
        if (score.first==get_joueur(joueur).getNom()) {
            score.second+=1;
            std::ofstream file("../data/gagnants");
            if(!file.is_open()) throw ("Erreur a l'ouverture du fichier de sauvegarde.\n");
            for(std::pair<std::string,unsigned int> score : scores){//sinon
                file<<score.first<<'\n';
                file<<score.second<<'\n';
            }
            file.close();
            return;
        }
        std::ofstream file;
        file.open("../data/gagnants", std::ios::app);
        file<<get_joueur(joueur).getNom()<<'\n';
        file<<1<<'\n';
        file.close();
    }
    
}

std::map<std::string,unsigned int> Partie::recupererGagnants(){
    std::map<std::string,unsigned int> scores;
    std::ifstream inputFile("../data/gagnants");
    if (!inputFile.is_open()) {
        throw std::runtime_error("Error opening the file: " + std::string(strerror(errno)));
        return;
    }
    std::string line1;
    std::string line2;
        while(std::getline(inputFile, line1) && std::getline(inputFile, line2)){
            scores[line1]=stoi(line2);
        }
    inputFile.close();
    return scores;
}