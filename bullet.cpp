#include "bullet.h"
#include <QPainter>
#include <QDebug>


Bullet::Bullet(QWidget *parent):parent(parent)
{
    bulletDestroyed = true;
    globalCollision = false;
    collision = false;
    initialShot = true;
    xcord = 0;
    ycord = parent->height()-10;
    shipXCord = parent->width()/2;
}

void Bullet::drawBullet(QPainter &paint)
{
    bulletDestroyed = false;
    QColor bulletColor = QColor(255,255,255);
    if(initialShot)
    {
        xcord = shipXCord+10;
        initialShot = false;
    }
    bullet.setCoords(xcord,ycord,xcord+5,ycord-10);
    paint.drawRect(bullet);
    paint.fillRect(bullet,bulletColor);
}

void Bullet::updateCoordinates()
{
    qDebug()<<"UPDATING BULLET COORDINATES";
        ycord-=10;
        if(ycord <= 0 || collision)
        {
            globalCollision = true;
            collision = false;
            bulletDestroyed = true;
            initialShot = true;
            ycord = parent->height()-10;
            xcord = 0;
            bullet.setCoords(xcord,ycord,xcord+5,ycord-10);
        }
}

void Bullet::setShipXCord(int x)
{
    this->shipXCord = x;
}

void Bullet::setCollision(bool collision)
{
    this->collision = collision;
}

void Bullet::setBulletDestroyed(bool destroyed)
{
    this->bulletDestroyed = destroyed;
}

bool Bullet::getBulletDestroyed()
{
    return this->bulletDestroyed;
}

bool Bullet::getBulletCollision()
{
    return this->collision;
}

int Bullet::getBulletYCord()
{
    return this->ycord;
}

QRect Bullet::getBulletRect()
{
    return this->bullet;
}
