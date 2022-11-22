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
    ~GaltonBoardWorld() override;
    void setFrame(float, float);
    float PtoM(float);
    float MtoP(float);

    b2World *world;
    vector<b2Body*> *frame;
    vector<b2Body*> *fence;
    vector<b2Body*> *pin;
    vector<b2Body*> *ball;
    /// TODO: make ppm responsive
    float ppm = -1;

private:
    void Update();
    void UpdateGravity();
    void AddBall();

    Config cfg;
    QTimer update_timer;
    QTimer add_timer;
    const uint update_interval_msec = 5;
    const uint add_interval_msec = 200;
    QAccelerometer *Accelerometer = nullptr;

    b2BodyDef     ball_def;
    b2CircleShape ball_shape;
    b2FixtureDef  ball_fixdef;

public slots:
    void button_pushed();
};

#endif // GALTONBOARDWORLD_H
