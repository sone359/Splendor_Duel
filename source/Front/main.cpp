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

#include "../Back/partie.h"
#include "../Back/plateau.h"
#include "../Back/sac.h"
#include "../Back/pyramide.h"



int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MenuWindow mainWindow; // Instanciez MainWindow au lieu de Plateau
    mainWindow.show();


return a.exec();

}
