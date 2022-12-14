#ifndef GALTONBOARDVIEW_H
#define GALTONBOARDVIEW_H

#include "galtonboardworld.h"
#include "config.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QWidget>
#include <Box2D/Box2D.h>

using std::vector;

class GaltonBoardView : public QGraphicsView
{
public:
    GaltonBoardView(QObject* parent = nullptr);
    ~GaltonBoardView() override;
    GaltonBoardWorld *gbw;
    Config cfg;

private:
    void SetPixPos();
    void resizeEvent(QResizeEvent*);

    QTimer update_timer;
    uint update_interval_msec = 5;
    QImage *ballimg;
    QImage *pinimg;
    float ballpos_offset, pinpos_offset;
    vector<QGraphicsPixmapItem*> *framepix;
    vector<QGraphicsPixmapItem*> *pinpix;
    vector<QGraphicsPixmapItem*> *ballpix;
    QGraphicsScene *scn;

public slots:
    void ResetScnWld();
};

#endif // GALTONBOARDVIEW_H
