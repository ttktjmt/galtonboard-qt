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
    void setFrame(float, float);

    struct BoardConfig
    {   // units: meters-kilogram-second (MKS)
        const float width   = 0.114f;
        const float height  = 0.190f;
        const uint  ballNum = 100;
    }bc;

    b2World *world;
    vector<b2Body*> *ball;
    vector<b2Body*> *frame;
    const int ppm = 88/*36*/; // pixels per meter

private:
    void Update();
    void UpdateGravity();
    float PtoM(int);
    int MtoP(float);

    QTimer update_timer;
    const uint update_interval_msec = 10;
    QAccelerometer *Accelerometer = nullptr;

    const float timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;

public slots:
    void button_pushed();
};

#endif // GALTONBOARDWORLD_H
