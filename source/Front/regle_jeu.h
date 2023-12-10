#ifndef REGLE_JEU_H
#define REGLE_JEU_H
#include <QWidget>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

class PageRegles : public QWidget
{
    Q_OBJECT

public:
    explicit PageRegles(QWidget *parent = nullptr);
    ~PageRegles();

private:
    QScrollArea *scrollArea;
    QWidget *scrollWidget;
    QHBoxLayout *scrollLayout;

    QList<QPixmap> imageList;
    QList<QLabel *> imageLabels;

    void setupImages();
};
#endif // REGLE_JEU_H
