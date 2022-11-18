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

    // Create Frame
    frame = new vector<b2Body*>(4);
    vector<b2BodyDef> frame_bodydef(4);
    frame_bodydef.at(0).position.Set(0.0f, 4.0f);
    frame_bodydef.at(1).position.Set(0.0f, -4.0f);
    frame_bodydef.at(2).position.Set(2.0f, 0.0f);
    frame_bodydef.at(3).position.Set(-2.0f, 0.0f);
    for(uint i=0; i<4; i++){
        frame->at(i) = this->CreateBody(&frame_bodydef.at(i));
    }
    vector<b2PolygonShape> frame_shape(4);
    frame_shape.at(0).SetAsBox(10000.0f, 0.001f);
    frame_shape.at(1).SetAsBox(10000.0f, 0.001f);
    frame_shape.at(2).SetAsBox(0.001f, 10000.0f);
    frame_shape.at(3).SetAsBox(0.001f, 10000.0f);
    for(uint i=0; i<4; i++){
        frame->at(i)->CreateFixture(&frame_shape.at(i), 0.0f);
    }

    // Create Pin
    const int pinNum = 3;
    pin = new vector<b2Body*>(pinNum);
    vector<b2BodyDef> pin_bodydef(pinNum);
    pin_bodydef.at(0).position.Set(-1.0f, 0.0f);
    pin_bodydef.at(1).position.Set(0.0f, 0.0f);
    pin_bodydef.at(2).position.Set(1.0f, 0.0f);
    for(uint i=0; i<pinNum; i++){
        pin->at(i) = this->CreateBody(&pin_bodydef.at(i));
    }
    b2CircleShape pin_shape;
    pin_shape.m_p.Set(0.0f, 0.0f);
    pin_shape.m_radius = cfg.pin_r;
    b2FixtureDef pin_fixdef;
    pin_fixdef.shape = &pin_shape;
    pin_fixdef.density = 1.0f;
    pin_fixdef.friction = 0.001f;
    pin_fixdef.restitution = 0.2f;
    for(uint i=0; i<pinNum; i++){
        pin->at(i)->CreateFixture(&pin_fixdef);
    }

    // Create Ball
    ball = new vector<b2Body*>;
    ball_def.type = b2_dynamicBody;
    ball_def.position.Set(0.0f, 0.0f);
    ball_def.allowSleep = false;
    ball_shape.m_p.Set(0.0f, 0.0f);
    ball_shape.m_radius = cfg.ball_r;
    ball_fixdef.shape = &ball_shape;
    ball_fixdef.density = 1.0f;
    ball_fixdef.friction = 0.001f;
    ball_fixdef.restitution = 0.2f;

    update_timer.start(update_interval_msec);
    add_timer.start(add_interval_msec);
    connect(&update_timer, &QTimer::timeout, this, &GaltonBoardWorld::Update);
    connect(&update_timer, &QTimer::timeout, this, &GaltonBoardWorld::UpdateGravity);
    connect(&add_timer,    &QTimer::timeout, this, &GaltonBoardWorld::AddBall);
}

GaltonBoardWorld::~GaltonBoardWorld()
{
    delete world;
    delete Accelerometer;
    delete frame;
    delete ball;
    qDebug("WORLD DESTRUCTED");
}

void GaltonBoardWorld::Update()
{
    this->Step(cfg.timeStep, cfg.velocityIterations, cfg.positionIterations);
}

void GaltonBoardWorld::UpdateGravity()
{
    auto acc = Accelerometer->reading();
    if (acc != nullptr){
#ifdef Q_OS_WIN
        b2Vec2 gravity(acc->x()*cfg.g_scale, acc->y()*cfg.g_scale);
#endif
#ifdef Q_OS_ANDROID
        b2Vec2 gravity(-acc->x()*cfg.g_scale, -acc->y()*cfg.g_scale);
#endif
        this->SetGravity(gravity);
    } else {
        qDebug("Access Denied: Accelerometer");
    }
}

void GaltonBoardWorld::AddBall()
{
    ball->push_back(this->CreateBody(&ball_def));
    ball->back()->CreateFixture(&ball_fixdef);
    ball->back()->SetTransform(b2Vec2(0,2.0f), 0.0f);
    ball->back()->SetLinearVelocity(b2Vec2(((float)std::rand()/RAND_MAX)-0.5f, ((float)std::rand()/RAND_MAX)*4-2));

    if (ball->size()>=cfg.ballNum) add_timer.stop();
}

void GaltonBoardWorld::button_pushed()
{
    for(uint i=0; i<ball->size(); i++){
        b2Vec2 vel(((float)std::rand()/RAND_MAX)*10-5, ((float)std::rand()/RAND_MAX)*10-5);
        ball->at(i)->SetLinearVelocity(vel);
    }
}

void GaltonBoardWorld::setFrame(float w, float h)
{
    /// TODO: make ppm responsive
    qDebug() << "w/cfg.frame_w :" << w/cfg.frame_w;
#ifdef Q_OS_WIN
    if (ppm == -1/*initial*/)     ppm = w/cfg.frame_w;
#endif
#ifdef Q_OS_ANDROID // graphicsview is resized twice on android
    if (ppm == -1/*initial*/)     ppm = /*-2;
    else if (ppm == -2) ppm =*/ w/cfg.frame_w;
#endif

    // update frame position
    float h_offset = h/2-cfg.frame_margin_pix['h'];
    float w_offset = w/2-cfg.frame_margin_pix['w'];
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
