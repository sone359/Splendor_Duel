#ifndef PARTIEWIDGET_H
#define PARTIEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QStringList>
#include "PlateauWidget.h"
#include "BoutonManager.h"

class PartieWidget : public QWidget {
public:
    static PartieWidget *getInstance();
    void displayRoyalImages(const QStringList &imagePaths);
    void remove(PlateauWidget * pl);
    void afficherPlateau(PlateauWidget * pl);

private:
    explicit PartieWidget(QWidget *parent = nullptr);
    static PartieWidget *instance;
    BoutonManager boutonManager;


    QVBoxLayout *mainLayout;
};
#endif // PARTIEWIDGET_H
