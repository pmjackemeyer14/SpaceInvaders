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

    QPainterPath barrier1,barrier2,barrier3,barrier4;
    barrier1.moveTo(80,parent->height()-50);
    barrier1.lineTo(80,parent->height()-90);
    barrier1.lineTo(130,parent->height()-90);
    barrier1.lineTo(130,parent->height()-50);
    barrier1.lineTo(120,parent->height()-50);
    barrier1.lineTo(120,parent->height()-80);
    barrier1.lineTo(90,parent->height()-80);
    barrier1.lineTo(90,parent->height()-50);
    barrier1.closeSubpath();
    barrier[0] = barrier1;

    barrier2.moveTo(230,parent->height()-50);
    barrier2.lineTo(230,parent->height()-90);
    barrier2.lineTo(280,parent->height()-90);
    barrier2.lineTo(280,parent->height()-50);
    barrier2.lineTo(270,parent->height()-50);
    barrier2.lineTo(270,parent->height()-80);
    barrier2.lineTo(240,parent->height()-80);
    barrier2.lineTo(240,parent->height()-50);
    barrier2.closeSubpath();
    barrier[1] = barrier2;

    barrier3.moveTo(380,parent->height()-50);
    barrier3.lineTo(380,parent->height()-90);
    barrier3.lineTo(430,parent->height()-90);
    barrier3.lineTo(430,parent->height()-50);
    barrier3.lineTo(420,parent->height()-50);
    barrier3.lineTo(420,parent->height()-80);
    barrier3.lineTo(390,parent->height()-80);
    barrier3.lineTo(390,parent->height()-50);
    barrier3.closeSubpath();
    barrier[2] = barrier3;

    barrier4.moveTo(530,parent->height()-50);
    barrier4.lineTo(530,parent->height()-90);
    barrier4.lineTo(580,parent->height()-90);
    barrier4.lineTo(580,parent->height()-50);
    barrier4.lineTo(570,parent->height()-50);
    barrier4.lineTo(570,parent->height()-80);
    barrier4.lineTo(540,parent->height()-80);
    barrier4.lineTo(540,parent->height()-50);
    barrier4.closeSubpath();
    barrier[3] = barrier4;

//        QPainterPath roundRectPath;
//        roundRectPath.moveTo(80.0, 35.0);
//        roundRectPath.arcTo(70.0, 30.0, 10.0, 10.0, 0.0, 90.0);
//        roundRectPath.lineTo(25.0, 30.0);
//        roundRectPath.arcTo(20.0, 30.0, 10.0, 10.0, 90.0, 90.0);
//        roundRectPath.lineTo(20.0, 65.0);
//        roundRectPath.arcTo(20.0, 60.0, 10.0, 10.0, 180.0, 90.0);
//        roundRectPath.lineTo(75.0, 70.0);
//        roundRectPath.arcTo(70.0, 60.0, 10.0, 10.0, 270.0, 90.0);
//        roundRectPath.closeSubpath();
        paint.fillPath(barrier1,Qt::blue);
        paint.fillPath(barrier2,Qt::blue);
        paint.fillPath(barrier3,Qt::blue);
        paint.fillPath(barrier4,Qt::blue);
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

        }
        if(barrier[i].intersects(alienBullet->getBulletRect()))
        {
            qDebug()<<"COLLISION DETECTED ON BARRIER "<<i;
            hitCount[i]++;
            alienBullet->setCollision(true);
        }
    }

}
