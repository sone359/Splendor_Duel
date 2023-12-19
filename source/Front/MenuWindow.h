#ifndef MENUWINDOW_H
#define MENUWINDOW_H
#include <QMainWindow>
#include "PlateauWidget.h"

class MenuWindow : public QMainWindow {
    Q_OBJECT

public:
    MenuWindow(QWidget *parent = nullptr);

private slots:
    void onButton1Clicked();
    void onButton2Clicked();
    void onButton3Clicked();
    void onButton4Clicked();

private:
    PlateauWidget *plateauWidget;  // Pointeur vers Plateau
};
#endif // MENUWINDOW_H
