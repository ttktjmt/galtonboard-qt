#include "galtonboardview.h"


GaltonBoardView::GaltonBoardView(QObject *parent)
{
    // Initialize world with zero gravity
    gbw = new GaltonBoardWorld(b2Vec2(0.0f, 0.0f));

    // Set Scene
    scn = new QGraphicsScene;
    img = new QImage(":/res/ball.png");
    ballpix = new vector<QGraphicsPixmapItem*>(gbw->bc.ballNum);
    for(uint i=0; i<gbw->bc.ballNum; i++){
        ballpix->at(i) = new QGraphicsPixmapItem(QPixmap::fromImage(*img));
        ballpix->at(i)->setOpacity((float)(i+gbw->bc.ballNum/5)/(gbw->bc.ballNum*6/5));
        scn->addItem(ballpix->at(i));
    }
    framepix = new vector<QGraphicsPixmapItem*>(4);
    for(uint i=0; i<4; i++){
        framepix->at(i) = new QGraphicsPixmapItem(QPixmap::fromImage(*img));
//        scn->addItem(framepix->at(i));
    }
    setScene(scn);

    // update
    update_timer.start(update_interval_msec);
    connect(&update_timer, &QTimer::timeout, this, &GaltonBoardView::SetPixPos);
}

void GaltonBoardView::resizeEvent(QResizeEvent *event)
{
    qDebug() << "<<RESIZED>>\n" << "width" << this->width() << "\nheight" << this->height();
    gbw->setFrame(this->width(), this->height());
}

void GaltonBoardView::SetPixPos()
{
    for(uint i=0; i<gbw->bc.ballNum; i++){
        b2Vec2 pos = gbw->ball->at(i)->GetPosition();
        ballpix->at(i)->setPos(gbw->MtoP(pos.x, true), gbw->MtoP(-pos.y, false));
    }
    for(uint i=0; i<4; i++){
        b2Vec2 pos = gbw->frame->at(i)->GetPosition();
        framepix->at(i)->setPos(gbw->MtoP(pos.x, true), gbw->MtoP(-pos.y, false));
        framepix->at(i)->setScale(3);
    }
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
