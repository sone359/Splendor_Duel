// PlateauWidget.cpp

#include "PlateauWidget.h"
#include <QPixmap>
#include <QPushButton>


PlateauWidget* PlateauWidget::instance = nullptr;

PlateauWidget::PlateauWidget(QWidget *parent) : QWidget(parent) {
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(2);
    setLayout(gridLayout);
}

void PlateauWidget::displayCase(const std::string &imageName, const Case &position) {
    if (imageName.empty()) {
        // If imageName is empty, just draw the border without creating a button
        QFrame* borderFrame = new QFrame;
        borderFrame->setFrameShape(QFrame::Box);
        borderFrame->setFixedSize(60, 60);
        borderFrame->setStyleSheet("border: 1px solid brown; background-color: #C4A484;");
        gridLayout->addWidget(borderFrame, position.col, position.row);
    } else {
        // If imageName is not empty, create a button with the image
        QPushButton *button = new QPushButton;

        QPixmap pixmap(imageName.c_str());
        // Resize the image to fit in the square button
        pixmap = pixmap.scaled(50, 50, Qt::KeepAspectRatio);

        // Set the background of the button to the image
        button->setIcon(QIcon(pixmap));
        button->setIconSize(pixmap.size());

        // Set the size and border of the button
        button->setFixedSize(60, 60);
        button->setStyleSheet("border: 1px solid brown; background-color: #C4A484; ");


        // Set the text of the button to be the position and the name of the image
        // Add the button to the grid layout
        gridLayout->addWidget(button, position.col, position.row);

        // Connect the button click event to handleButtonClick
        connect(button, &QPushButton::clicked, [position, imageName, this]() {
            handleButtonClick(position, imageName);
        });

        // Store the information about the displayed case
        plateauState[position] = imageName;
    }
}


void PlateauWidget::handleButtonClick(const Case &position, const std::string &imageName) {
    // Check if the JetonsTaken size is less than or equal to 3 before adding a new Jeton
    if (jetonsTaken.size() < 3) {
        // Store both the position and the name in jetonsTaken
        jetonsTaken[position] = imageName;

//        QMessageBox::information(this, "Jeton Taken", QString("Jeton Taken at (%1, %2)\nImage: %3")
//                                                          .arg(position.row).arg(position.col).arg(QString::fromStdString(imageName)));

//        // Display the contents of jetonsTaken
//        QString jetonsContents = "Jetons Taken:\n";
//        for (const auto &entry : jetonsTaken) {
//            jetonsContents += QString("(%1, %2): %3\n").arg(entry.first.row).arg(entry.first.col).arg(QString::fromStdString(entry.second));
//        }
//        QMessageBox::information(this, "Jetons Taken", jetonsContents);
    } else {
        QMessageBox::warning(this, "Limit Reached", "Cannot take more than 3 Jetons.");
    }
}

// Singleton instance retrieval function
PlateauWidget* PlateauWidget::getInstance() {
    if (!instance) {
        // Create the instance if it doesn't exist
        instance = new PlateauWidget;
    }
    return instance;
}
PlateauWidget* PlateauWidget::creerPlateau() {
    Plateau * plateau = Plateau::get_plateau();
    instance=nullptr;

    PlateauWidget * plateauWidget = PlateauWidget::getInstance();
    std::cout << "Hola 0 1 2 3 4 " << std::endl;
    for (int i = 0 ; i < 5 ; i++)
    {
        std::cout << i << " ";
        for (int j = 0 ; j < 5 ; j++)
        {
            switch ((*plateau)[j][i])
            {
            case Nul:
                std::cout << "- ";
                break;
            case Bleu:
                std::cout << "B ";
                break;
            case Vert:
                std::cout << "V ";
                break;
            case Blanc:
                std::cout << "W ";
                break;
            case Rouge:
                std::cout << "R ";
                break;
            case Noir:
                std::cout << "N ";
                break;
            case Perle:
                std::cout << "P ";
                break;
            case Or:
                std::cout << "O ";
                break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << i << " ";
        for (int j = 0; j < 5; j++) {
            switch ((*plateau)[j][i]) {
            case Nul:
                plateauWidget->displayCase("", {j, i});
                break;
            case Bleu:
                plateauWidget->displayCase(":/Images/Jetons/jeton_bleu.png", {j, i});
                std::cout << "Bleu ";
                break;
            case Vert:
                plateauWidget->displayCase(":/Images/Jetons/jeton_vert.png", {j, i});
                std::cout << "Vert ";
                break;
            case Blanc:
                plateauWidget->displayCase(":/Images/Jetons/jeton_blanc.png", {j, i});
                std::cout << "Blanc ";
                break;
            case Rouge:
                plateauWidget->displayCase(":/Images/Jetons/jeton_rouge.png", {j, i});
                std::cout << "Rouge ";
                break;
            case Noir:
                plateauWidget->displayCase(":/Images/noir.png", {j, i});
                std::cout << "Noir ";
                break;
            case Perle:
                plateauWidget->displayCase(":/Images/Jetons/jeton_perle.png", {j, i});
                std::cout << "Perle ";
                break;
            case Or:
                plateauWidget->displayCase(":/Images/Jetons/jeton_or.png", {j, i});
                std::cout << "Or ";
                break;
            }
        }
        std::cout << std::endl;  // Add a newline after each row
    }
    return plateauWidget;
}
void PlateauWidget::emptyJetons() {
    jetonsTaken.clear();
}

std::map<Case, std::string> PlateauWidget::getPlateauState() const {
    return plateauState;
}
std::map<Case, std::string> &PlateauWidget::getJetonsTaken() {
    return jetonsTaken;
}
