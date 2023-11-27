// PartieWidget.cpp
#include "PartieWidget.h"

PartieWidget *PartieWidget::instance = nullptr;

PartieWidget::PartieWidget(QWidget *parent) : QWidget(parent) {
    mainLayout = new QVBoxLayout(this);

    QStringList imagePaths = {
        ":/Images/Cartes_royales/CartesRoyales_voler.png",
        ":/Images/Cartes_royales/CartesRoyales_rejouer.png",
        ":/Images/Cartes_royales/CartesRoyales_sans.png",
        ":/Images/Cartes_royales/CartesRoyales_privilege.png"
    };

    displayRoyalImages(imagePaths);

    boutonManager.addButtonsToLayout(mainLayout);

    player1Label = new QLabel("Joueur 1", this);
    player1RedLineEdit = new QLineEdit(this);
    player1RedLineEdit->setText("0");
    player1RedLineEdit->setReadOnly(true);
    player1GreenLineEdit = new QLineEdit(this);
    player1GreenLineEdit->setText("0");
    player1GreenLineEdit->setReadOnly(true);
    player1BlueLineEdit = new QLineEdit(this);
    player1BlueLineEdit->setText("0");
    player1BlueLineEdit->setReadOnly(true);
    player1WhiteLineEdit = new QLineEdit(this);
    player1WhiteLineEdit->setText("0");
    player1WhiteLineEdit->setReadOnly(true);
    player1PearlLineEdit = new QLineEdit(this);
    player1PearlLineEdit->setText("0");
    player1PearlLineEdit->setReadOnly(true);
    player1BlackLineEdit = new QLineEdit(this);
    player1BlackLineEdit->setText("0");
    player1BlackLineEdit->setReadOnly(true);
    player1PrivilegeLineEdit = new QLineEdit(this);
    player1PrivilegeLineEdit->setText("0");
    player1PrivilegeLineEdit->setReadOnly(true);
    player1GoldLineEdit = new QLineEdit(this);
    player1GoldLineEdit->setText("0");
    player1GoldLineEdit->setReadOnly(true);

    setupPlayerWidgets(player1Label, player1RedLineEdit, player1GreenLineEdit,
                       player1BlueLineEdit, player1WhiteLineEdit, player1PearlLineEdit,
                       player1BlackLineEdit, player1PrivilegeLineEdit,player1GoldLineEdit);

    // Player 2
    player2Label = new QLabel("Joueur 2", this);
    player2RedLineEdit = new QLineEdit(this);
    player2RedLineEdit->setText("0");
    player2RedLineEdit->setReadOnly(true);
    player2GreenLineEdit = new QLineEdit(this);
    player2GreenLineEdit->setText("0");
    player2GreenLineEdit->setReadOnly(true);
    player2BlueLineEdit = new QLineEdit(this);
    player2BlueLineEdit->setText("0");
    player2BlueLineEdit->setReadOnly(true);
    player2WhiteLineEdit = new QLineEdit(this);
    player2WhiteLineEdit->setText("0");
    player2WhiteLineEdit->setReadOnly(true);
    player2PearlLineEdit = new QLineEdit(this);
    player2PearlLineEdit->setText("0");
    player2PearlLineEdit->setReadOnly(true);
    player2BlackLineEdit = new QLineEdit(this);
    player2BlackLineEdit->setText("0");
    player2BlackLineEdit->setReadOnly(true);
    player2PrivilegeLineEdit = new QLineEdit(this);
    player2PrivilegeLineEdit->setText("0");
    player2PrivilegeLineEdit->setReadOnly(true);
    player2GoldLineEdit = new QLineEdit(this);
    player2GoldLineEdit->setText("0");
    player2GoldLineEdit->setReadOnly(true);

    setupPlayerWidgets(player2Label, player2RedLineEdit, player2GreenLineEdit,
                       player2BlueLineEdit, player2WhiteLineEdit, player2PearlLineEdit,
                       player2BlackLineEdit, player2PrivilegeLineEdit,player2GoldLineEdit);


}

void PartieWidget::updatePlayerInfo(const QString& playerName, int redValue, int greenValue, int blueValue, int whiteValue, int pearlValue, int blackValue,int goldvalue) {
    if (playerName == "Joueur 1") {
        player1RedLineEdit->setText(QString::number(redValue));
        player1GreenLineEdit->setText(QString::number(greenValue));
        player1BlueLineEdit->setText(QString::number(blueValue));
        player1WhiteLineEdit->setText(QString::number(whiteValue));
        player1PearlLineEdit->setText(QString::number(pearlValue));
        player1BlackLineEdit->setText(QString::number(blackValue));
        player1GoldLineEdit->setText(QString::number(goldvalue));
    } else if (playerName == "Joueur 2") {
        player2RedLineEdit->setText(QString::number(redValue));
        player2GreenLineEdit->setText(QString::number(greenValue));
        player2BlueLineEdit->setText(QString::number(blueValue));
        player2WhiteLineEdit->setText(QString::number(whiteValue));
        player2PearlLineEdit->setText(QString::number(pearlValue));
        player2BlackLineEdit->setText(QString::number(blackValue));
        player2GoldLineEdit->setText(QString::number(goldvalue));
    }
}

// PartieWidget.cpp

void PartieWidget::setupPlayerWidgets(QLabel*& label, QLineEdit*& redLineEdit, QLineEdit*& greenLineEdit,
                                      QLineEdit*& blueLineEdit, QLineEdit*& whiteLineEdit,
                                      QLineEdit*& pearlLineEdit, QLineEdit*& blackLineEdit,
                                      QLineEdit*& privilegeLineEdit,QLineEdit *& GoldLineEdit) {
    QGridLayout *playerLayout = new QGridLayout;

    // Add widgets to the layout
    playerLayout->addWidget(label, 0, 0, 1, 1);
    playerLayout->addWidget(new QLabel("Rouge:"), 0, 1);
    playerLayout->addWidget(redLineEdit, 0, 2);
    playerLayout->addWidget(new QLabel("Vert:"), 0, 3);
    playerLayout->addWidget(greenLineEdit, 0, 4);
    playerLayout->addWidget(new QLabel("Bleu:"), 0, 5);
    playerLayout->addWidget(blueLineEdit, 0, 6);
    playerLayout->addWidget(new QLabel("Blanc:"), 0, 7);
    playerLayout->addWidget(whiteLineEdit, 0, 8);
    playerLayout->addWidget(new QLabel("Perle:"), 0, 9);
    playerLayout->addWidget(pearlLineEdit, 0, 10);
    playerLayout->addWidget(new QLabel("Noir:"), 0, 11);
    playerLayout->addWidget(blackLineEdit, 0, 12);
    playerLayout->addWidget(new QLabel("Privilège:"), 0, 13);
    playerLayout->addWidget(privilegeLineEdit, 0, 14);
    playerLayout->addWidget(new QLabel("Gold:"), 0, 15);
    playerLayout->addWidget(GoldLineEdit, 0, 16);

    // Add the player layout to the main layout
    mainLayout->addLayout(playerLayout);
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

//    if(getPlateauWidget())
//    mainLayout->removeWidget(getPlateauWidget());



//    mainLayout->addWidget(pl);

//    setPlateauWidget(pl);
    // Delete existing widget if it exists
//    PlateauWidget * to_remove = getPlateauWidget();
//    if(to_remove)
//    {
//        std::cout<<"plateau non vide";

//        mainLayout->removeWidget(to_remove);
//        to_remove = nullptr;
//    }
//    else         std::cout<<"plateau vide";

//    mainLayout->addWidget(pl);
//    setPlateauWidget(pl);

    // Delete the existing widget if it exists

    // Create a new widget
    QWidget * plateauWidget = new QWidget;
    // Create a new layout for the widget
    QVBoxLayout *plateauLayout = new QVBoxLayout(plateauWidget);
    plateauLayout->addWidget(pl);

    // Create a new mainLayout for PartieWidget
    mainLayout = new QVBoxLayout(this);
    // Add the new widget to the new mainLayout
    mainLayout->addWidget(plateauWidget);

    QWidget * ancien = getPlateauWidget();
    if (ancien) {
        std::cout << "Widget found. Deleting..." << std::endl;
        delete ancien;
    } else {
        std::cout << "Widget not found." << std::endl;
    }

    setPlateauWidget(plateauWidget);
    plateauWidget->show();



}

void PartieWidget::updatePlayerPrivilege(const QString& playerName,int privilegeValue){
     if (playerName == "Joueur 1") {
        player1PrivilegeLineEdit->setText(QString::number(privilegeValue));
        }
     else if(playerName == "Joueur 2")
     {
        player2PrivilegeLineEdit->setText(QString::number(privilegeValue));

}



}
void PartieWidget::remove(PlateauWidget * pl)
{
    //PlateauWidget * plateauWidget = PlateauWidget::getInstance();
    mainLayout->removeWidget(pl);
}
