QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = GaltonBoardSimulator
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    galtonboardworld.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    galtonboardworld.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resource.qrc

INCLUDEPATH += $$PWD/include/box2d
DEPENDPATH += $$PWD/include/box2d

LIBS += \
    -L"$$PWD/lib/debug" -lbox2d \
    -L"$$PWD/lib/release" -lbox2d
