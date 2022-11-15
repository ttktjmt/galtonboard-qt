#include "galtonboardworld.h"

GaltonBoardWorld::GaltonBoardWorld(b2Vec2 g) : b2World(g)
{
    // Sensor
    try {
        Accelerometer = new QAccelerometer();
        Accelerometer->setAccelerationMode(QAccelerometer::Gravity);
        Accelerometer->setActive(true);
        Accelerometer->start();
    }
    catch (...) {
        qDebug("Access Denied: Accelerometer");
    }

    // Create Static Body (Ground)
    frame = new vector<b2Body*>(4);
    vector<b2BodyDef> groundBodyDef(4);
    groundBodyDef.at(0).position.Set(0.0f, 4.0f);
    groundBodyDef.at(1).position.Set(0.0f, -4.0f);
    groundBodyDef.at(2).position.Set(2.0f, 0.0f);
    groundBodyDef.at(3).position.Set(-2.0f, 0.0f);
    for(uint i=0; i<4; i++){
        frame->at(i) = this->CreateBody(&groundBodyDef.at(i));
    }
    vector<b2PolygonShape> groundBox(4);
    groundBox.at(0).SetAsBox(10000.0f, 0.001f);
    groundBox.at(1).SetAsBox(10000.0f, 0.001f);
    groundBox.at(2).SetAsBox(0.001f, 10000.0f);
    groundBox.at(3).SetAsBox(0.001f, 10000.0f);
    for(uint i=0; i<4; i++){
        frame->at(i)->CreateFixture(&groundBox.at(i), 0.0f);
    }

    // Create Dynamic Body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 0.002f);
    bodyDef.allowSleep = false;
    ball = new vector<b2Body*>(bc.ballNum);
    for(uint i=0; i<bc.ballNum; i++){
        ball->at(i) = this->CreateBody(&bodyDef);
    }

    b2CircleShape dynamicCircle;
    dynamicCircle.m_p.Set(0.0f, 0.0f);
    dynamicCircle.m_radius = bc.radius;
    //    b2PolygonShape dynamicBox;
    //    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Fixture is a glue between body and shape
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    //    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.001f;
    fixtureDef.restitution = 0.2f;

    for(uint i=0; i<bc.ballNum; i++){
        ball->at(i)->CreateFixture(&fixtureDef);
    }

    for(uint i=0; i<bc.ballNum; i++){
        b2Vec2 vel(std::rand()%100/10-5/*[-5,5]*/, std::rand()%100/10-5);
        ball->at(i)->SetTransform(b2Vec2(i/1000,i/1000),0.0f);
        ball->at(i)->SetLinearVelocity(vel);
    }

    update_timer.start(update_interval_msec);
    connect(&update_timer, &QTimer::timeout, this, &GaltonBoardWorld::Update);
    connect(&update_timer, &QTimer::timeout, this, &GaltonBoardWorld::UpdateGravity);
}

void GaltonBoardWorld::Update()
{
    this->Step(timeStep, velocityIterations, positionIterations);
}

void GaltonBoardWorld::UpdateGravity()
{
    auto acc = Accelerometer->reading();
    if (acc != nullptr){
#ifdef Q_OS_WIN
        b2Vec2 gravity(acc->x()*g_scale, acc->y()*g_scale);
#endif
#ifdef Q_OS_ANDROID
        b2Vec2 gravity(-acc->x()*g_scale, -acc->y()*g_scale);
#endif
        this->SetGravity(gravity);
    } else {
        qDebug("Access Denied: Accelerometer");
    }
}

void GaltonBoardWorld::button_pushed()
{
    for(uint i=0; i<bc.ballNum; i++){
        b2Vec2 vel(std::rand()%100/10-5/*[-5,5]*/, std::rand()%100/10-3);
        ball->at(i)->SetLinearVelocity(vel);
    }
}

void GaltonBoardWorld::setFrame(float w, float h)
{
    /// TODO: make it responsive
    if (ppm == 0/*initial*/) ppm = w/bc.width;

    // update frame position
    float h_offset = h/2-bc.frame_margin_pix['H'];
    float w_offset = w/2-bc.frame_margin_pix['M'];
    frame->at(0)->SetTransform(b2Vec2(0.0f,            PtoM( h_offset)), 0.0f);
    frame->at(1)->SetTransform(b2Vec2(0.0f,            PtoM(-h_offset)), 0.0f);
    frame->at(2)->SetTransform(b2Vec2(PtoM( w_offset), 0.0f           ), 0.0f);
    frame->at(3)->SetTransform(b2Vec2(PtoM(-w_offset), 0.0f           ), 0.0f);
}

float GaltonBoardWorld::PtoM(float pixel)
{
    if (ppm!=0) return pixel/ppm; else qDebug("Error: ppm==0"); return -1;
}

float GaltonBoardWorld::MtoP(float meter)
{
    if (ppm!=0) return meter*ppm; else qDebug("Error: ppm==0"); return -1;
}
