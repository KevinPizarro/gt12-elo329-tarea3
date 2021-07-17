QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PainterRect
TEMPLATE = app

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Comuna.cpp \
    Pedestrian.cpp \
    Simulator.cpp \
    mainwindow.cpp \
    stage4.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Comuna.h \
    Pedestrian.h \
    Simulator.h \
    mainwindow.h

DISTFILES += \
    config.txt

FORMS += \
    mainwindow.ui
