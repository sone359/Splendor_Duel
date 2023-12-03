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
    PlateauWidget * plateauWidget = PlateauWidget::getInstance();
    Plateau& plateau = Plateau::get_plateau();
    PartieWidget * partie = PartieWidget::getInstance();
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





    partie->removePlateau(partie->getPlateauWidget());
    PlateauWidget *plateauWidgetInstance = PlateauWidget::creerPlateau();
    partie->afficherPlateau(plateauWidgetInstance);
    partie->setPlateauWidget(plateauWidgetInstance);
    partie->updatePlayerPrivilege("Joueur 1",game.get_joueur(1).getNbPrivileges());
    partie->updatePlayerPrivilege("Joueur 2",game.get_joueur(2).getNbPrivileges());

    plateauWidget->emptyJetons();

    if(joueur1 == 1)    {
    QMessageBox::information(parentWidget, "Action", "Joueur 1");
    partie->updatePlayerInfo("Joueur 1", game.get_joueur(1).getGemmes().get_Rouge() , game.get_joueur(1).getGemmes().get_Vert(), game.get_joueur(1).getGemmes().get_Bleu(), game.get_joueur(1).getGemmes().get_Blanc(), game.get_joueur(1).getGemmes().get_Perle(), game.get_joueur(1).getGemmes().get_Noir(),game.get_joueur(1).getGemmes().get_Or());

   }
    else { QMessageBox::information(parentWidget, "Action", "Joueur 2");
    Joueur& joueur = game.get_joueur(2);
    std::cout << "\nJetons possedes par le joueur 2 "  <<" : " << "B x " << joueur.getGemmes().get_Bleu() << ", V x " << joueur.getGemmes().get_Vert() << ", W x " << joueur.getGemmes().get_Blanc() << ", R x " << joueur.getGemmes().get_Rouge() << ", N x " << joueur.getGemmes().get_Noir() << ", P x " << joueur.getGemmes().get_Perle() << ", O x " << joueur.getGemmes().get_Or() << std::endl << std::endl;
    partie->updatePlayerInfo("Joueur 2", game.get_joueur(2).getGemmes().get_Rouge() , game.get_joueur(2).getGemmes().get_Vert(), game.get_joueur(2).getGemmes().get_Bleu(), game.get_joueur(2).getGemmes().get_Blanc(), game.get_joueur(2).getGemmes().get_Perle(), game.get_joueur(2).getGemmes().get_Noir(),game.get_joueur(2).getGemmes().get_Or());

    }

}

void BoutonManager::onVolerDisabledClicked() {

    QString message = "Le jeton de quelle couleur voulez-vous voler ?";
    QString colorChoice = QInputDialog::getText(nullptr, "Choix de couleur", message);


    if (!colorChoice.isEmpty()) {
            // Process the color choice (you can store it in a variable, etc.)
            // For now, we'll just display it in a message box
            QString resultMessage = "Vous avez choisi de voler le jeton de couleur : " + colorChoice;
            QMessageBox::information(nullptr, "Choix enregistré", resultMessage);
    } else {
            // User canceled the input
            qDebug() << "L'utilisateur a annulé le choix de couleur.";
    }
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


//    QWidget *widget = new QWidget;
//    QVBoxLayout* layout = new QVBoxLayout(widget);

//    // Assuming PlateauWidget::creerPlateau() returns a PlateauWidget instance
   //PlateauWidget *plateauWidgetInstance = PlateauWidget::creerPlateau();


//    layout->addWidget(plateauWidgetInstance);
//    widget->setLayout(layout);

//    widget->show();
    //partie->remove(plateauWidget);
    partie->removePlateau(partie->getPlateauWidget());
    PlateauWidget *plateauWidgetInstance = PlateauWidget::creerPlateau();
    partie->afficherPlateau(plateauWidgetInstance);
    partie->setPlateauWidget(plateauWidgetInstance);
    partie->updatePlayerPrivilege("Joueur 1",game.get_joueur(1).getNbPrivileges());
    partie->updatePlayerPrivilege("Joueur 2",game.get_joueur(2).getNbPrivileges());


    plateauWidget->emptyJetons();

   if(joueur1 == 1)    {
            QMessageBox::information(parentWidget, "Action", "Joueur 1");
            partie->updatePlayerInfo("Joueur 1", game.get_joueur(1).getGemmes().get_Rouge() , game.get_joueur(1).getGemmes().get_Vert(), game.get_joueur(1).getGemmes().get_Bleu(), game.get_joueur(1).getGemmes().get_Blanc(), game.get_joueur(1).getGemmes().get_Perle(), game.get_joueur(1).getGemmes().get_Noir(),game.get_joueur(1).getGemmes().get_Or());

            joueur1=0;
            partie->joueurActif("Joueur 2");
   }
    else { QMessageBox::information(parentWidget, "Action", "Joueur 2");
            Joueur& joueur = game.get_joueur(2);
            std::cout << "\nJetons possedes par le joueur 2 "  <<" : " << "B x " << joueur.getGemmes().get_Bleu() << ", V x " << joueur.getGemmes().get_Vert() << ", W x " << joueur.getGemmes().get_Blanc() << ", R x " << joueur.getGemmes().get_Rouge() << ", N x " << joueur.getGemmes().get_Noir() << ", P x " << joueur.getGemmes().get_Perle() << ", O x " << joueur.getGemmes().get_Or() << std::endl << std::endl;
            partie->updatePlayerInfo("Joueur 2", game.get_joueur(2).getGemmes().get_Rouge() , game.get_joueur(2).getGemmes().get_Vert(), game.get_joueur(2).getGemmes().get_Bleu(), game.get_joueur(2).getGemmes().get_Blanc(), game.get_joueur(2).getGemmes().get_Perle(), game.get_joueur(2).getGemmes().get_Noir(),game.get_joueur(2).getGemmes().get_Or());

            joueur1=1;
            partie->joueurActif("Joueur 1");


    }
   game.fin_tour();

//    acheterCarteButton->setDisabled(true);
//    reserverCarteButton->setDisabled(true);
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
    partie->updatePlayerPrivilege("Joueur 1",game.get_joueur(1).getNbPrivileges());
    partie->updatePlayerPrivilege("Joueur 2",game.get_joueur(2).getNbPrivileges());


    partie->removePlateau(partie->getPlateauWidget());
    PlateauWidget *plateauWidgetInstance = PlateauWidget::creerPlateau();
    partie->afficherPlateau(plateauWidgetInstance);
    partie->setPlateauWidget(plateauWidgetInstance);

    QMessageBox::information(parentWidget, "Action", "Remplir le plateau sélectionné");
}
