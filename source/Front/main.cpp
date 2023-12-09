#include <QApplication>
#include <iostream>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include "Effet.h"
#include <QWidget>
#include <QPixmap>
#include <QHBoxLayout>
#include "MenuWindow.h"

/*void displayRoyalImages(QWidget *widget, const QStringList &imagePaths) {
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
}*/

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MenuWindow mainWindow; // Instanciez MainWindow au lieu de Plateau
    mainWindow.show();

    return a.exec();
}
