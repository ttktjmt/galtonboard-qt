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
//    b2Vec2 gravity(0.0f, -0.1f);
    world = new b2World(gravity);

    // Create Static Body (Ground)
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
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

    body->CreateFixture(&fixtureDef);

    connect(&update_timer,SIGNAL(timeout()),this,SLOT(update()));
    update_timer.start(30);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_released()
{
    body->SetAwake(true);
    b2Vec2 pos(0.0f, 4.0f);
    body->SetTransform(pos, 0.0f);
    update_timer.start(30);
}

void MainWindow::update()
{
    world->Step(timeStep, velocityIterations, positionIterations);
    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();
    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    pix->setPos(position.x*100, -position.y*100);
}
