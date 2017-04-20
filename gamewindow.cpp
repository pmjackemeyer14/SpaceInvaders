#include "gamewindow.h"
#include <QPainter>
#include <QPaintEvent>

GameWindow::GameWindow(QWidget *parent) : QWidget(parent)
{

}

void GameWindow::paintEvent(QPaintEvent *e)
{
    QRect r;
    r.setCoords(20,40,20,80);
    QPainter p;
    p.drawRect(r);

}

