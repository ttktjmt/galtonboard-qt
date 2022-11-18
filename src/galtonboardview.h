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
    float ballpos_offset;
    vector<QGraphicsPixmapItem*> *ballpix;
    vector<QGraphicsPixmapItem*> *framepix;
    QGraphicsScene *scn;

public slots:
    void ResetScnWld();
};

#endif // GALTONBOARDVIEW_H
