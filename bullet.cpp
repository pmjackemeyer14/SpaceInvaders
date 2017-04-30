#include "bullet.h"
#include <QPainter>


Bullet::Bullet(QWidget *parent):parent(parent)
{
    bulletDestroyed = true;
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
        //NEED TO GET XCORD FROM SHIP
        xcord = shipXCord+10;
        initialShot = false;
    }
    bullet.setCoords(xcord,ycord,xcord+5,ycord-10);
    paint.drawRect(bullet);
    paint.fillRect(bullet,bulletColor);
}

void Bullet::updateCoordinates()
{
        ycord-=10;
        if(ycord <= 0 || collision)
        {
            collision = false;
            bulletDestroyed = true;
            initialShot = true;
            ycord = parent->height()-10;
        }
        //int offset = 0;
//        if(alienDirection == 1)
//        {
//            offset = -10;
//        }else
//        {
//            offset = 10;
//        }
//        for(int i = 0; i<55;i++)
//        {
//            if(bullet_ycord==alien_ycord[i] && bullet_xcord-alien_xcord[i] <= offset)
//            {
//                bulletDestroyed = true;
//                bullet_timer->stop();
//                shotFired = false;
//                bullet_ycord = this->height()-10;
//                alien_ycord[i] = 0;
//                alienDestroyed[i] = 1;
//            }
        //        }
}

void Bullet::setShipXCord(int x)
{
    this->shipXCord = x;
}

void Bullet::setCollision(bool collision)
{
    this->collision = collision;
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
