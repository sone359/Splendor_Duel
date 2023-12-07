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
#include "../Back/pyramide.h"

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

int main(int argc, char *argv[]) {


    QApplication app(argc, argv);




    Partie& game = Partie::get_partie();

//    game.lire_fichier(":/../../data/info_cartejoaillerie");

//    Pyramide::initialiser(cartes);
//    pyramide = Pyramide::getInstance();

    // Create and add the PlateauWidget to the layout
    PlateauWidget * plateauWidget = PlateauWidget::getInstance();

    plateauWidget = PlateauWidget::creerPlateau();
    PartieWidget * partie = PartieWidget::getInstance();
    //partie->displayRoyalImages(imagePaths);
    partie->afficherPlateau(plateauWidget);
    partie->joueurActif("Joueur 1");

    partie->setPlateauWidget(plateauWidget);

    // Show the widget
    partie->show();
    return app.exec();
}
