#include "galtonboardscene.h"

GaltonBoardScene::GaltonBoardScene()
{
    // Ball Image
    img = new QImage(":/res/ball.png");
    pmi = new QGraphicsPixmapItem(QPixmap::fromImage((*img)));

    // Set scene
    scn = new QGraphicsScene();
    scn->setSceneRect(this->x()-this->width()/2, this->y()-this->height()/2, this->width(), this->height());
    scn->addItem(pmi);
}
