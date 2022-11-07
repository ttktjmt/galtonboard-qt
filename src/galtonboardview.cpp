#include "galtonboardview.h"


GaltonBoardView::GaltonBoardView(QObject *parent)
{
    // Create a world
    b2Vec2 gravity(0.0f, -9.8f);
    world = new b2World(gravity);

    // Create Static Body (Ground)
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -13.0f);
    b2Body* groundBody = world->CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Create Dynamic Body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    body = world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Fixture is a glue between body and shape
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.8f;

    body->CreateFixture(&fixtureDef);

    // Set Scene
    scn = new QGraphicsScene;
    img = new QImage(":/res/ball.png");
    pix = new QGraphicsPixmapItem(QPixmap::fromImage(*img));
    scn->addItem(pix);
//    setScene(scn);

    connect(&update_timer,  &QTimer::timeout,   this,   &GaltonBoardView::update);
    update_timer.start(update_interval_msec);
}

void GaltonBoardView::update()
{
    world->Step(timeStep, velocityIterations, positionIterations);
    b2Vec2 position = body->GetPosition();
    pix->setPos(position.x*100, -position.y*100);
}

void GaltonBoardView::button_pushed()
{
    body->SetAwake(true);
    b2Vec2 vel(0.0f, 4.0f);
    body->SetLinearVelocity(vel);
}
