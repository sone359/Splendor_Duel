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
    Partie * game = Partie::get_partie();
    boutonManager.addButtonsToLayout(mainLayout);
    //QMessageBox::information(this, "Info", "Player 1: " + Player1 );
    player1Label = new QLabel(Player1, this);
    player1RedLineEdit = new QLineEdit(this);
    player1RedLineEdit->setText(QString::number(game->get_joueur(1).getGemmes().get_Rouge()));
    player1RedLineEdit->setReadOnly(true);
    player1GreenLineEdit = new QLineEdit(this);
    player1GreenLineEdit->setText(QString::number(game->get_joueur(1).getGemmes().get_Vert()));
    player1GreenLineEdit->setReadOnly(true);
    player1BlueLineEdit = new QLineEdit(this);
    player1BlueLineEdit->setText(QString::number(game->get_joueur(1).getGemmes().get_Bleu()));
    player1BlueLineEdit->setReadOnly(true);
    player1WhiteLineEdit = new QLineEdit(this);
    player1WhiteLineEdit->setText(QString::number(game->get_joueur(1).getGemmes().get_Blanc()));
    player1WhiteLineEdit->setReadOnly(true);
    player1PearlLineEdit = new QLineEdit(this);
    player1PearlLineEdit->setText(QString::number(game->get_joueur(1).getGemmes().get_Perle()));
    player1PearlLineEdit->setReadOnly(true);
    player1BlackLineEdit = new QLineEdit(this);
    player1BlackLineEdit->setText(QString::number(game->get_joueur(1).getGemmes().get_Noir()));
    player1BlackLineEdit->setReadOnly(true);
    player1PrivilegeLineEdit = new QLineEdit(this);
    player1PrivilegeLineEdit->setText(QString::number(game->get_joueur(1).getNbPrivileges()));
    player1PrivilegeLineEdit->setReadOnly(true);
    player1GoldLineEdit = new QLineEdit(this);
    player1GoldLineEdit->setText(QString::number(game->get_joueur(1).getGemmes().get_Or()));
    player1GoldLineEdit->setReadOnly(true);
    player1CoronneLineEdit = new QLineEdit(this);
    player1CoronneLineEdit->setText(QString::number(game->get_joueur(1).getNbCouronnes()));
    player1CoronneLineEdit->setReadOnly(true);



    setupPlayerWidgets(player1Label, player1RedLineEdit, player1GreenLineEdit,
                       player1BlueLineEdit, player1WhiteLineEdit, player1PearlLineEdit,
                       player1BlackLineEdit, player1PrivilegeLineEdit,player1GoldLineEdit,player1CoronneLineEdit);

    // Player 2
    player2Label = new QLabel(Player2, this);
    player2RedLineEdit = new QLineEdit(this);
    player2RedLineEdit->setText(QString::number(game->get_joueur(2).getGemmes().get_Rouge()));
    player2RedLineEdit->setReadOnly(true);
    player2GreenLineEdit = new QLineEdit(this);
    player2GreenLineEdit->setText(QString::number(game->get_joueur(2).getGemmes().get_Vert()));
    player2GreenLineEdit->setReadOnly(true);
    player2BlueLineEdit = new QLineEdit(this);
    player2BlueLineEdit->setText(QString::number(game->get_joueur(2).getGemmes().get_Bleu()));
    player2BlueLineEdit->setReadOnly(true);
    player2WhiteLineEdit = new QLineEdit(this);
    player2WhiteLineEdit->setText(QString::number(game->get_joueur(2).getGemmes().get_Blanc()));
    player2WhiteLineEdit->setReadOnly(true);
    player2PearlLineEdit = new QLineEdit(this);
    player2PearlLineEdit->setText(QString::number(game->get_joueur(2).getGemmes().get_Perle()));
    player2PearlLineEdit->setReadOnly(true);
    player2BlackLineEdit = new QLineEdit(this);
    player2BlackLineEdit->setText(QString::number(game->get_joueur(2).getGemmes().get_Noir()));
    player2BlackLineEdit->setReadOnly(true);
    player2PrivilegeLineEdit = new QLineEdit(this);
    player2PrivilegeLineEdit->setText(QString::number(game->get_joueur(2).getNbPrivileges()));
    player2PrivilegeLineEdit->setReadOnly(true);
    player2GoldLineEdit = new QLineEdit(this);
    player2GoldLineEdit->setText(QString::number(game->get_joueur(2).getGemmes().get_Or()));
    player2GoldLineEdit->setReadOnly(true);
    player2CoronneLineEdit = new QLineEdit(this);
    player2CoronneLineEdit->setText(QString::number(game->get_joueur(2).getNbCouronnes()));
    player2CoronneLineEdit->setReadOnly(true);

    setupPlayerWidgets(player2Label, player2RedLineEdit, player2GreenLineEdit,
                       player2BlueLineEdit, player2WhiteLineEdit, player2PearlLineEdit,
                       player2BlackLineEdit, player2PrivilegeLineEdit,player2GoldLineEdit,player2CoronneLineEdit);

    CarteRoyale carte1(2, Effet::voler, ":/Images/Cartes_royales/CartesRoyales_voler.png");
    CarteRoyale carte2(2, Effet::rejouer, ":/Images/Cartes_royales/CartesRoyales_rejouer.png");
    CarteRoyale carte3(3, Effet::sans, ":/Images/Cartes_royales/CartesRoyales_sans.png");
    CarteRoyale carte4(2, Effet::privilege, ":/Images/Cartes_royales/CartesRoyales_privilege.png");



    // Add the CarteRoyale objects to the cartesRoyales attribute
    cartesRoyales.push_back(carte1);
    cartesRoyales.push_back(carte2);
    cartesRoyales.push_back(carte3);
    cartesRoyales.push_back(carte4);


}





void PartieWidget::updatePlayerInfo(const QString& playerName, int redValue, int greenValue, int blueValue, int whiteValue, int pearlValue, int blackValue,int goldvalue) {
    if (playerName == Player1) {
        player1RedLineEdit->setText(QString::number(redValue));
        player1GreenLineEdit->setText(QString::number(greenValue));
        player1BlueLineEdit->setText(QString::number(blueValue));
        player1WhiteLineEdit->setText(QString::number(whiteValue));
        player1PearlLineEdit->setText(QString::number(pearlValue));
        player1BlackLineEdit->setText(QString::number(blackValue));
        player1GoldLineEdit->setText(QString::number(goldvalue));
    } else if (playerName == Player2) {
        player2RedLineEdit->setText(QString::number(redValue));
        player2GreenLineEdit->setText(QString::number(greenValue));
        player2BlueLineEdit->setText(QString::number(blueValue));
        player2WhiteLineEdit->setText(QString::number(whiteValue));
        player2PearlLineEdit->setText(QString::number(pearlValue));
        player2BlackLineEdit->setText(QString::number(blackValue));
        player2GoldLineEdit->setText(QString::number(goldvalue));
    }
}

void PartieWidget::setLabel(const QString & player1,const QString & player2)
{
    player1Label->setText(player1);
    player2Label->setText(player2);

}

void setSmallImageBackground(QLabel* label, const QString& imagePath) {
    QPixmap pixmap(imagePath);

    pixmap = pixmap.scaled(QSize(20, 20),Qt::IgnoreAspectRatio);

    label->setPixmap(pixmap);
    label->setFixedSize(pixmap.size());
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    label->setAutoFillBackground(true);
    label->setPalette(palette);
}


// PartieWidget.cpp
void decorateLineEdits(QLabel*& label,QLineEdit* redLineEdit, QLineEdit* greenLineEdit,
                       QLineEdit* blueLineEdit, QLineEdit* whiteLineEdit,
                       QLineEdit* pearlLineEdit, QLineEdit* blackLineEdit,
                       QLineEdit* privilegeLineEdit, QLineEdit* goldLineEdit , QLineEdit  * CoronneLineEdit) {
    QString styleSheet = "QLineEdit {"
                         "   border: 2px solid #cccccc;"
                         "   border-radius: 5px;"
                         "   background-color: #f2f2f2;"
                         "   padding: 1px;"
                         "}";

    QString labelStyleSheet = "QLabel {"
                              "   border: 2px solid #cccccc;"
                              "   border-radius: 5px;"
                              "   background-color: #f2f2f2;"
                              "   padding: 3px;"
                              "}";

    label->setStyleSheet(labelStyleSheet);


    redLineEdit->setStyleSheet(styleSheet);
    greenLineEdit->setStyleSheet(styleSheet);
    blueLineEdit->setStyleSheet(styleSheet);
    whiteLineEdit->setStyleSheet(styleSheet);
    pearlLineEdit->setStyleSheet(styleSheet);
    blackLineEdit->setStyleSheet(styleSheet);
    privilegeLineEdit->setStyleSheet(styleSheet);
    CoronneLineEdit->setStyleSheet(styleSheet);
    goldLineEdit->setStyleSheet(styleSheet);

}
void PartieWidget::setupPlayerWidgets(QLabel*& label, QLineEdit*& redLineEdit, QLineEdit*& greenLineEdit,
                                      QLineEdit*& blueLineEdit, QLineEdit*& whiteLineEdit,
                                      QLineEdit*& pearlLineEdit, QLineEdit*& blackLineEdit,
                                      QLineEdit*& privilegeLineEdit,QLineEdit *& GoldLineEdit,QLineEdit *& CoronneLineEdit) {
    QGridLayout *playerLayout = new QGridLayout;

    decorateLineEdits(label, redLineEdit,  greenLineEdit,
                       blueLineEdit,  whiteLineEdit,
                       pearlLineEdit,  blackLineEdit,
                       privilegeLineEdit, GoldLineEdit,CoronneLineEdit);

    // Add widgets to the layout
    playerLayout->addWidget(label, 0, 0, 1, 1);
    QLabel* smallImageLabel = new QLabel;

    setSmallImageBackground(smallImageLabel, ":/Images/Jetons/jeton_rouge.png");

    playerLayout->addWidget(smallImageLabel, 0, 1);
    playerLayout->addWidget(redLineEdit, 0, 2);
    QLabel* smallImageLabel1 = new QLabel;
    setSmallImageBackground(smallImageLabel1, ":/Images/Jetons/jeton_vert.png");
    playerLayout->addWidget(smallImageLabel1, 0, 3);
    playerLayout->addWidget(greenLineEdit, 0, 4);
    QLabel* smallImageLabel2 = new QLabel;
    setSmallImageBackground(smallImageLabel2, ":/Images/Jetons/jeton_bleu.png");
    playerLayout->addWidget(smallImageLabel2, 0, 5);
    playerLayout->addWidget(blueLineEdit, 0, 6);
    QLabel* smallImageLabel3 = new QLabel;
    setSmallImageBackground(smallImageLabel3, ":/Images/Jetons/jeton_blanc.png");
    playerLayout->addWidget(smallImageLabel3, 0, 7);
    playerLayout->addWidget(whiteLineEdit, 0, 8);
    QLabel* smallImageLabel4 = new QLabel;
    setSmallImageBackground(smallImageLabel4, ":/Images/Jetons/jeton_perle.png");
    playerLayout->addWidget(smallImageLabel4, 0, 9);
    playerLayout->addWidget(pearlLineEdit, 0, 10);
    QLabel* smallImageLabel5 = new QLabel;
    setSmallImageBackground(smallImageLabel5, ":/Images/noir.png");
    playerLayout->addWidget(smallImageLabel5, 0, 11);
    playerLayout->addWidget(blackLineEdit, 0, 12);
    QLabel* smallImageLabel7 = new QLabel;
    setSmallImageBackground(smallImageLabel7, ":/Images/privilege.png");
    playerLayout->addWidget(smallImageLabel7, 0, 13);
    playerLayout->addWidget(privilegeLineEdit, 0, 14);
    QLabel* smallImageLabel6 = new QLabel;
    setSmallImageBackground(smallImageLabel6, ":/Images/Jetons/jeton_or.png");
    playerLayout->addWidget(smallImageLabel6, 0, 15);
    playerLayout->addWidget(GoldLineEdit, 0, 16);
    QLabel* smallImageLabel8 = new QLabel;
    setSmallImageBackground(smallImageLabel8, ":/Images/coronne.png");
    playerLayout->addWidget(smallImageLabel8, 0, 17);
    playerLayout->addWidget(CoronneLineEdit, 0, 18);

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

    for (int i = 0; i < imagePaths.size(); ++i) {
        // Create a QPushButton with the image as its background
        QPushButton *button = new QPushButton;
        QPixmap pixmap(imagePaths[i]);
        pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio);
        button->setIcon(QIcon(pixmap));
        button->setIconSize(pixmap.size());
        button->setFixedSize(69, 100); // Set the size of the button

        // Add a spacing of 3 pixels after each button
        if (i > 0) {
            imageRowLayout->addSpacing(3);
        }

        // Add the button to the layout
        imageRowLayout->addWidget(button);
        royalButtons.append(button);

        // Connect the button click event to a slot that handles the click
        connect(button, &QPushButton::clicked, [this, i, imagePaths]() {
            handleRoyalButtonClick(imagePaths[i]);
        });
    }

    // Add the QHBoxLayout to the QVBoxLayout (mainLayout)
    mainLayout->addLayout(imageRowLayout);
}

void PartieWidget::removeRoyalButton(int buttonIndex) {
    if (buttonIndex >= 0 && buttonIndex < royalButtons.size()) {
        // Remove the button from layout and delete it
        mainLayout->removeWidget(royalButtons[buttonIndex]);
        delete royalButtons[buttonIndex];

    } else {
        qDebug() << "Invalid button index";
    }
}





void PartieWidget::handleRoyalButtonClick(const QString &imagePath) {
    // Check if the buttonIndex is within the valid range

    for (int i = 0; i < cartesRoyales.size(); ++i) {
        if (QString::fromStdString(cartesRoyales[i].getCheminImage()) == imagePath)
         {
            Partie * game = Partie::get_partie();
            CarteRoyale & clickedCarte = cartesRoyales[i];
            // You can use the information as needed

            Joueur & joueur = game->get_joueur(game->joueur_actif());

            if (game->get_cartes_royales().size() > 0 && (joueur.getNbCouronnes() >= 3 && joueur.getCartesRoyalesPossedees().size() == 0) && (joueur.getNbCouronnes() >= 6 && joueur.getCartesRoyalesPossedees().size() <= 1))

            {
            joueur.addCartesRoyalesPossedees(clickedCarte);
            joueur.addPointsPrestiges(clickedCarte.getPointsPrestige());
            removeRoyalButton(i);
            boutonManager.gestionEffetRoyale(clickedCarte);



            }
            else
            {
           QMessageBox::information(this, "Exception", "Tu n'a pas assez de coronne . Désolé");


        }
    }

}
}

void colorerLabel(QLabel* label, const QString& couleur) {

    QString labelStyleSheet = "QLabel {"
                              "   border: 2px solid #cccccc;"
                              "   border-radius: 5px;"
                              "   background-color:"+ couleur+ " ;"
                              "   padding: 3px;"
                              "}";

    label->setStyleSheet(labelStyleSheet);

}

void PartieWidget::joueurActif(const QString& playerName) {
    if (playerName == Player1) {

        colorerLabel(player1Label, "green");
        colorerLabel(player2Label, "");  // Réinitialiser le fond de l'autre label
    } else if (playerName == Player2) {
        colorerLabel(player1Label, "");  // Réinitialiser le fond de l'autre label
        colorerLabel(player2Label, "green");
    }
    // Ajoutez d'autres conditions au besoin
}


void PartieWidget::afficherPlateau(PlateauWidget * pl) {

mainLayout->addWidget(pl);

}

void PartieWidget::displayPyramide(pyramidefront* pyramide){
mainLayout->addWidget(pyramide);
}





void PartieWidget::updatePlayerPrivilege(const QString& playerName,int privilegeValue){
     if (playerName == Player1) {
        player1PrivilegeLineEdit->setText(QString::number(privilegeValue));
        }
     else if(playerName == Player2)
     {
        player2PrivilegeLineEdit->setText(QString::number(privilegeValue));

}

}

void PartieWidget::updatePlayerCoronne(const QString& playerName,int coronneValue)
{
if (playerName == Player1) {
        player1CoronneLineEdit->setText(QString::number(coronneValue));
}
else if(playerName == Player2)
{
        player2CoronneLineEdit->setText(QString::number(coronneValue));

}
}

void PartieWidget::removePlateau(PlateauWidget * pl)
{
   if(pl)
{
    mainLayout->removeWidget(pl);
        std::cout<<"PlateauTrouve";

    // Remove the widget from the layout, but don't delete it yet
    pl->setParent(nullptr);

    // Delete the widget

   }
}
