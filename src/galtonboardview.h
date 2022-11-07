#ifndef GALTONBOARDVIEW_H
#define GALTONBOARDVIEW_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QTimer>
#include <QWidget>
#include "Box2D/Box2D.h"


class GaltonBoardView : public QGraphicsView
{
public:
    GaltonBoardView(QObject* parent = nullptr);
    QGraphicsScene *scn;

public slots:
    void button_pushed();

private slots:
    void update();

private:
    b2Body *body;
    b2World *world;
    QImage *img;
    QGraphicsPixmapItem *pix;

    QTimer update_timer;
    unsigned int update_interval_msec = 5;
    const float timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;
};

#endif // GALTONBOARDVIEW_H
