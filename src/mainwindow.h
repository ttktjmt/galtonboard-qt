#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "galtonboardview.h"
#include "galtonboardworld.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SetWindowSize();

    GaltonBoardView *gbv;

private:
    Ui::MainWindow  *ui;
};

#endif // MAINWINDOW_H
