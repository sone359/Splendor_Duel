// PartieWidget.cpp
#include "PartieWidget.h"

PartieWidget *PartieWidget::instance = nullptr;

PartieWidget::PartieWidget(QWidget *parent) : QWidget(parent) {
    mainLayout = new QVBoxLayout(this);

    QStringList imagePaths = {
        "D:/Qt_project/sans_titre/Images/Cartes_royales/CartesRoyales_voler.png",
        "D:/Qt_project/sans_titre/Images/Cartes_royales/CartesRoyales_rejouer.png",
        "D:/Qt_project/sans_titre/Images/Cartes_royales/CartesRoyales_sans.png",
        "D:/Qt_project/sans_titre/Images/Cartes_royales/CartesRoyales_privilege.png"
    };

    displayRoyalImages(imagePaths);

    boutonManager.addButtonsToLayout(mainLayout);


}

PartieWidget *PartieWidget::getInstance() {
    if (!instance) {
        instance = new PartieWidget();
    }
    return instance;
}

void PartieWidget::displayRoyalImages(const QStringList &imagePaths) {
    QHBoxLayout *imageRowLayout = new QHBoxLayout;

    for (const QString &imagePath : imagePaths) {
        // Load and display each image
        QLabel *label = new QLabel;
        QPixmap pixmap(imagePath);
        pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio);
        label->setPixmap(pixmap);
        imageRowLayout->addWidget(label);

        // Add a spacing of 3 pixels after each image
        imageRowLayout->addSpacing(3); // Vous avez probablement voulu utiliser 3 pixels ici
    }

    // Add the QHBoxLayout to the QVBoxLayout (mainLayout)
    mainLayout->addLayout(imageRowLayout);
}

void PartieWidget::afficherPlateau(PlateauWidget * pl) {
mainLayout->addWidget(pl);
}
void PartieWidget::remove(PlateauWidget * pl)
{
    //PlateauWidget * plateauWidget = PlateauWidget::getInstance();
    mainLayout->removeWidget(pl);
}
