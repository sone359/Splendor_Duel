#include "BoutonManager.h"
#include <QRadioButton>
#include <QMessageBox>
#include "PartieWidget.h"
#include <iostream>

BoutonManager::BoutonManager(QWidget *parent)
    : parentWidget(parent),
      buttonsLayout(new QGridLayout(parent)),
      menu(new QMenu(parent))

{
    createButtons();

}

BoutonManager::~BoutonManager() {
    delete buttonsLayout;
    delete menu;
}

void BoutonManager::createButtons() {

    //volerButton->setDisabled(true);

    // Définir le style pour les boutons
    QString buttonStyle = "QPushButton {"
                          "    display: inline-block;"
                          "    background-color: green;"
                          "    border-radius: 10px;"
                          "    border: 4px double #cccccc;"
                          "    color: #eeeeee;"
                          "    text-align: center;"
                          "    font-size: 12px;"
                          "    padding: 10px;"
                          "    width: 10px;"
                          "    transition: all 0.5s;"
                          "    cursor: pointer;"
                          "    margin: 5px;"
                          "}"
                          "QPushButton:hover {"
                          "    background-color: gray;"
                          "}"
                          "QPushButton:hover span {"
                          "    padding-right: 25px;"
                          "}"
                          "QPushButton:hover span:after {"
                          "    opacity: 1;"
                          "    right: 0;"
                          "}";

    acheterCarteButton->setStyleSheet(buttonStyle);
    reserverCarteButton->setStyleSheet(buttonStyle);
    utiliserPrivilegeButton->setStyleSheet(buttonStyle);
    annulerJetonsButton->setStyleSheet(buttonStyle);
    prendreJetonsButton->setStyleSheet(buttonStyle);
    remplirPlateauButton->setStyleSheet(buttonStyle);

    buttonsLayout->addWidget(acheterCarteButton, 0, 0);
    buttonsLayout->addWidget(reserverCarteButton, 0, 1);
    buttonsLayout->addWidget(utiliserPrivilegeButton, 0, 2);

    buttonsLayout->addWidget(prendreJetonsButton, 0, 4);
    buttonsLayout->addWidget(annulerJetonsButton, 0, 5);
    buttonsLayout->addWidget(remplirPlateauButton, 0, 6);

    // Associer chaque bouton à son action respective
    connect(acheterCarteButton, &QPushButton::clicked, this, &BoutonManager::onAcheterCarteClicked);
    connect(reserverCarteButton, &QPushButton::clicked, this, &BoutonManager::onReserverCarteClicked);
    connect(utiliserPrivilegeButton, &QPushButton::clicked, this, &BoutonManager::onUtiliserPrivilegeClicked);
    connect(annulerJetonsButton, &QPushButton::clicked, this, &BoutonManager::onAnnulerJetonsClicked);
    connect(prendreJetonsButton, &QPushButton::clicked, this, &BoutonManager::onPrendreJetonsClicked);
    connect(remplirPlateauButton, &QPushButton::clicked, this, &BoutonManager::onRemplirPlateauClicked);

}

void demanderCouleurJeton(int occ) {

        QMessageBox msgBox;
    msgBox.setText(QString("T'as beaucoup de jetons, tu dois rendre %1 jetons").arg(occ));
    msgBox.setWindowTitle("Rendre des Jetons");

    // Créer des boutons radio
    QRadioButton *rougeButton = new QRadioButton("Rouge");
    QRadioButton *blancButton = new QRadioButton("Blanc");
    QRadioButton *noirButton = new QRadioButton("Noir");
    QRadioButton *orButton = new QRadioButton("Or");
    QRadioButton *perleButton = new QRadioButton("Perle");
    QRadioButton *vertButton = new QRadioButton("Vert");
    QRadioButton *bleuButton = new QRadioButton("Bleu");

    // Ajouter les boutons radio à la boîte de message
    msgBox.addButton(rougeButton, QMessageBox::ActionRole);
    msgBox.addButton(blancButton, QMessageBox::ActionRole);
    msgBox.addButton(noirButton, QMessageBox::ActionRole);
    msgBox.addButton(orButton, QMessageBox::ActionRole);
    msgBox.addButton(perleButton, QMessageBox::ActionRole);
    msgBox.addButton(vertButton, QMessageBox::ActionRole);
    msgBox.addButton(bleuButton, QMessageBox::ActionRole);

    // Afficher la boîte de message et attendre la réponse de l'utilisateur
    msgBox.exec();
    Partie * partie = Partie::get_partie();
    // Retourner la couleur sélectionnée
    if (rougeButton->isChecked()) {
        partie->remettre_jeton(Rouge);
    } else if (blancButton->isChecked()) {
        partie->remettre_jeton(Blanc);
    } else if (noirButton->isChecked()) {
        partie->remettre_jeton(Noir);
    } else if (orButton->isChecked()) {
        partie->remettre_jeton(Or);
    } else if (perleButton->isChecked()) {
        partie->remettre_jeton(Perle);
    } else if (vertButton->isChecked()) {
        partie->remettre_jeton(Vert);
    } else if (bleuButton->isChecked()) {
        partie->remettre_jeton(Bleu);
    }


}

void update_info()
{
    Partie * game = Partie::get_partie();
    PartieWidget * partie = PartieWidget::getInstance();

    partie->updatePlayerInfo(partie->getPlayer1(), game->get_joueur(1).getGemmes().get_Rouge() , game->get_joueur(1).getGemmes().get_Vert(), game->get_joueur(1).getGemmes().get_Bleu(), game->get_joueur(1).getGemmes().get_Blanc(), game->get_joueur(1).getGemmes().get_Perle(), game->get_joueur(1).getGemmes().get_Noir(),game->get_joueur(1).getGemmes().get_Or());
    partie->updatePlayerInfo(partie->getPlayer2(), game->get_joueur(2).getGemmes().get_Rouge() , game->get_joueur(2).getGemmes().get_Vert(), game->get_joueur(2).getGemmes().get_Bleu(), game->get_joueur(2).getGemmes().get_Blanc(), game->get_joueur(2).getGemmes().get_Perle(), game->get_joueur(2).getGemmes().get_Noir(),game->get_joueur(2).getGemmes().get_Or());
    partie->updatePlayerPrivilege(partie->getPlayer1(),game->get_joueur(1).getNbPrivileges());
    partie->updatePlayerPrivilege(partie->getPlayer2(),game->get_joueur(2).getNbPrivileges());
    partie->updatePlayerCoronne(partie->getPlayer1(),game->get_joueur(1).getNbCouronnes());
    partie->updatePlayerCoronne(partie->getPlayer2(),game->get_joueur(2).getNbCouronnes());

}
void update_plateau()
{
    PartieWidget * partie = PartieWidget::getInstance();

    partie->removePlateau(partie->getPlateauWidget());
    PlateauWidget *plateauWidgetInstance = PlateauWidget::creerPlateau();
    partie->afficherPlateau(plateauWidgetInstance);
    partie->setPlateauWidget(plateauWidgetInstance);

}

void fin_tour(){

    Partie* partie = Partie::get_partie();
    //Joueur & joueur = partie->get_joueur(partie->joueur_actif());
    PartieWidget * partieWidget = PartieWidget::getInstance();
    partie->fin_tour();
    if(partie->joueur_actif()==1)    {


        partieWidget->joueurActif(partieWidget->getPlayer1());

    }
    else {

        partieWidget->joueurActif(partieWidget->getPlayer2());
    }
    update_info();
    update_plateau();


}

void volerJeton() {
    PartieWidget * partieWidget = PartieWidget::getInstance();
    QMessageBox msgBox;
    msgBox.setText(QString("Activation de l'effet Voler de la carte !, chosis une couleur de jeton"));
    msgBox.setWindowTitle("Voler un  Jeton");

    // Créer des boutons radio
    QRadioButton *rougeButton = new QRadioButton("Rouge");
    QRadioButton *blancButton = new QRadioButton("Blanc");
    QRadioButton *noirButton = new QRadioButton("Noir");

    QRadioButton *perleButton = new QRadioButton("Perle");
    QRadioButton *vertButton = new QRadioButton("Vert");
    QRadioButton *bleuButton = new QRadioButton("Bleu");

    // Ajouter les boutons radio à la boîte de message
    msgBox.addButton(rougeButton, QMessageBox::ActionRole);
    msgBox.addButton(blancButton, QMessageBox::ActionRole);
    msgBox.addButton(noirButton, QMessageBox::ActionRole);

    msgBox.addButton(perleButton, QMessageBox::ActionRole);
    msgBox.addButton(vertButton, QMessageBox::ActionRole);
    msgBox.addButton(bleuButton, QMessageBox::ActionRole);

    // Afficher la boîte de message et attendre la réponse de l'utilisateur
    msgBox.exec();
    Partie* partie = Partie::get_partie();
    // Retourner la couleur sélectionnée
    try {
    if (rougeButton->isChecked()) {
        partie->voler(partie->get_joueur(partie->joueur_actif()), partie->get_joueur(partie->joueur_adverse()), Rouge);
    } else if (blancButton->isChecked()) {
        partie->voler(partie->get_joueur(partie->joueur_actif()), partie->get_joueur(partie->joueur_adverse()), Blanc);

    } else if (noirButton->isChecked()) {
        partie->voler(partie->get_joueur(partie->joueur_actif()), partie->get_joueur(partie->joueur_adverse()), Noir);

    } else if (perleButton->isChecked()) {
        partie->voler(partie->get_joueur(partie->joueur_actif()), partie->get_joueur(partie->joueur_adverse()), Perle);

    } else if (vertButton->isChecked()) {
        partie->voler(partie->get_joueur(partie->joueur_actif()), partie->get_joueur(partie->joueur_adverse()), Vert);


    } else if (bleuButton->isChecked()) {
        partie->voler(partie->get_joueur(partie->joueur_actif()), partie->get_joueur(partie->joueur_adverse()), Bleu);

    }
    }
    catch (const SplendorException& ex) {
    // Exception caught, display a QMessageBox with the exception message
    QMessageBox::information(partieWidget, "Exception", ex.what());
    }
    update_info();
}



void couleurEffet(CarteJoaillerie & carte) {
    PartieWidget * partieWidget = PartieWidget::getInstance();
    QMessageBox msgBox;
    msgBox.setText(QString("Activation de l'effet Couleur de la carte ! Entrez le type de bonus que la carte achetee doit prendre"));
    msgBox.setWindowTitle("Effet couleur");

    // Créer des boutons radio
    QRadioButton *rougeButton = new QRadioButton("Rouge");
    QRadioButton *blancButton = new QRadioButton("Blanc");
    QRadioButton *noirButton = new QRadioButton("Noir");


    QRadioButton *vertButton = new QRadioButton("Vert");
    QRadioButton *bleuButton = new QRadioButton("Bleu");

    // Ajouter les boutons radio à la boîte de message
    msgBox.addButton(rougeButton, QMessageBox::ActionRole);
    msgBox.addButton(blancButton, QMessageBox::ActionRole);
    msgBox.addButton(noirButton, QMessageBox::ActionRole);


    msgBox.addButton(vertButton, QMessageBox::ActionRole);
    msgBox.addButton(bleuButton, QMessageBox::ActionRole);

    // Afficher la boîte de message et attendre la réponse de l'utilisateur
    msgBox.exec();
    Partie* partie = Partie::get_partie();
    Joueur & joueur = partie->get_joueur(partie->joueur_actif());




    // Retourner la couleur sélectionnée

    if (rougeButton->isChecked()) {

        if(joueur.getBonus().get_Rouge() == 0)
        {
            fin_tour();
            throw SplendorException("Vous n'avez pas de carte rouge ! Veuillez choisir un type de bonus que vous possedez.");

        }
        else
        {
            StockGemmes nouveau_bonus = StockGemmes(0, 0, 0, carte.get_nbBonus());
            carte.setTypeBonus(nouveau_bonus);
            joueur.setBonus(joueur.getBonus()+nouveau_bonus);
            return;
        }




    } else if (blancButton->isChecked()) {
        if(joueur.getBonus().get_Blanc() == 0)
        {
            fin_tour();
            throw SplendorException("Vous n'avez pas de carte blanche ! Veuillez choisir un type de bonus que vous possedez.");

        }
        else
        {
            StockGemmes nouveau_bonus = StockGemmes(0, 0, carte.get_nbBonus());
            carte.setTypeBonus(nouveau_bonus);
            joueur.setBonus(joueur.getBonus()+nouveau_bonus);
            return;
        }

    } else if (noirButton->isChecked()) {

        if(joueur.getBonus().get_Noir() == 0)
        {
           fin_tour();
           throw SplendorException("Vous n'avez pas de carte noire ! Veuillez choisir un type de bonus que vous possedez.");

        }
        else
        {
            StockGemmes nouveau_bonus = StockGemmes(0, 0, 0, 0, carte.get_nbBonus());
            carte.setTypeBonus(nouveau_bonus);
            joueur.setBonus(joueur.getBonus()+nouveau_bonus);
            return;
        }

    } else if (vertButton->isChecked()) {

        if(joueur.getBonus().get_Vert() == 0)
        {
            fin_tour();

           throw SplendorException("Vous n'avez pas de carte verte ! Veuillez choisir un type de bonus que vous possedez.");

        }
        else
        {
            StockGemmes nouveau_bonus = StockGemmes(0, carte.get_nbBonus());
            carte.setTypeBonus(nouveau_bonus);
            joueur.setBonus(joueur.getBonus()+nouveau_bonus);
            return;
        }

    } else if (bleuButton->isChecked()) {
        if(joueur.getBonus().get_Bleu() == 0)
        {
            fin_tour();
            throw SplendorException("Vous n'avez pas de carte bleue ! Veuillez choisir un type de bonus que vous possedez.");

        }
        else
        {
            StockGemmes nouveau_bonus = StockGemmes(carte.get_nbBonus());
            carte.setTypeBonus(nouveau_bonus);
            joueur.setBonus(joueur.getBonus()+nouveau_bonus);
            return;
        }

    }





}

void gemmeEffet(CarteJoaillerie & carte)
{
     PartieWidget * partieWidget = PartieWidget::getInstance();
     Partie* partie = Partie::get_partie();
     Jeton type_carte = Nul;
     StockGemmes stockBonus = carte.get_typeBonus();
     QMessageBox::information(partieWidget, "Capacite", "Activation de l'effet Gemme de la carte !");

     //std::cout<<"StockBonus"<<stockBonus;
     // Vos opérations pour obtenir les valeurs


     if (stockBonus.get_Bleu() > 0) {type_carte = Bleu; std::cout<<"-bleu" ;}
     else if (stockBonus.get_Vert() > 0) {type_carte = Vert; std::cout<<"-vert" ;}
     else if (stockBonus.get_Blanc() > 0) {type_carte = Blanc; std::cout<<"-blanc" ;}
     else if (stockBonus.get_Rouge() > 0) {type_carte = Rouge; std::cout<<"-rouge";}
     else if (stockBonus.get_Noir() > 0) {type_carte = Noir ;  std::cout<<"-noir";}
     else {
    partie->fin_tour();
    update_info();

    if(partie->joueur_actif()==1)    {


        partieWidget->joueurActif(partieWidget->getPlayer1());

    }
    else {

        partieWidget->joueurActif(partieWidget->getPlayer2());
    }
    throw SplendorException( "La carte passee en parametre possède un type de bonus incorrect (Or ou Perle) ou nul ce qui empeche le traitement de l'effet gemme et traduit sans doute une erreur de conception des cartes. Peut-etre l'erreur vient-elle d'un effet gemme place avant un effet couleur.");

     }
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
        QMessageBox::information(partieWidget, "Action", "Le plateau est de cette forme [0:4,0:4] du gauche à droite");


        unsigned int colonne = 0, ligne = 0;
        do
        {

           ligne = QInputDialog::getInt(nullptr, "Entrer la ligne", "Entrez la ligne du jeton a retirer (il doit etre de la couleur de la carte que vous avez achetee) : ", 0, 0, 4, 1);
           colonne = QInputDialog::getInt(nullptr, "Entrer la colonne", "Entrez la colonne du jeton a retirer (il doit etre de la couleur de la carte que vous avez achetee) : ", 0, 0, 4, 1);


            if(partie->get_plateau()[colonne][ligne] != type_carte)
           {
                QMessageBox::information(partieWidget, "Exception", "Ce jeton n'est pas de la meme couleur que la carte que vous avez achetee");
            }


        } while (partie->get_plateau()[colonne][ligne] != type_carte);

         partie->retirer_jetons({colonne, ligne});

    }
    else{
        partie->fin_tour();
        update_info();

        if(partie->joueur_actif()==1)    {


                partieWidget->joueurActif(partieWidget->getPlayer1());

        }
        else {

                partieWidget->joueurActif(partieWidget->getPlayer2());
        }
        throw SplendorException("Aucun jeton du plateau ne correspond a la couleur de la carte que vous avez achetee, l'effet Gemme de la carte n'a pas pu etre active");
    }
}







void BoutonManager::addButtonsToLayout(QVBoxLayout *layout) {
    layout->addLayout(buttonsLayout);
}


void gestionEffet(CarteJoaillerie & carte){
    Partie* partie = Partie::get_partie();
    Joueur & joueur = partie->get_joueur(partie->joueur_actif());
    PartieWidget * partieWidget = PartieWidget::getInstance();
    for(unsigned int pos = 0 ; pos < carte.get_capacite().size() ; pos++)
    {

                switch (carte.get_capacite()[pos])
                {
                case rejouer:

                QMessageBox::information(partieWidget, "Capacite", "Activation de l'effet Rejouer de la carte !");
                partie->ajouter_rejouer();

                return ;


                break;
                case couleur:

                couleurEffet(carte);
                return;

                break;
                case voler:

                   volerJeton();
                return;

                break;
                case gemme:

                gemmeEffet(carte);
                QMessageBox::information(partieWidget, "Information","Jeton pris");
                return;

                break;

                case privilege:

                QMessageBox::information(partieWidget, "Capacite", "Activation de l'effet Privilege de la carte !");
                partie->prend_privilege(joueur);

                return ;


                break;
                }


    }

}



void BoutonManager::gestionEffetRoyale(CarteRoyale & carte)
{
    Partie* partie = Partie::get_partie();
    Joueur& joueur = partie->get_joueur(partie->joueur_actif());
    PartieWidget * partieWidget = PartieWidget::getInstance();

    switch (carte.getCapacite())
    {
    case rejouer:

                QMessageBox::information(partieWidget, "Capacite", "Activation de l'effet Rejouer de la carte !");
                partie->ajouter_rejouer();
                update_info();
                update_plateau();
                partie->fin_tour();
                return ;


                break;

    case privilege:

                QMessageBox::information(partieWidget, "Capacite", "Activation de l'effet Privilege de la carte !");
                partie->prend_privilege(joueur);
                update_info();
                update_plateau();
                return;
                break;

    case voler:

                volerJeton();
                return;
                break;



    }
}

void afficherCarteparligne(const CarteJoaillerie& c,unsigned int ligne,std::ostream& os) {

    //if (ligne<1 || ligne>7)  throw SplendorException("Une carte s'affiche en 7 lignes.\n");
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


void afficherPyramide()
{
    Partie * partie = Partie::get_partie();
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


void BoutonManager::onAcheterCarteClicked() {

     Partie* partie = Partie::get_partie();
    Joueur & joueur = partie->get_joueur(partie->joueur_actif());
     PartieWidget * partieWidget = PartieWidget::getInstance();


    afficherPyramide();

      //InterfaceConsole  ic;
      //ic.afficherPyramide();
    QMessageBox msgBox;
    msgBox.setText("Souhaitez-vous acheter une des cartes que vous avez réservées?");
                   msgBox.addButton("Oui", QMessageBox::YesRole);
                   msgBox.addButton("Non", QMessageBox::NoRole);
                   //msgBox.setDefaultButton(QMessageBox::No);

                   int choice = msgBox.exec();
                   bool ok;
                   try{
                   if (choice == 0) {

    int numeroCarte = QInputDialog::getInt(nullptr, "Numéro de la carte","Entrez le numero de la carte que vous souhaitez acheter (à partir de 1):",1,1,joueur.getCartesJoailleriesReservees().size(),1,&ok );

        gestionEffet(joueur.acheterCarteReservee(numeroCarte));


                   } else {

                        // Boîte de dialogue pour obtenir le niveau de la carte à réserver
                        int niveauCarte = QInputDialog::getInt(nullptr, "Niveau de la carte", "Entrez le niveau de la carte à acheter (1-3):", 1, 1, 3, 1, &ok);

                        if (!ok) {
                            return;
                        }

                        // Boîte de dialogue pour obtenir le numéro de la carte à réserver
                        int numeroCarte = QInputDialog::getInt(nullptr, "Numéro de la carte", "Entrez le numéro de la carte à acheter :", 1, 1, 6 - niveauCarte , 1, &ok);

                        if (!ok) {
                            return;
                          }
                        gestionEffet( partie->acheter_carte(joueur,niveauCarte,numeroCarte));


                        //ic.gestion_effets(partie->get_joueur(partie->joueur_actif()).acheterCarteReservee(numeroCarte));
                        }




                  fin_tour();

                   }      catch (const SplendorException& ex) {
                   // Exception caught, display a QMessageBox with the exception message
                   QMessageBox::information(partieWidget, "Exception", ex.what());
                   }
}


void BoutonManager::onAnnulerJetonsClicked()
{

          PlateauWidget * plateauWidget = PlateauWidget::getInstance();
                   plateauWidget->emptyJetons();


}










void BoutonManager::onReserverCarteClicked() {
    Partie * partie = Partie::get_partie();
    PartieWidget * partieWidget = PartieWidget::getInstance();
    bool ok;
    int ligneOr = QInputDialog::getInt(nullptr, "Ligne du jeton Or", "Entrez la ligne du jeton Or (0-4):", 0, 0, 4, 1, &ok);

    if (!ok) {
        // L'utilisateur a annulé la saisie
        return;
    }

    // Boîte de dialogue pour obtenir la colonne du jeton Or
    int colonneOr = QInputDialog::getInt(nullptr, "Colonne du jeton Or", "Entrez la colonne du jeton Or (0-4):", 0, 0, 4, 1, &ok);

    if (!ok) {
        return;
    }
    try
    {
    partie->retirer_jetons_or({colonneOr,ligneOr});

    // Boîte de dialogue pour obtenir le niveau de la carte à réserver
    int niveauCarte = QInputDialog::getInt(nullptr, "Niveau de la carte", "Entrez le niveau de la carte à réserver (1-3):", 1, 1, 3, 1, &ok);

    if (!ok) {
        return;
    }

    // Boîte de dialogue pour obtenir le numéro de la carte à réserver
    int numeroCarte = QInputDialog::getInt(nullptr, "Numéro de la carte", "Entrez le numéro de la carte à réserver :", 1, 1, 6 - niveauCarte , 1, &ok);

    if (!ok) {
        return;
    }

    partie->reserver_carte(partie->get_joueur(partie->joueur_actif()), niveauCarte, numeroCarte);
    fin_tour();
    }
    catch (const SplendorException& ex) {
    // Exception caught, display a QMessageBox with the exception message
    QMessageBox::information(parentWidget, "Exception", ex.what());
    }







}

void BoutonManager::onUtiliserPrivilegeClicked() {
    PlateauWidget * plateauWidget = PlateauWidget::getInstance();
    //Plateau& plateau = Plateau::get_plateau();
   // PartieWidget * partie = PartieWidget::getInstance();
    Partie * game = Partie::get_partie();
    plateauWidget->emptyJetons();
    QMessageBox::information(parentWidget, "Action", "Le plateau est de cette forme [0:4,0:4] du gauche à droite");

        unsigned int row = QInputDialog::getInt(nullptr, "Entrer la ligne", "Entrez le numéro de ligne du jeton que vous souhaitez avoir :", 0, 0, 4, 1);
        unsigned int col = QInputDialog::getInt(nullptr, "Entrer la colonne", "Entrez le numéro de colonne jeton que vous souhaitez avoir :", 0, 0, 4, 1);


        // Vérifiez si l'utilisateur a appuyé sur OK

            // Utilisez les valeurs de row et col comme nécessaire
            if(game->joueur_actif()==1)
                try{
                    game->utilise_privilege(game->get_joueur(1),col,row);


                }
                catch (const SplendorException& ex) {
                    // Exception caught, display a QMessageBox with the exception message
                    QMessageBox::information(parentWidget, "Exception", ex.what());
                }
            else
                try{
                    game->utilise_privilege(game->get_joueur(2),col,row);
                }
                catch (const SplendorException& ex) {
                    // Exception caught, display a QMessageBox with the exception message
                    QMessageBox::information(parentWidget, "Exception", ex.what());
                }




     update_plateau();

    update_info();

    plateauWidget->emptyJetons();



}

void verifierCarteRoyale(Joueur & joueur)
{
    PartieWidget * partieWidget = PartieWidget::getInstance();
    Partie * partie = Partie::get_partie();
    if (partie->get_cartes_royales().size() > 0 && (joueur.getNbCouronnes() >= 3 && joueur.getCartesRoyalesPossedees().size() == 0) && (joueur.getNbCouronnes() >= 6 && joueur.getCartesRoyalesPossedees().size() <= 1))
    {
          QMessageBox::information(partieWidget, "Information", "Vous avez rempli les conditions pour obtenir une carte Royale ! Cliquer sur la carte Royale à prendre");
    }


}



void BoutonManager::onPrendreJetonsClicked() {
   PlateauWidget * plateauWidget = PlateauWidget::getInstance();
    //Plateau& plateau = Plateau::get_plateau();
   PartieWidget * partie = PartieWidget::getInstance();
    std::map<Case, std::string>& jetons = plateauWidget->getJetonsTaken();

   std::vector<std::array<unsigned int, 2>> positionArrayVector;

   for (const auto& pair : jetons) {
            const Case& position = pair.first;
            std::array<unsigned int, 2> tposition = {static_cast<unsigned int>(position.row), static_cast<unsigned int>(position.col)};
            positionArrayVector.push_back(tposition);
   }

   Partie* game = Partie::get_partie();


   try {
   if(jetons.size()==1)
   {
            StockGemmes stock;



            game->retirer_jetons(positionArrayVector[0]);



    }
    if(jetons.size()==2)
    {

         StockGemmes stock;



             game->retirer_jetons(positionArrayVector[0],positionArrayVector[1]);



    }
    if(jetons.size()==3)
    {

         StockGemmes stock;


         game->retirer_jetons(positionArrayVector[0],positionArrayVector[1],positionArrayVector[2]);




    }

    plateauWidget->emptyJetons();


    Joueur & joueur = game->get_joueur(game->joueur_actif());
    while (total_stock(joueur.getGemmes()) > 10)
         try{
                            demanderCouleurJeton(total_stock(joueur.getGemmes())-10);
         }
         catch (const SplendorException& ex) {

                            QMessageBox::information(parentWidget, "Exception", ex.what());
         }

  fin_tour();



   } catch (const SplendorException& ex) {
  plateauWidget->emptyJetons();
         // Exception caught, display a QMessageBox with the exception message
         QMessageBox::information(parentWidget, "Exception", ex.what());
    }







}

void BoutonManager::onRemplirPlateauClicked() {
    Partie* game = Partie::get_partie();

   // PartieWidget * partie = PartieWidget::getInstance();
    if(joueur1 == 1)
    {
            game->remplir_plateau(game->get_joueur(1));

    }
    else  {
            game->remplir_plateau(game->get_joueur(2));

    }
    update_info();
    update_plateau();


}


