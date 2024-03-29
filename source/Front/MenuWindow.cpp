#include "MenuWindow.h"
#include "PlateauWidget.h"
#include "BoutonManager.h"
#include "PartieWidget.h"
#include "../Back/partie.h"
#include "../Back/plateau.h"
#include "../Back/sac.h"
#include "../Back/CarteRoyale.h"
#include "regle_jeu.h"
#include "Effet.h"
#include <QApplication>
#include <iostream>
#include <QVBoxLayout>
#include <QPushButton>
#include <QApplication>
#include <QScreen>
#include <QSpacerItem>
#include <QLabel>

MenuWindow::MenuWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    //setStyleSheet("MenuWindow { background-color: #00FF00; }");
    setStyleSheet("MenuWindow {"
                  "background-image: url(:/Images/fond_menu_splendor.jpg);"
                  "background-repeat: no-repeat;"
                  "background-position: center;"
                  "}");
    setFixedSize(1080, 750);



    layout->addItem(new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Expanding));

    QLabel *titleLabel = new QLabel("");
    titleLabel->setAlignment(Qt::AlignHCenter);
    titleLabel->setFont(QFont("Courier New", 80, QFont::Bold));
    titleLabel->setStyleSheet("QLabel { color: white; }");
    layout->addWidget(titleLabel);
    QPushButton *button1 = new QPushButton("Jouer à deux");
    QPushButton *button2 = new QPushButton("Jouer contre IA");
    QPushButton *button3 = new QPushButton("Quitter le jeu");
    QPushButton *button4 = new QPushButton("Règles du jeu");

    // Changer la police des boutons
    QFont buttonFont("Greek", 22, QFont::Bold);
    button1->setFont(buttonFont);
    button2->setFont(buttonFont);
    button3->setFont(buttonFont);
    button4->setFont(buttonFont);

    // Modifier la taille des boutons
    button1->setFixedSize(300, 70);
    button2->setFixedSize(300, 70);
    button3->setFixedSize(300, 70);
    button4->setFixedSize(300, 70);

    //Modifier la couleur et les angles des boutons
    button1->setStyleSheet("QPushButton { background-color: #05AAE4; color: #DB8822; border-radius: 10px; border-width: 2px ; border-color: #F1EEA1}");
    button2->setStyleSheet("QPushButton { background-color: #05AAE4; color: #DB8822; border-radius: 10px; border-width: 2px ; border-color: #F1EEA1}");
    button3->setStyleSheet("QPushButton { background-color: #05AAE4; color: #DB8822; border-radius: 10px; border-width: 2px ; border-color: #F1EEA1}");
    button4->setStyleSheet("QPushButton { background-color: #05AAE4; color: #DB8822; border-radius: 10px; border-width: 2px ; border-color: #F1EEA1}");



    // Centrer les boutons horizontalement
    layout->addWidget(button1, 0, Qt::AlignHCenter);

    layout->addWidget(button2, 0, Qt::AlignHCenter);
    layout->addWidget(button3, 0, Qt::AlignHCenter);
    layout->addWidget(button4, 0, Qt::AlignHCenter);
    layout->addItem(new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding));


    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);

    connect(button1, &QPushButton::clicked, this, &MenuWindow::onButton1Clicked);
    connect(button2, &QPushButton::clicked, this, &MenuWindow::onButton2Clicked);
    connect(button3, &QPushButton::clicked, this, &MenuWindow::onButton3Clicked);
    connect(button4, &QPushButton::clicked, this, &MenuWindow::onButton4Clicked);

    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    setGeometry(screenGeometry);

    // Définir le titre de la fenêtre principale
    setWindowTitle("Menu Splendor");
}




void MenuWindow::onButton1Clicked() {
    Partie * game=nullptr;
    QMessageBox msgBox;
   msgBox.setWindowTitle("Continuez ?");
    msgBox.setText("Que souhaitez-vous faire?");
    msgBox.addButton("Nouvelle Partie", QMessageBox::AcceptRole);
    msgBox.addButton("Continuer Partie", QMessageBox::RejectRole);

    // Définir le bouton par défaut sur "Nouvelle Partie"
    //msgBox.setDefaultButton(QMessageBox::AcceptRole);

    // Afficher la boîte de dialogue et attendre la réponse
    int choice = msgBox.exec();

    // Traiter la réponse en fonction du bouton cliqué
    if (choice == 0) {
        // Action si "Nouvelle Partie" est cliqué
        game = Partie::get_partie();
    } else  {
        // Action si "Continuer Partie" est cliqué
       game = Partie::get_partie("../../data/sauvegarde");
    }

    game->get_joueur(1).setNbCouronnes(3);




    // Create and add the PlateauWidget to the layout
    PlateauWidget * plateauWidget = PlateauWidget::getInstance();

    plateauWidget = PlateauWidget::creerPlateau();
    PartieWidget * partie = PartieWidget::getInstance();
    partie->setWindowTitle("Splender Duel");
    //pyramidefront *pyramide;
    //partie->displayRoyalImages(imagePaths);
    QString  playerName1  =     QInputDialog::getText(nullptr, "Nom du joueur 1", "Le premier joueur  est:");
    QString   playerName2 = QInputDialog::getText(nullptr, "Nom du joueur 2", "Le deuxième joueur  est:");






    // Set the player names in PartieWidget (assuming you have setters for player names)
//
//    QMessageBox(parentWidget,"information",playerName2);
    partie->setPlayer1(playerName1);
    partie->setPlayer2(playerName2);

    partie->setLabel(playerName1,playerName2);

    // Appliquer l'image de fond à PartieWidget
    partie->setStyleSheet("background-color: #fffaca");
    pyramidefront * pyramide=pyramidefront::getInstance();

    pyramide = pyramidefront::creerPyramide();


//    partie->afficherPlateau(plateauWidget);
//    partie->displayPyramide(pyramide);
    partie->afficherCarteReserve();
    partie->afficherCartePosseder();
    partie->afficherPlateauetPyramide(plateauWidget,pyramide);


    if(game->joueur_actif()==1)    {


        partie->joueurActif(partie->getPlayer1());

    }
    else {

        partie->joueurActif(partie->getPlayer2());
    }

    partie->setPlateauWidget(plateauWidget);
    partie->setPyramideWidget(pyramide);

    // Show the widget
    partie->show();
    close();

}



void MenuWindow::onButton2Clicked() {
    Partie * game = Partie::get_partie();

    // Create and add the PlateauWidget to the layout
    PlateauWidget * plateauWidget = PlateauWidget::getInstance();

    plateauWidget = PlateauWidget::creerPlateau();
    PartieWidget * partie = PartieWidget::getInstance();
    //partie->displayRoyalImages(imagePaths);
    partie->afficherPlateau(plateauWidget);
    partie->joueurActif("Joueur 1");
    QString backgroundImagePath = ":/Images/splender_background.jpg";

    // Appliquer l'image de fond à PartieWidget
    partie->setStyleSheet("background-image: url('" + backgroundImagePath + "'); background-repeat: no-repeat; background-position: center;");


    partie->setPlateauWidget(plateauWidget);

    // Show the widget
    partie->show();
    close();
}

void MenuWindow::onButton3Clicked() {
    close();

}

void MenuWindow::onButton4Clicked() {
    PageRegles *pageRegles = new PageRegles;
    pageRegles->setAttribute(Qt::WA_DeleteOnClose);

    // Récupérer la géométrie de l'écran principal
    QRect screenGeometry = QApplication::primaryScreen()->geometry();

    // Définir la géométrie de la fenêtre des règles pour la centrer
    int width = 800; // Ajustez la largeur selon vos besoins
    int height = 600; // Ajustez la hauteur selon vos besoins

    int x = (screenGeometry.width() - width) / 2;
    int y = (screenGeometry.height() - height) / 2;

    pageRegles->setGeometry(x, y, width, height);
    pageRegles->show();
}

