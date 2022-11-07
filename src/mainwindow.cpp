#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /// TODO: Instance of GaltonBoardView class is created twice somehow. Need to fix and remove setScene in this class later
    gbv = new GaltonBoardView(this);
    ui->GaltonBoard->setScene(gbv->scn);

    connect(ui->physicsButton, &QPushButton::released, gbv,     &GaltonBoardView::button_pushed);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gbv;
}
