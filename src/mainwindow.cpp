#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gbv = ui->GaltonBoard;

    connect(ui->physicsButton, &QPushButton::clicked, gbv->gbw, &GaltonBoardWorld::button_pushed);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gbv;
}
