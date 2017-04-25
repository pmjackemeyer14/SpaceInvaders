#include "gamewindow.h"
#include <QPainter>
#include <QPaintEvent>

GameWindow::GameWindow(QWidget *parent) : QWidget(parent)
{

}

void GameWindow::paintEvent(QPaintEvent *e)
{
    QPainter* paint = new QPainter(this);
    QRect r;
    QColor color2 = QColor(76,230,23);
    r.setCoords(20,40,60,80);
    paint->drawRect(r);
    paint->fillRect(r,color2);

}

