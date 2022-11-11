#include "galtonboardview.h"


GaltonBoardView::GaltonBoardView(QObject *parent)
{
    // Initialize world with zero gravity
    gbw = new GaltonBoardWorld(b2Vec2(0.0f, 0.0f));

    // Set Scene
    scn = new QGraphicsScene;
    img = new QImage(":/res/ball.png");
    pix1 = new QGraphicsPixmapItem(QPixmap::fromImage(*img));
    pix2 = new QGraphicsPixmapItem(QPixmap::fromImage(*img));
    pix2->setOpacity(0.3);
    scn->addItem(pix1);
    scn->addItem(pix2);
    setScene(scn);

    // update
    update_timer.start(update_interval_msec);
    connect(&update_timer, &QTimer::timeout, this, &GaltonBoardView::SetPixPos);
}

void GaltonBoardView::SetPixPos()
{
    b2Vec2 pos1 = gbw->body1->GetPosition();
    b2Vec2 pos2 = gbw->body2->GetPosition();
    pix1->setPos(pos1.x*100, -pos1.y*100);
    pix2->setPos(pos2.x*100, -pos2.y*100);
}

//void GaltonBoardView::draw()
//{
//    std::vector<b2Vec2> pos_list;

//    for (ball : gbw->ball_list) {
//        b2Vec2 pos(ball->GetPosition().x, ball->GetPosition().y);
//        pos_list.push_back(pos);
//    }

//    for (item : item_list) {
//        item->setPos(x, y)
//    }
//}
