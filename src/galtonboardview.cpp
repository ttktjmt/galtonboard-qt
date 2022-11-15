#include "galtonboardview.h"


GaltonBoardView::GaltonBoardView(QObject *parent)
{
    // Initialize world with zero gravity
    gbw = new GaltonBoardWorld(b2Vec2(0.0f, 0.0f));

    // Set Scene
    scn = new QGraphicsScene;
    ballimg = new QImage(":/res/ball.png");
    ballpix = new vector<QGraphicsPixmapItem*>(gbw->bc.ballNum);
    for(uint i=0; i<gbw->bc.ballNum; i++){
        ballpix->at(i) = new QGraphicsPixmapItem(QPixmap::fromImage(*ballimg));
        ballpix->at(i)->setOpacity((float)(i+gbw->bc.ballNum/10)/(gbw->bc.ballNum*11/10));
        scn->addItem(ballpix->at(i));
    }
    framepix = new vector<QGraphicsPixmapItem*>(4);
    for(uint i=0; i<4; i++){
        framepix->at(i) = new QGraphicsPixmapItem(QPixmap::fromImage(*ballimg));
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
    float w_offset = this->width()/2 - gbw->bc.frame_margin_pix['M'];
    float h_offset = this->height()/2 - gbw->bc.frame_margin_pix['H'];
    scn->setSceneRect(-w_offset, -h_offset, 2*w_offset, 2*h_offset);
    gbw->setFrame(this->width(), this->height());

    // change ball size after updating ppm
    int ballimg_radius = ballimg->size().width()/2;
    float ball_scale = (float)gbw->bc.radius / gbw->PtoM(ballimg_radius);
    qDebug() << "ball_scale :" << ball_scale;
    for(uint i=0; i<gbw->bc.ballNum; i++){
        ballpix->at(i)->setScale(ball_scale);
    }
}

void GaltonBoardView::SetPixPos()
{
    for(uint i=0; i<gbw->bc.ballNum; i++){
        b2Vec2 pos = gbw->ball->at(i)->GetPosition();
        ballpix->at(i)->setPos(gbw->MtoP(pos.x), gbw->MtoP(-pos.y));
    }
    for(uint i=0; i<4; i++){
        b2Vec2 pos = gbw->frame->at(i)->GetPosition();
        framepix->at(i)->setPos(gbw->MtoP(pos.x), gbw->MtoP(-pos.y));
        framepix->at(i)->setScale(3);
    }
}
