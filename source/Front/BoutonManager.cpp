#include "BoutonManager.h"
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

    volerButton->setDisabled(true);


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

void BoutonManager::addButtonsToLayout(QVBoxLayout *layout) {
    layout->addLayout(buttonsLayout);
}



void BoutonManager::onAcheterCarteClicked() {
    if(joueur1 == 1)    {
        QMessageBox::information(parentWidget, "Action", "Joueur 1");
        joueur1=0;}
    else { QMessageBox::information(parentWidget, "Action", "Joueur 2");
        joueur1=1;
    }

    QMessageBox::information(parentWidget, "Action", "Acheter une carte sélectionné");
    prendreJetonsButton->setDisabled(true);
    reserverCarteButton->setDisabled(true);
}

void BoutonManager::onReserverCarteClicked() {
    if(joueur1 == 1)    {
        QMessageBox::information(parentWidget, "Action", "Joueur 1");
        joueur1=0;}
        else { QMessageBox::information(parentWidget, "Action", "Joueur 2");
            joueur1=1;
    }
    QMessageBox::information(parentWidget, "Action", "Réserver une carte sélectionné");
    acheterCarteButton->setDisabled(true);
    prendreJetonsButton->setDisabled(true);
}

void BoutonManager::onUtiliserPrivilegeClicked() {
    QMessageBox::information(parentWidget, "Action", "Utiliser un privilège sélectionné");
}

void BoutonManager::onVolerDisabledClicked() {
    // Cette action est désactivée, donc cette partie du code ne sera pas atteinte
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
            if(joueur1 == 1)

            game.retirer_jetons(game.get_joueur(1),positionArrayVector[0]);

            else
                game.retirer_jetons(game.get_joueur(2),positionArrayVector[0]);
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
         if(joueur1 == 1)

             game.retirer_jetons(game.get_joueur(1),positionArrayVector[0],positionArrayVector[1]);

         else
             game.retirer_jetons(game.get_joueur(2),positionArrayVector[0],positionArrayVector[1]);

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
         //stock=plateau.actionRetirerJetons(positionArrayVector[0],positionArrayVector[1],positionArrayVector[2]);
         if(joueur1 == 1)

         game.retirer_jetons(game.get_joueur(1),positionArrayVector[0],positionArrayVector[1],positionArrayVector[2]);

         else
             game.retirer_jetons(game.get_joueur(2),positionArrayVector[0],positionArrayVector[1],positionArrayVector[2]);
            }
            catch (const SplendorException& ex) {
         // Exception caught, display a QMessageBox with the exception message
         QMessageBox::information(parentWidget, "Exception", ex.what());
            }
    }


//    QWidget *widget = new QWidget;
//    QVBoxLayout* layout = new QVBoxLayout(widget);

//    // Assuming PlateauWidget::creerPlateau() returns a PlateauWidget instance
   //PlateauWidget *plateauWidgetInstance = PlateauWidget::creerPlateau();


//    layout->addWidget(plateauWidgetInstance);
//    widget->setLayout(layout);

//    widget->show();
    //partie->remove(plateauWidget);
    PlateauWidget *plateauWidgetInstance = PlateauWidget::creerPlateau();
    partie->afficherPlateau(plateauWidgetInstance);
    partie->updatePlayerPrivilege("Joueur 1",game.get_joueur(1).getNbPrivileges());
    partie->updatePlayerPrivilege("Joueur 2",game.get_joueur(2).getNbPrivileges());


    plateauWidget->emptyJetons();

   if(joueur1 == 1)    {
            QMessageBox::information(parentWidget, "Action", "Joueur 1");
            partie->updatePlayerInfo("Joueur 1", game.get_joueur(1).getGemmes().get_Rouge() , game.get_joueur(1).getGemmes().get_Vert(), game.get_joueur(1).getGemmes().get_Bleu(), game.get_joueur(1).getGemmes().get_Blanc(), game.get_joueur(1).getGemmes().get_Perle(), game.get_joueur(1).getGemmes().get_Noir(),game.get_joueur(1).getGemmes().get_Or());

            joueur1=0;}
    else { QMessageBox::information(parentWidget, "Action", "Joueur 2");
            partie->updatePlayerInfo("Joueur 2", game.get_joueur(2).getGemmes().get_Rouge() , game.get_joueur(2).getGemmes().get_Vert(), game.get_joueur(2).getGemmes().get_Bleu(), game.get_joueur(2).getGemmes().get_Blanc(), game.get_joueur(2).getGemmes().get_Perle(), game.get_joueur(2).getGemmes().get_Noir(),game.get_joueur(2).getGemmes().get_Or());

            joueur1=1;
    }

//    acheterCarteButton->setDisabled(true);
//    reserverCarteButton->setDisabled(true);
}

void BoutonManager::onRemplirPlateauClicked() {
    Partie& game = Partie::get_partie();

    PartieWidget * partie = PartieWidget::getInstance();
    if(joueur1 == 1)
    {
            game.remplir_plateau(game.get_joueur(1));

            joueur1=0;

    }
    else  {
            game.remplir_plateau(game.get_joueur(2));
            joueur1=1;
    }
    partie->updatePlayerPrivilege("Joueur 1",game.get_joueur(1).getNbPrivileges());
    partie->updatePlayerPrivilege("Joueur 2",game.get_joueur(2).getNbPrivileges());


    PlateauWidget *plateauWidgetInstance = PlateauWidget::creerPlateau();
    partie->afficherPlateau(plateauWidgetInstance);


    QMessageBox::information(parentWidget, "Action", "Remplir le plateau sélectionné");
}
