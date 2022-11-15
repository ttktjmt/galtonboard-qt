#ifndef GALTONBOARDWORLD_H
#define GALTONBOARDWORLD_H

#include "config.h"

#include <QObject>
#include <QTimer>
#include <QAccelerometer>
#include <Box2D/Box2D.h>
#include <map>

using std::vector;

class GaltonBoardWorld : public b2World, public QObject
{
public:
    GaltonBoardWorld(b2Vec2);
    void setFrame(float, float);
    float PtoM(float);
    float MtoP(float);

    b2World *world;
    vector<b2Body*> *frame;
    vector<b2Body*> *ball;
    /// TODO: make ppm value responsive
    float ppm = 0;

private:
    void Update();
    void UpdateGravity();

    Config cfg;
    QTimer update_timer;
    const uint update_interval_msec = 5;

    QAccelerometer *Accelerometer = nullptr;
    const float g_scale = (float)1/6;

    const float timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;

public slots:
    void button_pushed();
};

#endif // GALTONBOARDWORLD_H
