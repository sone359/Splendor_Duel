#include "pyramideFront.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPixmap>
#include <QImage>
#include "../Back/partie.h"

pyramidefront* pyramidefront::instance = nullptr;



pyramidefront::pyramidefront(QWidget *parent) : QWidget(parent){

};

pyramidefront * pyramidefront::getInstance() {
    if (!instance) {
        // Create the instance if it doesn't exist
        instance = new pyramidefront;
    }
    return instance;
}

//QVBoxLayout* pyramidefront::get_mainLayout(){return mainLayout;}

pyramidefront* pyramidefront::creerPyramide(){
    instance=nullptr;
    pyramidefront *pyr = pyramidefront::getInstance();
    QVBoxLayout * mainLayout = new QVBoxLayout(instance);

     mainLayout->setSpacing(2);
    Partie * partie = Partie::get_partie();

    const int espaceEntreCases = 2;

    QVector<QHBoxLayout*> niveauLayouts;

    // Niveau 1
    QHBoxLayout *gridLayoutniv1 = new QHBoxLayout;



    for (int row = 1; row <= 3; row++) {
        CarteJoaillerie cartejoaillerie3 = partie->get_pyramide().recupererCarteJoaillerie(3, row);
        std::string cheminBase3 = "../../data/cartesplendor(niveau_3)/";
        std::string cheminImage3 = cheminBase3 + cartejoaillerie3.getChemin() +".jpg";
        // Convertir la std::string en QString
        QString cheminImageQString = QString::fromStdString(cheminImage3);

        // Charger l'image avec QPixmap
        QPixmap image = QPixmap::fromImage(QImage(cheminImageQString));
        image = image.scaled(100, 100, Qt::KeepAspectRatio);
        QPushButton *carte = new QPushButton;
        carte->setIcon(QIcon(image));
        carte->setIconSize(image.size());
        carte->setFixedSize(image.size());

        gridLayoutniv1->addWidget(carte);
        connect(carte, &QPushButton::clicked, [=]() {
            // partie->getinfo carte(joueur, niv, colonne); // Ajoutez vos paramètres
            // appropriés
        });

    }
    niveauLayouts.append(gridLayoutniv1);

    // Niveau 2
    QHBoxLayout *gridLayoutniv2 = new QHBoxLayout;
    for (int row2 = 1; row2 <= 4; row2++) {
        CarteJoaillerie cartejoaillerie2 = partie->get_pyramide().recupererCarteJoaillerie(2, row2);
        std::string cheminBase2 = "../../data/cartesplendor(niveau_2)/";
        std::string cheminImage2 = cheminBase2 + cartejoaillerie2.getChemin() +".jpg";
        // Convertir la std::string en QString
        QString cheminImageQString = QString::fromStdString(cheminImage2);

        // Charger l'image avec QPixmap
        QPixmap image = QPixmap::fromImage(QImage(cheminImageQString));
        image = image.scaled(100, 100, Qt::KeepAspectRatio);
        QPushButton *carte = new QPushButton;
        carte->setIcon(QIcon(image));
        carte->setIconSize(image.size());
        carte->setFixedSize(image.size());
        gridLayoutniv2->addWidget(carte);
        connect(carte, &QPushButton::clicked, [=]() {
            // partie->getinfo carte(joueur, niv, colonne); // Ajoutez vos paramètres
            // appropriés
        });
    }
    niveauLayouts.append(gridLayoutniv2);

    // Niveau 3
    QHBoxLayout *gridLayoutniv3 = new QHBoxLayout;

    for (int row1 = 1; row1 < 6; row1++){
        CarteJoaillerie cartejoaillerie1 = partie->get_pyramide().recupererCarteJoaillerie(1, row1);
        std::string cheminBase1 = "../../data/cartesplendor(niveau_1)/";
        std::string cheminImage1 = cheminBase1 + cartejoaillerie1.getChemin() +".jpg";
        qDebug() << "Chemin de l'image : " << QString::fromStdString(cheminImage1);

        // Convertir la std::string en QString
        QString cheminImageQString = QString::fromStdString(cheminImage1);

        // Charger l'image avec QPixmap
        QPixmap image = QPixmap::fromImage(QImage(cheminImageQString));
        image = image.scaled(100, 100, Qt::KeepAspectRatio);
        QPushButton *carte = new QPushButton;
        carte->setIcon(QIcon(image));
        carte->setIconSize(image.size());
        carte->setFixedSize(image.size());
        gridLayoutniv3->addWidget(carte);
        connect(carte, &QPushButton::clicked, [=]() {
            // partie->getinfo carte(joueur, niv, colonne); // Ajoutez vos paramètres
            // appropriés
        });
    }
    niveauLayouts.append(gridLayoutniv3);
    // Ajouter les layouts des niveaux au layout principal
    for (QHBoxLayout *niveauLayout : niveauLayouts) {
        niveauLayout->setSpacing(espaceEntreCases);
        mainLayout->addLayout(niveauLayout);
    }

    // Ajouter un espace en haut
    mainLayout->addStretch();
    return pyr;
}



