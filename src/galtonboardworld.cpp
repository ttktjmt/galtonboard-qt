#include "galtonboardworld.h"

GaltonBoardWorld::GaltonBoardWorld(b2Vec2 g) : b2World(g)
{
    // Sensor
    Accelerometer = new QAccelerometer();
    Accelerometer->setAccelerationMode(QAccelerometer::Gravity);
    Accelerometer->setActive(true);
    Accelerometer->start();

    // Create Static Body (Ground)
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -13.0f);
    b2Body* groundBody = this->CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Create Dynamic Body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    body = this->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Fixture is a glue between body and shape
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.8f;

    body->CreateFixture(&fixtureDef);

    update_timer.start(update_interval_msec);
    connect(&update_timer, &QTimer::timeout, this, &GaltonBoardWorld::update);
    connect(&update_timer, &QTimer::timeout, this, &GaltonBoardWorld::update_gravity);
}

void GaltonBoardWorld::update()
{
    this->Step(timeStep, velocityIterations, positionIterations);
    // set pix pos
}

void GaltonBoardWorld::update_gravity()
{
    try {
        auto acc = Accelerometer->reading();
        b2Vec2 gravity(-acc->x(), -acc->y());
        this->SetGravity(gravity);
    }
    catch (...) {
        qDebug("Access Denied: Accelerometer");
    }
}

void GaltonBoardWorld::button_pushed()
{
    body->SetAwake(true);
    b2Vec2 vel(0.0f, 4.0f);
    body->SetLinearVelocity(vel);
}

