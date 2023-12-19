#ifndef PARTIEWIDGET_H
#define PARTIEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QLineEdit>
#include <QStringList>
#include "PlateauWidget.h"
#include "BoutonManager.h"
#include "../Back/CarteRoyale.h"

class PartieWidget : public QWidget {
public:
    static PartieWidget *getInstance();
    void displayRoyalImages(const QStringList &imagePaths);
    void removePlateau(PlateauWidget * pl=nullptr);
    void afficherPlateau(PlateauWidget * pl);
    void setupPlayerWidgets(QLabel*& label, QLineEdit*& redLineEdit, QLineEdit*& greenLineEdit,
                                          QLineEdit*& blueLineEdit, QLineEdit*& whiteLineEdit,
                                          QLineEdit*& pearlLineEdit, QLineEdit*& blackLineEdit,
                            QLineEdit*& privilegeLineEdit,QLineEdit *& GoldLineEdit,QLineEdit *& CoronneLineEdit);
    void updatePlayerInfo(const QString& playerName, int redValue, int greenValue, int blueValue, int whiteValue, int pearlValue, int blackValue ,int goldvalue);

    void updatePlayerPrivilege(const QString& playerName,int privilegeValue);
    void updatePlayerCoronne(const QString& playerName,int coronneValue);

    PlateauWidget * getPlateauWidget() const {
        return pl;
    }

    // Setter for PlateauWidget
    void setPlateauWidget(PlateauWidget * plateauWidget) {
        pl = plateauWidget;
    }

    void removeRoyalButton(int buttonIndex);

    void joueurActif(const QString& playerName) ;

public slots:
    void handleRoyalButtonClick(const QString &imagePath);

private:
    explicit PartieWidget(QWidget *parent = nullptr);
    static PartieWidget *instance;
    PlateauWidget * pl;
    BoutonManager boutonManager;
    QVBoxLayout *mainLayout;
    // Player 1 Labels and LineEdits
    QLabel *player1Label;
    QLineEdit *player1RedLineEdit;
    QLineEdit *player1GreenLineEdit;
    QLineEdit *player1BlueLineEdit;
    QLineEdit *player1WhiteLineEdit;
    QLineEdit *player1PearlLineEdit;
    QLineEdit *player1BlackLineEdit;
    QLineEdit *player1PrivilegeLineEdit;
    QLineEdit * player1GoldLineEdit;
    QLineEdit *player1CoronneLineEdit;

    // Player 2 Labels and LineEdits
    QLabel *player2Label;
    QLineEdit *player2RedLineEdit;
    QLineEdit *player2GreenLineEdit;
    QLineEdit *player2BlueLineEdit;
    QLineEdit *player2WhiteLineEdit;
    QLineEdit *player2PearlLineEdit;
    QLineEdit *player2BlackLineEdit;
    QLineEdit *player2PrivilegeLineEdit;

    QLineEdit * player2GoldLineEdit;
    QLineEdit *player2CoronneLineEdit;



    std::vector<CarteRoyale> cartesRoyales;
    QVector<QPushButton*> royalButtons;
};
#endif // PARTIEWIDGET_H
