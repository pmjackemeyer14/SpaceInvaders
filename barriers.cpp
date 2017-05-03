#include "barriers.h"
#include <QPainter>
#include <QPainterPath>
#include <QDebug>

Barriers::Barriers(QWidget *parent, Bullet *b, AlienBullets *ab):parent(parent),playerBullet(b),alienBullet(ab)
{
    for(int i = 0;i<4;i++)
    {
        hitCount[i] = 0;
    }

}

void Barriers::DrawBarriers(QPainter &paint)
{


    QPainterPath barriers[4];
    int x = 80;
    int y = parent->height()-50;
    for(int i = 0;i<4;i++)
    {
        if(hitCount[i] >= 4)
        {

        }else
        {
          barriers[i].moveTo(x,y);
          barriers[i].lineTo(x,y-40);
          barriers[i].lineTo(x+50,y-40);
          barriers[i].lineTo(x+50,y);
          barriers[i].lineTo(x+40,y);
          barriers[i].lineTo(x+40,y-30);
          barriers[i].lineTo(x+10,y-30);
          barriers[i].lineTo(x+10,y);
          barriers[i].closeSubpath();

        }
        x+=150;
        barrier[i] = barriers[i];
    }

    for(int i = 0;i<4;i++)
    {
        if(hitCount[i]==1)
        {
            paint.fillPath(barrier[i],Qt::green);
        }else if(hitCount[i]==2)
        {
            paint.fillPath(barrier[i],Qt::yellow);
        }else if(hitCount[i]==3)
        {
            paint.fillPath(barrier[i],Qt::red);
        }else if(hitCount[i] == 0)
        {
            paint.fillPath(barrier[i],Qt::blue);
        }
    }

}

void Barriers::CheckforCollisions()
{
    for(int i = 0; i<4;i++)
    {
        if(barrier[i].intersects(playerBullet->getBulletRect()))
        {
            qDebug()<<"COLLISION DETECTED ON BARRIER "<<i;
            hitCount[i]++;
            playerBullet->setCollision(true);
            //playerBullet->updateCoordinates();

        }
        if(barrier[i].intersects(alienBullet->getBulletRect()))
        {
            qDebug()<<"COLLISION DETECTED ON BARRIER "<<i;
            hitCount[i]++;
            alienBullet->setCollision(true);
        }
    }

}
