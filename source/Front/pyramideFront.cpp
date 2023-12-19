#include "pyramideFront.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPixmap>
#include <QImage>
#include "../Back/partie.h"

pyramidefront::pyramidefront(QWidget *parent) : QWidget(parent)
{
    Partie * partie = Partie::get_partie();

    const int espaceEntreCases = 2;

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QVector<QHBoxLayout*> niveauLayouts;

    // Niveau 1
    QHBoxLayout *gridLayoutniv1 = new QHBoxLayout;

    for (int row = 0; row < 3; ++row) {
      CarteJoaillerie cartejoaillerie3 = partie->get_pyramide().recupererCarteJoaillerie(3, row);
      std::string cheminBase3 = "D:\\LO21\\lo21_splendor-main\\data\\cartesplendor(niveau_3)\\";
      std::string cheminImage3 = cheminBase3 + cartejoaillerie3.getChemin() +".jpg";
      // Convertir la std::string en QString
      QString cheminImageQString = QString::fromStdString(cheminImage3);

      // Charger l'image avec QPixmap
      QPixmap image = QPixmap::fromImage(QImage(cheminImageQString));
      QPushButton *carte = new QPushButton;
      carte->setIcon(QIcon(image));
      carte->setIconSize(image.size());
      carte->setFixedSize(image.size());
      gridLayoutniv1->addWidget(carte);
      connect(carte, &QPushButton::clicked, [=]() {
        // partie.getinfo carte(joueur, niv, colonne); // Ajoutez vos paramètres
        // appropriés
      });

    }
    niveauLayouts.append(gridLayoutniv1);

    // Niveau 2
    QHBoxLayout *gridLayoutniv2 = new QHBoxLayout;
    for (int row = 0; row < 4; ++row) {
      CarteJoaillerie cartejoaillerie2 = partie->get_pyramide().recupererCarteJoaillerie(3, row);
      std::string cheminBase2 = "D:\\LO21\\lo21_splendor-main\\data\\cartesplendor(niveau_2)/";
      std::string cheminImage2 = cheminBase2 + cartejoaillerie2.getChemin() +".jpg";
      // Convertir la std::string en QString
      QString cheminImageQString = QString::fromStdString(cheminImage2);

      // Charger l'image avec QPixmap
      QPixmap image = QPixmap::fromImage(QImage(cheminImageQString));
      QPushButton *carte = new QPushButton;
      carte->setIcon(QIcon(image));
      carte->setIconSize(image.size());
      carte->setFixedSize(image.size());
      gridLayoutniv1->addWidget(carte);
      connect(carte, &QPushButton::clicked, [=]() {
          // partie.getinfo carte(joueur, niv, colonne); // Ajoutez vos paramètres
          // appropriés
      });
    }
    niveauLayouts.append(gridLayoutniv2);

    // Niveau 3
    QHBoxLayout *gridLayoutniv3 = new QHBoxLayout;

    for (int row = 0; row < 5; ++row){
    CarteJoaillerie cartejoaillerie1 = partie->get_pyramide().recupererCarteJoaillerie(3, row);
    std::string cheminBase1 = "D:\\LO21\\lo21_splendor-main\\data\\cartesplendor(niveau_3)/";
    std::string cheminImage1 = cheminBase1 + cartejoaillerie1.getChemin() +".jpg";
    qDebug() << "Chemin de l'image : " << QString::fromStdString(cheminImage1);

    // Convertir la std::string en QString
    QString cheminImageQString = QString::fromStdString(cheminImage1);

    // Charger l'image avec QPixmap
    QPixmap image = QPixmap::fromImage(QImage(cheminImageQString));
    QPushButton *carte = new QPushButton;
    carte->setIcon(QIcon(image));
    carte->setIconSize(image.size());
    carte->setFixedSize(image.size());
    gridLayoutniv1->addWidget(carte);
    connect(carte, &QPushButton::clicked, [=]() {
        // partie.getinfo carte(joueur, niv, colonne); // Ajoutez vos paramètres
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

    setLayout(mainLayout);

    };

pyramidefront::~pyramidefront(){

};
