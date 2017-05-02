#include "ufo.h"
#include <QPainter>

UFO::UFO(QWidget *parent):parent(parent)
{
    show = false;
    xcord = 0;
    ufo.setCoords(xcord,20,xcord+20,40);
}

void UFO::drawUFO(QPainter &paint)
{
    QColor ufoColor = QColor(255,0,23);
    if(show)
    {
        ufo.setCoords(xcord,20,xcord+20,40);
        paint.drawRect(ufo);
        paint.fillRect(ufo,ufoColor);
    }

}

void UFO::updateCoordinates()
{
    if(show)
    {
        xcord+=40;
        if(xcord > parent->width()-20)
        {
            xcord = 0;
            show = false;
        }
    }
}

void UFO::setShow(bool shown)
{
    this->show = shown;
}

bool UFO::getShow()
{
    return this->show;
}
