#ifndef GALTONBOARDWORLD_H
#define GALTONBOARDWORLD_H

#include <QObject>
#include <QTimer>
#include <QAccelerometer>
#include <Box2D/Box2D.h>

using std::vector;

class GaltonBoardWorld : public b2World, public QObject
{
public:
    GaltonBoardWorld(b2Vec2);
    b2World *world;
    b2Body *body;

private:
    void update();
    void update_gravity();

//    vector<Ball> ball_list;
    QTimer update_timer;
    uint update_interval_msec = 5;
    QAccelerometer *Accelerometer = nullptr;

    const float timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;

public slots:
    void button_pushed();
};

#endif // GALTONBOARDWORLD_H
