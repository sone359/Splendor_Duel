#ifndef BOUTONMANAGER_H
#define BOUTONMANAGER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include "../Back/plateau.h"
#include "PlateauWidget.h"
#include "../Back/partie.h"
#include "../Back/Joueur.h"
#include "QInputDialog"
#include "../Console/interfaceConsole.h"

class BoutonManager : public QObject {

public:
    BoutonManager(QWidget *parent = nullptr);
    ~BoutonManager();

    void createButtons();
    void addButtonsToLayout(QVBoxLayout *layout);



private slots:
    void onAcheterCarteClicked();
    void onReserverCarteClicked();
    void onUtiliserPrivilegeClicked();
    void onVolerDisabledClicked();
    void onPrendreJetonsClicked();
    void onRemplirPlateauClicked();

private:
    QWidget *parentWidget;
    QGridLayout *buttonsLayout ;
    QMenu *menu;
    QPushButton *acheterCarteButton = new QPushButton("Acheter une carte", parentWidget);
    QPushButton *reserverCarteButton = new QPushButton("Réserver une carte", parentWidget);
    QPushButton *utiliserPrivilegeButton = new QPushButton("Utiliser un privilège", parentWidget);
    QPushButton *volerButton = new QPushButton("Voler", parentWidget);

    QPushButton *prendreJetonsButton = new QPushButton("Prendre des Jetons", parentWidget);
    QPushButton *remplirPlateauButton = new QPushButton("Remplir le plateau", parentWidget);
    int joueur1=1;

};

#endif // BOUTONMANAGER_H
