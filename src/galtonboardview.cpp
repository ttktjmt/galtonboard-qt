#include "galtonboardview.h"


GaltonBoardView::GaltonBoardView(QObject *parent)
{
    // Initialize world with zero gravity
    gbw = new GaltonBoardWorld(b2Vec2(0.0f, 0.0f));

    // Set Scene
    scn = new QGraphicsScene;
    img = new QImage(":/res/ball.png");
    pix = new QGraphicsPixmapItem(QPixmap::fromImage(*img));
    scn->addItem(pix);
    setScene(scn);

    // update
    update_timer.start(update_interval_msec);
    connect(&update_timer, &QTimer::timeout, this, &GaltonBoardView::setPixPos);
}

void GaltonBoardView::setPixPos()
{
    b2Vec2 pos = gbw->body->GetPosition();
    pix->setPos(pos.x*100, -pos.y*100);
}

///**
// * attach pixmap on calculated position
// *
// * @brief GaltonBoardView::draw
// */
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
