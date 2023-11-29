#include    <QApplication>
#include <QApplication>
#include <iostream>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include "../Back/CarteRoyale.h"
#include "Effet.h"
#include <QWidget>
#include <QPixmap>
#include <QHBoxLayout>
#include "PlateauWidget.h"
#include "BoutonManager.h"
#include "PartieWidget.h"
#include "../Back/partie.h"

#include "../Back/plateau.h"
#include "../Back/sac.h"

void displayRoyalImages(QWidget *widget, const QStringList &imagePaths) {
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);

    // Create a QHBoxLayout for the row
    QHBoxLayout *imageRowLayout = new QHBoxLayout;

    for (const QString &imagePath : imagePaths) {
        // Load and display each image
        QLabel *label = new QLabel;
        QPixmap pixmap(imagePath);
        pixmap = pixmap.scaled(100,100, Qt::KeepAspectRatio);
        label->setPixmap(pixmap);
        imageRowLayout->addWidget(label);

        // Add a spacing of 3 pixels after each image
        imageRowLayout->addSpacing(1);
    }

    // Add the QHBoxLayout to the QVBoxLayout
    mainLayout->addLayout(imageRowLayout);

    widget->show();
}
/*
void displayJetons(QWidget *widget, const QStringList &jetonImagePaths) {
    // Create a QHBoxLayout for the jetons row
    QHBoxLayout *jetonRowLayout = new QHBoxLayout;

    for (const QString &imagePath : jetonImagePaths) {
        // Load and display each jeton
        QLabel *label = new QLabel;
        QPixmap pixmap(imagePath);
        // Resize the image to the specified size
        pixmap = pixmap.scaled(100,100, Qt::KeepAspectRatio);
        label->setPixmap(pixmap);
        jetonRowLayout->addWidget(label);

        // Add a spacing of 3 pixels after each jeton
        jetonRowLayout->addSpacing(3);
    }

    // Add the jetons QHBoxLayout to the existing QVBoxLayout
    QVBoxLayout *mainLayout = dynamic_cast<QVBoxLayout *>(widget->layout());
    if (mainLayout) {
        mainLayout->addLayout(jetonRowLayout);
    }
}
*/
int main(int argc, char *argv[]) {

    Plateau& pl = Plateau::get_plateau();
    Sac& sac = Sac::get_sac();

    QApplication app(argc, argv);




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

    pl.ajouterJeton(sac.retirer_jeton());
    pl.ajouterJeton(sac.retirer_jeton());
    pl.ajouterJeton(sac.retirer_jeton());
    pl.ajouterJeton(sac.retirer_jeton());
    pl.ajouterJeton(sac.retirer_jeton());
    pl.ajouterJeton(sac.retirer_jeton());
    pl.ajouterJeton(sac.retirer_jeton());
    // Example 1
    CarteRoyale carte1(2, Effet::voler, "Images/Cartes_royales/CartesRoyales_voler.png");
    std::cout << "Carte 1 - Points Prestige: " << carte1.getPointsPrestige() << std::endl;
    std::cout << "Carte 1 - Capacite: " << static_cast<int>(carte1.getCapacite()) << std::endl;
    std::cout << "Carte 1 - Chemin Image: " << carte1.getCheminImage() << std::endl;

    // Example 2
    CarteRoyale carte2(2, Effet::privilege, "Images/Cartes_royales/CartesRoyales_privilege.png");
    std::cout << "Carte 2 - Points Prestige: " << carte2.getPointsPrestige() << std::endl;
    std::cout << "Carte 2 - Capacite: " << static_cast<int>(carte2.getCapacite()) << std::endl;
    std::cout << "Carte 2 - Chemin Image: " << carte2.getCheminImage() << std::endl;

    // Example 3
    CarteRoyale carte3(2, Effet::rejouer, "Images/Cartes_royales/CartesRoyales_rejouer.png");
    std::cout << "Carte 3 - Points Prestige: " << carte3.getPointsPrestige() << std::endl;
    std::cout << "Carte 3 - Capacite: " << static_cast<int>(carte3.getCapacite()) << std::endl;
    std::cout << "Carte 3 - Chemin Image: " << carte3.getCheminImage() << std::endl;

    // Example 4
    CarteRoyale carte4(3,Effet::sans, "Images/Cartes_royales/CartesRoyales_sans.png");
    std::cout << "Carte 4 - Points Prestige: " << carte4.getPointsPrestige() << std::endl;
    std::cout << "Carte 4 - Capacite: " << static_cast<int>(carte4.getCapacite()) << std::endl;
    std::cout << "Carte 4 - Chemin Image: " << carte4.getCheminImage() << std::endl;

    QWidget *widget = new QWidget;

    // List of image paths
    QStringList imagePaths = {
        "D:/Qt_project/sans_titre/Images/Cartes_royales/CartesRoyales_voler.png",
        "D:/Qt_project/sans_titre/Images/Cartes_royales/CartesRoyales_rejouer.png",
        "D:/Qt_project/sans_titre/Images/Cartes_royales/CartesRoyales_sans.png",
        "D:/Qt_project/sans_titre/Images/Cartes_royales/CartesRoyales_privilege.png"
    };

    // List of paths for Jetons
    /*
    QStringList jetonImagePaths = {
        "D:/Qt_project/sans_titre/Images/Jetons/jeton_bleu.png",
        "D:/Qt_project/sans_titre/Images/Jetons/jeton_noir.png",
        "D:/Qt_project/sans_titre/Images/Jetons/jeton_or.png",
        "D:/Qt_project/sans_titre/Images/Jetons/jeton_perle.png",
        "D:/Qt_project/sans_titre/Images/Jetons/jeton_rouge.png",
        "D:/Qt_project/sans_titre/Images/Jetons/jeton_vert.png"
    };
*/
    // Call the function to display images
    //displayRoyalImages(widget, imagePaths);
    // Call the function to display Jetons
    //displayJetons(widget, jetonImagePaths);

//    // Create BoutonManager and add buttons to layout
//    BoutonManager boutonManager(widget);
//    // Utiliser qobject_cast pour convertir le QLayout* en QVBoxLayout*
//    QVBoxLayout* mainLayout = qobject_cast<QVBoxLayout*>(widget->layout());
//    if (mainLayout) {
//        boutonManager.addButtonsToLayout(mainLayout);
//    } else {
//        // Gérer le cas où le layout n'est pas QVBoxLayout
//        qWarning("Le layout du widget n'est pas QVBoxLayout.");
//    }

    Partie& game = Partie::get_partie();

    // Create and add the PlateauWidget to the layout
    PlateauWidget * plateauWidget = PlateauWidget::getInstance();
    // Display some cases on the plateau
//    plateauWidget->displayCase("D:/Qt_project/sans_titre/Images/Jetons/jeton_bleu.png", {0, 0});
//    plateauWidget->displayCase("D:/Qt_project/sans_titre/Images/Jetons/jeton_rouge.png", {1, 1});
//    plateauWidget->displayCase("D:/Qt_project/sans_titre/Images/Jetons/jeton_vert.png", {2, 2});
//    plateauWidget->displayCase("D:/Qt_project/sans_titre/Images/Jetons/jeton_or.png", {2, 3});
//    plateauWidget->displayCase("D:/Qt_project/sans_titre/Images/Jetons/jeton_noir.png", {3, 3});
//    plateauWidget=plateauWidget->creerPlateau(plateauWidget);
//    mainLayout->addWidget(plateauWidget);
    plateauWidget = PlateauWidget::creerPlateau();
    PartieWidget * partie = PartieWidget::getInstance();
    //partie->displayRoyalImages(imagePaths);
    partie->afficherPlateau(plateauWidget);

    partie->setPlateauWidget(plateauWidget);

    // Show the widget
    partie->show();

/*
    QApplication app(argc, argv);
    QWidget *widget = new QWidget;
    QLabel *label = new QLabel;

    QPixmap *pixmap_img = new QPixmap("D:/Qt_project/sans_titre/Images/Cartes_royales/CartesRoyales_voler.png");
    label->setPixmap(*pixmap_img);

    QGridLayout *gridLayout = new QGridLayout(widget);
    gridLayout->addWidget(label, 0, 0);
    widget->setLayout(gridLayout);

    widget->setFixedSize(pixmap_img->size()); // Set a fixed size for the widget

    widget->show();

   // QPushButton button("Quitter");
   //  button.show();
*/
    return app.exec();
}
