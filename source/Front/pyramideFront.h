#ifndef PYRAMIDEFRONT_H
#define PYRAMIDEFRONT_H
#include <QWidget>
#include <QHBoxLayout>


class pyramidefront : public QWidget
{
public:
    static pyramidefront* getInstance();
    static pyramidefront* creerPyramide();
    static pyramidefront * instance;

    //QVBoxLayout* get_mainLayout();
private:
    pyramidefront(QWidget *parent = nullptr);

};

#endif // PYRAMIDEFRONT_H
