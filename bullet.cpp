#include "bullet.h"

Bullet::Bullet(QWidget *parent):parent(parent)
{
    bulletDestroyed = true;
    xcord = 0;
    ycord = parent->height()-10;
}

void Bullet::drawBullet(QPainter &paint)
{
    bulletDestroyed = false;
    QColor bulletColor = QColor(255,255,255);
    if(firstFire)
    {
        bullet_xcord = ship_xcord+10;
    }
    bullet.setCoords(xcord,ycord,xcord+5,ycord-10);
    paint->drawRect(bullet);
    paint->fillRect(bullet,bulletColor);
}

void Bullet::updateCoordinates()
{

}
