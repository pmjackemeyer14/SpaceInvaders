#-------------------------------------------------
#
# Project created by QtCreator 2017-04-20T13:14:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpaceInvaders
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    gamewindow.cpp \
    highscore.cpp \
    alien.cpp \
    bullet.cpp \
    playership.cpp \
    alienbullets.cpp \
    barriers.cpp

HEADERS  += widget.h \
    gamewindow.h \
    highscore.h \
    alien.h \
    bullet.h \
    playership.h \
    alienbullets.h \
    barriers.h

FORMS    += widget.ui \
    highscore.ui
