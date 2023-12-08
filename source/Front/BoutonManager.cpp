#include "BoutonManager.h"
#include <QRadioButton>
#include <QMessageBox>
#include "PartieWidget.h"
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
    volerButton->setStyleSheet(buttonStyle);
    prendreJetonsButton->setStyleSheet(buttonStyle);
    remplirPlateauButton->setStyleSheet(buttonStyle);

    buttonsLayout->addWidget(acheterCarteButton, 0, 0);
    buttonsLayout->addWidget(reserverCarteButton, 0, 1);
    buttonsLayout->addWidget(utiliserPrivilegeButton, 0, 2);
    buttonsLayout->addWidget(volerButton, 0, 3);
    buttonsLayout->addWidget(prendreJetonsButton, 0, 4);
    buttonsLayout->addWidget(remplirPlateauButton, 0, 5);

    // Associer chaque bouton à son action respective
    connect(acheterCarteButton, &QPushButton::clicked, this, &BoutonManager::onAcheterCarteClicked);
    connect(reserverCarteButton, &QPushButton::clicked, this, &BoutonManager::onReserverCarteClicked);
    connect(utiliserPrivilegeButton, &QPushButton::clicked, this, &BoutonManager::onUtiliserPrivilegeClicked);
    connect(volerButton, &QPushButton::clicked, this, &BoutonManager::onVolerDisabledClicked);
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
    Partie& partie = Partie::get_partie();
    // Retourner la couleur sélectionnée
    if (rougeButton->isChecked()) {
        partie.remettre_jeton(Rouge);
    } else if (blancButton->isChecked()) {
        partie.remettre_jeton(Blanc);
    } else if (noirButton->isChecked()) {
        partie.remettre_jeton(Noir);
    } else if (orButton->isChecked()) {
        partie.remettre_jeton(Or);
    } else if (perleButton->isChecked()) {
        partie.remettre_jeton(Perle);
    } else if (vertButton->isChecked()) {
        partie.remettre_jeton(Vert);
    } else if (bleuButton->isChecked()) {
        partie.remettre_jeton(Bleu);
    }


}

void update_info()
{
    Partie & game = Partie::get_partie();
    PartieWidget * partie = PartieWidget::getInstance();

    partie->updatePlayerInfo("Joueur 1", game.get_joueur(1).getGemmes().get_Rouge() , game.get_joueur(1).getGemmes().get_Vert(), game.get_joueur(1).getGemmes().get_Bleu(), game.get_joueur(1).getGemmes().get_Blanc(), game.get_joueur(1).getGemmes().get_Perle(), game.get_joueur(1).getGemmes().get_Noir(),game.get_joueur(1).getGemmes().get_Or());
    partie->updatePlayerInfo("Joueur 2", game.get_joueur(2).getGemmes().get_Rouge() , game.get_joueur(2).getGemmes().get_Vert(), game.get_joueur(2).getGemmes().get_Bleu(), game.get_joueur(2).getGemmes().get_Blanc(), game.get_joueur(2).getGemmes().get_Perle(), game.get_joueur(2).getGemmes().get_Noir(),game.get_joueur(2).getGemmes().get_Or());
    partie->updatePlayerPrivilege("Joueur 1",game.get_joueur(1).getNbPrivileges());
    partie->updatePlayerPrivilege("Joueur 2",game.get_joueur(2).getNbPrivileges());
    partie->updatePlayerCoronne("Joueur 1",game.get_joueur(1).getNbCouronnes());
    partie->updatePlayerCoronne("Joueur 2",game.get_joueur(2).getNbCouronnes());

}

void volerJeton() {
    PartieWidget * partieWidget = PartieWidget::getInstance();
    QMessageBox msgBox;
    msgBox.setText(QString("Congratulations, tu peux voler un jeton de ton adversaire, chosis une couleur de jeton"));
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
    Partie& partie = Partie::get_partie();
    // Retourner la couleur sélectionnée
    try {
    if (rougeButton->isChecked()) {
        partie.voler(partie.get_joueur(partie.joueur_actif()), partie.get_joueur(partie.joueur_adverse()), Rouge);
    } else if (blancButton->isChecked()) {
        partie.voler(partie.get_joueur(partie.joueur_actif()), partie.get_joueur(partie.joueur_adverse()), Blanc);

    } else if (noirButton->isChecked()) {
        partie.voler(partie.get_joueur(partie.joueur_actif()), partie.get_joueur(partie.joueur_adverse()), Noir);

    } else if (perleButton->isChecked()) {
        partie.voler(partie.get_joueur(partie.joueur_actif()), partie.get_joueur(partie.joueur_adverse()), Perle);

    } else if (vertButton->isChecked()) {
        partie.voler(partie.get_joueur(partie.joueur_actif()), partie.get_joueur(partie.joueur_adverse()), Vert);


    } else if (bleuButton->isChecked()) {
        partie.voler(partie.get_joueur(partie.joueur_actif()), partie.get_joueur(partie.joueur_adverse()), Bleu);

    }
    }
    catch (const SplendorException& ex) {
    // Exception caught, display a QMessageBox with the exception message
    QMessageBox::information(partieWidget, "Exception", ex.what());
    }
    update_info();
}

void BoutonManager::addButtonsToLayout(QVBoxLayout *layout) {
    layout->addLayout(buttonsLayout);
}
void update_plateau()
{
    PartieWidget * partie = PartieWidget::getInstance();
    partie->removePlateau(partie->getPlateauWidget());
    PlateauWidget *plateauWidgetInstance = PlateauWidget::creerPlateau();
    partie->afficherPlateau(plateauWidgetInstance);
    partie->setPlateauWidget(plateauWidgetInstance);

}


void BoutonManager::onAcheterCarteClicked() {
    if(joueur1 == 1)    {

        joueur1=0;}
    else {
        joueur1=1;
    }


}

void BoutonManager::onReserverCarteClicked() {
    if(joueur1 == 1)    {

        joueur1=0;}
        else {
            joueur1=1;
    }


}

void BoutonManager::onUtiliserPrivilegeClicked() {
    PlateauWidget * plateauWidget = PlateauWidget::getInstance();
    Plateau& plateau = Plateau::get_plateau();
   // PartieWidget * partie = PartieWidget::getInstance();
    Partie& game = Partie::get_partie();
    plateauWidget->emptyJetons();
    QMessageBox::information(parentWidget, "Action", "Le plateau est de cette forme [0:4,0:4] du gauche à droite");

        unsigned int row = QInputDialog::getInt(nullptr, "Entrer la ligne", "Entrez le numéro de ligne du jeton que vous souhaitez avoir :", 0, 0, 4, 1);
        unsigned int col = QInputDialog::getInt(nullptr, "Entrer la colonne", "Entrez le numéro de colonne jeton que vous souhaitez avoir :", 0, 0, 4, 1);


        // Vérifiez si l'utilisateur a appuyé sur OK

            // Utilisez les valeurs de row et col comme nécessaire
            if(joueur1==1)
                try{
                    game.utilise_privilege(game.get_joueur(1),row,col);
                    QMessageBox::information(parentWidget, "Action", "Hi");

                }
                catch (const SplendorException& ex) {
                    // Exception caught, display a QMessageBox with the exception message
                    QMessageBox::information(parentWidget, "Exception", ex.what());
                }
            else
                try{
                    game.utilise_privilege(game.get_joueur(2),row,col);
                }
                catch (const SplendorException& ex) {
                    // Exception caught, display a QMessageBox with the exception message
                    QMessageBox::information(parentWidget, "Exception", ex.what());
                }




     update_plateau();

    update_info();

    plateauWidget->emptyJetons();



}

void BoutonManager::onVolerDisabledClicked() {
 volerJeton();

}

void BoutonManager::onPrendreJetonsClicked() {
   PlateauWidget * plateauWidget = PlateauWidget::getInstance();
    Plateau& plateau = Plateau::get_plateau();
   PartieWidget * partie = PartieWidget::getInstance();
    std::map<Case, std::string>& jetons = plateauWidget->getJetonsTaken();

   std::vector<std::array<unsigned int, 2>> positionArrayVector;

   for (const auto& pair : jetons) {
            const Case& position = pair.first;
            std::array<unsigned int, 2> tposition = {static_cast<unsigned int>(position.row), static_cast<unsigned int>(position.col)};
            positionArrayVector.push_back(tposition);
   }

   Partie& game = Partie::get_partie();

   if(jetons.size()==1)
   {       try {
            StockGemmes stock;
            //stock=plateau.actionRetirerJetons(positionArrayVector[0]);


            game.retirer_jetons(positionArrayVector[0]);

            }
            catch (const SplendorException& ex) {
            // Exception caught, display a QMessageBox with the exception message
            QMessageBox::information(parentWidget, "Exception", ex.what());
            }
    }
    if(jetons.size()==2)
    {
            try {
         StockGemmes stock;
         //stock=plateau.actionRetirerJetons(positionArrayVector[0],positionArrayVector[1]);


             game.retirer_jetons(positionArrayVector[0],positionArrayVector[1]);


            }
            catch (const SplendorException& ex) {
         // Exception caught, display a QMessageBox with the exception message
         QMessageBox::information(parentWidget, "Exception", ex.what());
            }
    }
    if(jetons.size()==3)
    {
            try {
         StockGemmes stock;


         game.retirer_jetons(positionArrayVector[0],positionArrayVector[1],positionArrayVector[2]);

            }
            catch (const SplendorException& ex) {
         // Exception caught, display a QMessageBox with the exception message
         QMessageBox::information(parentWidget, "Exception", ex.what());
            }
    }


    update_plateau();



    plateauWidget->emptyJetons();

   if(joueur1 == 1)    {

            joueur1=0;
            partie->joueurActif("Joueur 2");
   }
    else {

            joueur1=1;
            partie->joueurActif("Joueur 1");

    }
   Joueur & joueur = game.get_joueur(game.joueur_actif());
    while (total_stock(joueur.getGemmes()) > 10)
            try{
            demanderCouleurJeton(total_stock(joueur.getGemmes())-10);
            }
            catch (const SplendorException& ex) {
            QMessageBox::information(parentWidget, "Exception", ex.what());
            }

    update_info();

   game.fin_tour();


}

void BoutonManager::onRemplirPlateauClicked() {
    Partie& game = Partie::get_partie();

    PartieWidget * partie = PartieWidget::getInstance();
    if(joueur1 == 1)
    {
            game.remplir_plateau(game.get_joueur(1));

    }
    else  {
            game.remplir_plateau(game.get_joueur(2));

    }
    update_info();
    update_plateau();


}
