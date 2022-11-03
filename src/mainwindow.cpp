#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set Scene
    scn = new QGraphicsScene();
    img = new QImage(":/res/ball.png");
    pix = new QGraphicsPixmapItem(QPixmap::fromImage(*img));
    scn->addItem(pix);
    ui->GaltonBoardView->setScene(scn);

    // Create a world
    b2Vec2 gravity(0.0f, -9.8f);
    b2World world(gravity);

    // Create Static Body (Ground)
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Create Dynamic Body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 10.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Fixture is a glue between body and shape
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);

    // Simulating the World
    for(int32 i = 0; i < 600; i++){
        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();
        printf("%d:  %4.2f %4.2f %4.2f\n", i,  position.x, position.y, angle);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
