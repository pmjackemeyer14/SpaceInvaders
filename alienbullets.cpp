#include "alienbullets.h"
#include <ctime>
#include <QPainter>

AlienBullets::AlienBullets(QWidget *parent):parent(parent)
{
   bulletDestroyed = true;
}

void AlienBullets::setBulletCoordinates(int x, int y)
{
    xcord = x+10;
    ycord = y;
}

void AlienBullets::drawAlienBullets(QPainter &paint)
{
    bulletDestroyed = false;
    QColor bulletColor = QColor(255,255,255);
    bullet.setCoords(xcord,ycord,xcord+5,ycord-10);
    paint.drawRect(bullet);
    paint.fillRect(bullet,bulletColor);
}

void AlienBullets::updateCoordinates()
{
    ycord+=10;
    if(ycord > parent->height())
    {
        bulletDestroyed = true;

    }
}
