#ifndef GALTONBOARDWORLD_H
#define GALTONBOARDWORLD_H

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

    struct BoardConfig
    {   // units: meters-kilogram-second (MKS)
        const float scale   = 100;
        const float width   = 0.114f * scale;
        const float height  = 0.190f * scale;
        std::map<char, int> frame_margin_pix = {{'W', 75}, {'H', 10}};
        const uint  ballNum = 100;
        const float radius  = 0.0012f * scale;
    }bc;

    b2World *world;
    vector<b2Body*> *frame;
    vector<b2Body*> *ball;
    /// TODO: make ppm value responsive
    float ppm = 0;

private:
    void Update();
    void UpdateGravity();

    QTimer update_timer;
    const uint update_interval_msec = 10;

    QAccelerometer *Accelerometer = nullptr;
    const float g_scale = (float)1/6;

    const float timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;

public slots:
    void button_pushed();
};

#endif // GALTONBOARDWORLD_H
