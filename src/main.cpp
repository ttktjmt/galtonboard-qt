/// Naming Rule: Google C++ Style Guide (https://google.github.io/styleguide/cppguide.html#Naming)
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Galton Board Simulator");

#ifdef Q_OS_WIN
    qDebug("WINDOWS");
    w.resize(380, 780);
#endif
#ifdef Q_OS_ANDROID
    qDebug("ANDROID");
#endif

    w.show();
    return a.exec();
}
