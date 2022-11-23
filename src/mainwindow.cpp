#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gbv = ui->GaltonBoard;

#ifdef Q_OS_WIN
    qDebug("WINDOWS");
    this->resize(380, 780);
#endif
#ifdef Q_OS_ANDROID
    qDebug("ANDROID");
    this->resize(380, 780);
#endif
//    connect(ui->physicsButton, &QPushButton::clicked, gbv->gbw, &GaltonBoardWorld::button_pushed);
    connect(ui->physicsButton, &QPushButton::released, gbv, &GaltonBoardView::ResetScnWld);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gbv;
}
