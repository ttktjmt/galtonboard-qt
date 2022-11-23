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
    b2BodyDef frame_bodydef;
    for(uint i=0; i<4; i++){
        frame->at(i) = this->CreateBody(&frame_bodydef);
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
    pin = new vector<b2Body*>(cfg.pinNumAll);
    b2BodyDef pin_bodydef;
    for(uint i=0; i<cfg.pinNumAll; i++){
        pin->at(i) = this->CreateBody(&pin_bodydef);
    }
    b2CircleShape pin_shape;
    pin_shape.m_p.Set(0.0f, 0.0f);
    pin_shape.m_radius = cfg.pinR;
    b2FixtureDef pin_fixdef;
    pin_fixdef.shape = &pin_shape;
    pin_fixdef.density = 1.0f;
    pin_fixdef.friction = 0.001f;
    pin_fixdef.restitution = 0.2f;
    for(uint i=0; i<cfg.pinNumAll; i++){
        pin->at(i)->CreateFixture(&pin_fixdef);
    }

    // Create Fence
    fence = new vector<b2Body*>(cfg.fenceNum);
    b2BodyDef fence_bodydef;
    for(uint i=0; i<cfg.fenceNum; i++){
        fence->at(i) = this->CreateBody(&fence_bodydef);
    }

    // Create Ball
    ball = new vector<b2Body*>;
    ball_def.type = b2_dynamicBody;
    ball_def.position.Set(0.0f, 0.0f);
    ball_def.allowSleep = false;
    ball_shape.m_p.Set(0.0f, 0.0f);
    ball_shape.m_radius = cfg.ballR;
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
    delete fence;
    delete pin;
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
        b2Vec2 gravity(acc->x()*cfg.gScale, acc->y()*cfg.gScale);
#endif
#ifdef Q_OS_ANDROID
        b2Vec2 gravity(-acc->x()*cfg.gScale, -acc->y()*cfg.gScale);
#endif
        this->SetGravity(gravity);
    } else {
        qDebug("Access Denied: Accelerometer");
    }
//    this->SetGravity(b2Vec2(0.0f, -9.8f));
}

void GaltonBoardWorld::AddBall()
{
    ball->push_back(this->CreateBody(&ball_def));
    ball->back()->CreateFixture(&ball_fixdef);
    ball->back()->SetTransform(b2Vec2(0.0f, 4.0f), 0.0f);
//    ball->back()->SetLinearVelocity(b2Vec2((((float)std::rand()/(float)RAND_MAX)-0.5f)/3, ((float)std::rand()/(float)RAND_MAX)*4-2));
    ball->back()->SetLinearVelocity(b2Vec2((((float)std::rand()/(float)RAND_MAX)-0.5f)/3, 0.0f));

    if (ball->size()>=cfg.ballNum) add_timer.stop();
}

void GaltonBoardWorld::button_pushed()
{
    for(uint i=0; i<ball->size(); i++){
        b2Vec2 vel(((float)std::rand()/(float)RAND_MAX)*10-5, ((float)std::rand()/(float)RAND_MAX)*10-5);
        ball->at(i)->SetLinearVelocity(vel);
    }
}

void GaltonBoardWorld::setFrame(float w, float h)
{
    float world_w = w - 2*cfg.frameMarginPix['w'];
    float world_h = h - 2*cfg.frameMarginPix['h'];
    /// TODO: make ppm responsive
    qDebug() << "w/cfg.frame_w :" << w/cfg.frameW;
#ifdef Q_OS_WIN
    if (ppm == -1/*initial*/)     ppm = w/cfg.frameW;
#endif
#ifdef Q_OS_ANDROID // graphicsview is resized twice on android
    if (ppm == -1/*initial*/)     ppm = /*-2;   /// TODO: fix this error happening after refreshing
    else if (ppm == -2) ppm =*/ w/cfg.frameW;
#endif

    // Update Frame Position
    frame->at(0)->SetTransform(b2Vec2(0.0f,            PtoM( world_h/2)), 0.0f);
    frame->at(1)->SetTransform(b2Vec2(0.0f,            PtoM(-world_h/2)), 0.0f);
    frame->at(2)->SetTransform(b2Vec2(PtoM( world_w/2), 0.0f           ), 0.0f);
    frame->at(3)->SetTransform(b2Vec2(PtoM(-world_w/2), 0.0f           ), 0.0f);

    // Update Pin Position
    float p_gap_w = PtoM(world_w)/(cfg.pinNumEach.back()+2), p_gap_h = p_gap_w * sqrt(3)/2, p_offset = p_gap_w/2;
    float p_initpos_x = (cfg.pinNumEach.at(0)%2 == 0)
                      ? -p_gap_w * (cfg.pinNumEach.at(0)/2-0.5)
                      : -p_gap_w * (cfg.pinNumEach.at(0)-1)/2;
    float p_initpos_y =  p_gap_h * (cfg.pinNumEach.size()-1);
    uint cnt = 0;
    for(uint row=0; row<cfg.pinNumEach.size(); row++) {
        for(uint col=0; col<cfg.pinNumEach.at(row); col++){
            float pos_x = p_initpos_x - (p_offset * row) + (p_gap_w * col);
            float pos_y = p_initpos_y - (p_gap_h * row);
            pin->at(cnt)->SetTransform(b2Vec2(pos_x, pos_y), 0.0f);
            cnt++;
        }
    }

    // Update Fence Position
    float f_length = world_h/2 - p_gap_h;
    b2PolygonShape fence_shape;
    fence_shape.SetAsBox(cfg.fenceW, f_length);
    for(uint i=0; i<cfg.fenceNum; i++){
        fence->at(i)->CreateFixture(&fence_shape, 0.0f);
    }
    float f_gap_w = PtoM(world_w)/(cfg.fenceNum+1);
    float f_initpos_x = (cfg.fenceNum%2 == 0)
                      ? -f_gap_w * (cfg.fenceNum/2-0.5)
                      : -f_gap_w * (cfg.fenceNum-1)/2;
    float f_initpos_y = -p_gap_h - f_length/2 - world_h/4;
    for(uint i=0; i<cfg.fenceNum; i++){
        float pos_x = f_initpos_x + (f_gap_w * i);
        fence->at(i)->SetTransform(b2Vec2(pos_x, f_initpos_y), 0.0f);
    }
}

float GaltonBoardWorld::PtoM(float pixel)
{
    if (ppm!=0) return pixel/ppm; else qDebug("Error: ppm==0"); return -1;
}

float GaltonBoardWorld::MtoP(float meter)
{
    if (ppm!=0) return meter*ppm; else qDebug("Error: ppm==0"); return -1;
}
