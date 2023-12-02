#ifndef PLATEAUWIDGET_H
#define PLATEAUWIDGET_H
#include <QGraphicsView>
// PlateauWidget.h

#include <QWidget>
#include <QGridLayout>
#include <QMessageBox>
#include <iostream>


#include <QLabel>
#include <string>
#include <vector>
#include <map>
#include <QMouseEvent>
#include <../Back/plateau.h>

// Define the Case struct
struct Case {
    int row;
    int col;

    // Define the operator< for Case
    bool operator<(const Case& other) const {
        return std::tie(row, col) < std::tie(other.row, other.col);
    }
};

class PlateauWidget : public QWidget {
public:
    static PlateauWidget* getInstance();
    void displayCase(const std::string &imageName, const Case &position);
    std::map<Case, std::string> getPlateauState() const;
    std::map<Case, std::string> &getJetonsTaken() ;
    static PlateauWidget* creerPlateau();
    static PlateauWidget * instance;
    void emptyJetons();


    void handleButtonClick(const Case &position, const std::string &imageName);

private:
    PlateauWidget(QWidget *parent = nullptr);
    QGridLayout *gridLayout;
    std::map<Case, std::string> plateauState;
    std::map<Case, std::string> jetonsTaken;
};

#endif // PLATEAUWIDGET_H






