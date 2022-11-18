#include "galtonboardview.h"


GaltonBoardView::GaltonBoardView(QObject *parent)
{
    // Initialize world with zero gravity
    gbw = new GaltonBoardWorld(b2Vec2(0.0f, 0.0f));

    // Set Scene
    scn = new QGraphicsScene;
    ballimg = new QImage(":/res/ball.png");
    ballpix = new vector<QGraphicsPixmapItem*>(cfg.ballNum);
    for(uint i=0; i<ballpix->size(); i++){
        ballpix->at(i) = new QGraphicsPixmapItem(QPixmap::fromImage(*ballimg));
        ballpix->at(i)->setOpacity((float)(i+cfg.ballNum/8)/(cfg.ballNum*9/8));
        ballpix->at(i)->hide();
        scn->addItem(ballpix->at(i));
    }
    framepix = new vector<QGraphicsPixmapItem*>(4);
    for(uint i=0; i<framepix->size(); i++){
        framepix->at(i) = new QGraphicsPixmapItem(QPixmap::fromImage(*ballimg));
        framepix->at(i)->setOpacity(0.05);
        scn->addItem(framepix->at(i));
    }
    setScene(scn);

    // update
    update_timer.start(update_interval_msec);
    connect(&update_timer, &QTimer::timeout, this, &GaltonBoardView::SetPixPos);
}

GaltonBoardView::~GaltonBoardView()
{
    delete gbw;
    delete ballimg;
    delete ballpix;
    delete framepix;
    delete scn;
}

void GaltonBoardView::resizeEvent(QResizeEvent *event)
{
    qDebug() << "<<RESIZED>>\n" << "width" << this->width() << "\nheight" << this->height();
    float scn_w  = (float)this->width()/2  - cfg.frame_margin_pix['w'];
    float scn_h  = (float)this->height()/2 - cfg.frame_margin_pix['h'];
    scn->setSceneRect(-scn_w, -scn_h, 2*scn_w, 2*scn_h);
    gbw->setFrame(this->width(), this->height());

    // resize ball after updating ppm
    int ballimg_r = ballimg->size().width()/2;
    float ball_scale = cfg.ball_r / gbw->PtoM(ballimg_r);
    ballpos_offset = ball_scale * ballimg_r;
    for(uint i=0; i<ballpix->size(); i++){
        ballpix->at(i)->setScale(ball_scale);
    }
    for(uint i=0; i<framepix->size(); i++){
        framepix->at(i)->setScale(ball_scale);
    }
}

void GaltonBoardView::ResetScnWld()
{
    /// TODO: getting slower so clear data (destruct GaltonBoardWorld instance properly)
    gbw = new GaltonBoardWorld(b2Vec2(0.0f, 0.0f));
    scn = new QGraphicsScene;

    ballpix = new vector<QGraphicsPixmapItem*>(cfg.ballNum);
    for(uint i=0; i<ballpix->size(); i++){
        ballpix->at(i) = new QGraphicsPixmapItem(QPixmap::fromImage(*ballimg));
        ballpix->at(i)->setOpacity((float)(i+cfg.ballNum/8)/(cfg.ballNum*9/8));
        ballpix->at(i)->hide();
        scn->addItem(ballpix->at(i));
    }

    setScene(scn);
    resizeEvent(nullptr);
}

void GaltonBoardView::SetPixPos()
{
    for(uint i=0; i<gbw->ball->size(); i++){
        if (!ballpix->at(i)->isVisible()) ballpix->at(i)->show();
        b2Vec2 pos = gbw->ball->at(i)->GetPosition();
        ballpix->at(i)->setPos(gbw->MtoP(pos.x)-ballpos_offset, gbw->MtoP(-pos.y)-ballpos_offset);
    }
    for(uint i=0; i<4; i++){
        b2Vec2 pos = gbw->frame->at(i)->GetPosition();
        framepix->at(i)->setPos(gbw->MtoP(pos.x)-ballpos_offset, gbw->MtoP(-pos.y)-ballpos_offset);
    }
}
