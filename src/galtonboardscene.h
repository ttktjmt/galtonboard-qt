#ifndef GALTONBOARDSCENE_H
#define GALTONBOARDSCENE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>


class GaltonBoardScene : public QGraphicsView
{
public:
    GaltonBoardScene();
    QGraphicsPixmapItem* pmi;

private:
    QImage* img;
    QGraphicsScene* scn;
};

#endif // GALTONBOARDSCENE_H
