/// Naming Rule: Google C++ Style Guide (https://google.github.io/styleguide/cppguide.html#Naming)

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Galton Board Simulator");
    w.setStyleSheet("background-color: white;");

    w.show();
    return a.exec();
}
