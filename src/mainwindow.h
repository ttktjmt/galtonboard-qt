#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QTimer>
#include "Box2D/Box2D.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_released();
    void update();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scn;
    QImage *img;
    QGraphicsPixmapItem *pix;
    QTimer update_timer;
    b2World *world;
    b2Body *body;

    unsigned int update_interval_msec = 1;

    const float timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 6;
    const int32 positionIterations = 2;
};

#endif // MAINWINDOW_H
