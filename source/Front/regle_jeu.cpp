#include "regle_jeu.h"

PageRegles::PageRegles(QWidget *parent)
    : QWidget(parent),
    scrollArea(new QScrollArea(this)),
    scrollWidget(new QWidget(this)),
    scrollLayout(new QHBoxLayout(scrollWidget))
{
    // Ajouter le widget à la zone de défilement
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollWidget);

    // Ajouter la zone de défilement à la mise en page principale
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);

    // Charger les images dans la liste
    setupImages();
    setWindowTitle("Page des Règles");
}

PageRegles::~PageRegles()
{
}

void PageRegles::setupImages()
{
    // Ajouter les chemins de vos images à la liste
    imageList << QPixmap(":/Images/regle1.jpg")
              << QPixmap(":/Images/regle2.jpg")
              << QPixmap(":/Images/regle3.jpg");

    // Taille fixe pour toutes les images
    QSize fixedSize(1080, 768);
    QVBoxLayout *scrollLayoutVertical = new QVBoxLayout(scrollWidget);

    // Créer des QLabel pour chaque image et les ajouter à la mise en page
    for (const QPixmap &pixmap : imageList) {
        QLabel *label = new QLabel(this);
        label->setPixmap(pixmap.scaled(fixedSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        label->setScaledContents(true);

        imageLabels.append(label);
        scrollLayout->addWidget(label);
    }
}
