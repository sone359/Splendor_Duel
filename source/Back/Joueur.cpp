#include "Joueur.h"

// Constructeurs
Joueur::Joueur() :  nbPrivileges(0), nbCouronnes(0){}

Joueur::Joueur(int nbPrivileges, int nbCouronnes, StockGemmesOr & tgemmes, StockGemmes & tbonus)
    : nbPrivileges(nbPrivileges), nbCouronnes(nbCouronnes), gemmes(tgemmes), bonus(tbonus) {}



// Getters
int Joueur::getNbPrivileges() const
{
    return nbPrivileges;
}
std::vector<CarteJoaillerie> Joueur::getCartesJoailleriesPossedees() const
{
    return cartesJoailleriesPossedees;
}
std::deque<CarteJoaillerie> Joueur::getCartesJoailleriesReservees() const
{
    return cartesJoailleriesReservees;
}
std::vector<CarteRoyale> Joueur::getCartesRoyalesPossedees() const
{
    return cartesRoyalesPossedees;
}
int Joueur::getNbCouronnes() const
{
    return nbCouronnes;
}
StockGemmesOr Joueur::getGemmes() const
{
    return gemmes;
}

StockGemmes Joueur::getBonus() const
{
    return bonus;
}

StockGemmesOr Joueur::getRessources() const {
    return gemmes+bonus;
}

unsigned int Joueur::getNbPointsPrestige() const
{
    return nbPointsPrestige;
}
unsigned int Joueur::getNbPointsPrestigeBleu() const
{
    return nbPointsPrestigeCouleurs[0];
}
unsigned int Joueur::getNbPointsPrestigeVert() const
{
    return nbPointsPrestigeCouleurs[1];
}
unsigned int Joueur::getNbPointsPrestigeBlanc() const
{
    return nbPointsPrestigeCouleurs[2];
}
unsigned int Joueur::getNbPointsPrestigeRouge() const
{
    return nbPointsPrestigeCouleurs[3];
}
unsigned int Joueur::getNbPointsPrestigeNoir() const
{
    return nbPointsPrestigeCouleurs[4];
}


// Setters
void Joueur::setNbPrivileges(int nbPrivileges)
{
    this->nbPrivileges = nbPrivileges;
}

void Joueur::setCartesJoailleriesPossedees(std::vector<CarteJoaillerie> cartes){
    cartesJoailleriesPossedees=cartes;
}

void Joueur::addCartesJoailleriesPossedees(CarteJoaillerie carte)
{
    //gemmes.depense(carte.get_cout(),bonus);
    cartesJoailleriesPossedees.push_back(carte);
    addBonus(carte);
}

void Joueur::addBonus(const CarteJoaillerie& carte){
    bonus+=carte.get_typeBonus()*carte.get_nbBonus();
}

void Joueur::setCartesJoailleriesReservees(std::deque<CarteJoaillerie> cartes)
{
    cartesJoailleriesReservees=cartes;
}

void Joueur::addCartesJoailleriesReservees(CarteJoaillerie& carte)
{
    if (cartesJoailleriesReservees.size()>3) throw SplendorException("Impossible de reserver plus de 3 cartes.");
    else cartesJoailleriesReservees.push_back(carte);
}


void Joueur::setCartesRoyalesPossedees(std::vector<CarteRoyale> cartes)
{
    cartesRoyalesPossedees=cartes;
}

void Joueur::addCartesRoyalesPossedees(CarteRoyale& carte)
{
    cartesRoyalesPossedees.push_back(carte);
}

void Joueur::setNbCouronnes(int nc)
{
    nbCouronnes = nc;
}

void Joueur::setGemmes(const StockGemmesOr& g)
{
    gemmes = g;
}


void Joueur::setBonus(const StockGemmes& b)
{
    bonus = b;
}

int Joueur::verifVictoire()
//Renvoie 0 si le joueur n'a pas atteint les conditions de victoire, 1 s'il a plus de 20 points de prestige, 2 s'il a plus de 10 couronnes ou 3 s'il a plus de 10 points de prestige dans une des couleurs de gemmes
{
    if(nbPointsPrestige >= 20)
    {
        return 1;
    }
    if(nbCouronnes >= 10)
    {
        return 2;
    }
    if(getNbPointsPrestigeBleu() >= 10 || getNbPointsPrestigeVert() >= 10 || getNbPointsPrestigeBlanc() >= 10 || getNbPointsPrestigeRouge() >= 10 || getNbPointsPrestigeNoir() >= 10)
    {
        return 3;
    }
    return 0;
}

CarteJoaillerie& Joueur::acheterCarteReservee(unsigned int num){
    //std::cout<<"\nCARTE RESA SIZE :"<<cartesJoailleriesReservees.size();
    if (peutAcheter(cartesJoailleriesReservees[num-1])){
        if (num > 0 && num <= cartesJoailleriesReservees.size()) {
            addCartesJoailleriesPossedees(cartesJoailleriesReservees[num-1]);
            auto it = cartesJoailleriesReservees.begin() + num;
            cartesJoailleriesReservees.erase(it);
            return cartesJoailleriesPossedees.back();
            
        } else {
            throw SplendorException("Numero invalide pour les cartes reservees.");
        }        
    
    }
    else throw SplendorException("Cette carte est trop chere, recuperez plus de jetons.\n");
}

bool Joueur::peutAcheter(const CarteJoaillerie& carte){
        StockGemmes depense = carte.get_cout();
        depense-=bonus;
        StockGemmes temp = gemmes + bonus;
        if (temp<carte.get_cout()){
            temp=temp/carte.get_cout();
            if(temp.total_gemmes()>gemmes.get_Or()){
                //std::cout<<"avec or il reste encore "<<temp.total_gemmes()-gemmes.get_Or()<<"\n";
                return false;
            }
            else{
                //std::cout<<"acheté avec jetons or.\n";
                gemmes=gemmes-depense;

                return true;
            }
        }
        else{
            //std::cout<<"ca marche :"<<temp-carte.get_cout()<<"\n";
            gemmes=gemmes-depense;
            return true;

        }
        
        return false;
    }

