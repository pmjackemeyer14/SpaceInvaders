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
    highscore.cpp

HEADERS  += widget.h \
    gamewindow.h \
    highscore.h

FORMS    += widget.ui \
    highscore.ui
