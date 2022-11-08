#ifndef GALTONBOARDVIEW_H
#define GALTONBOARDVIEW_H

#include "galtonboardworld.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QWidget>
#include <Box2D/Box2D.h>


class GaltonBoardView : public QGraphicsView
{
public:
    GaltonBoardView(QObject* parent = nullptr);
    GaltonBoardWorld    *gbw;

public slots:

private:
    void setPixPos();

    QTimer update_timer;
    uint update_interval_msec = 5;
    QImage              *img;
    QGraphicsPixmapItem *pix;
    QGraphicsScene      *scn;
};

#endif // GALTONBOARDVIEW_H
