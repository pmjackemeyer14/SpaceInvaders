#include "gamewindow.h"
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QKeyEvent>

GameWindow::GameWindow(QWidget *parent) : QWidget(parent)
{
    direction = 0;
    bulletDestroyed = true;
    shotFired = false;
    firstFire = false;
    bullet_timer = new QTimer();
    ship_timer = new QTimer();
    connect(bullet_timer,SIGNAL(timeout()),this,SLOT(updateBulletCoordinates()));
    connect(ship_timer,SIGNAL(timeout()),this,SLOT(updateShipCoordinates()));
    ship_timer->start();
    ship_timer->setInterval(50);
    bullet_timer->setInterval(100);
    bullet_xcord = 0;
    bullet_ycord = this->height()-10;
    ship_xcord = this->width()/2;

}

void GameWindow::paintEvent(QPaintEvent *e)
{
    QPainter* paint = new QPainter(this);
    drawPlayerShip(paint);
    if(shotFired)
    {
        fireShot(paint);
    }

}

void GameWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_Left)
    {
        direction = 1;

    }else if(ev->key()==Qt::Key_Right)
    {
        direction = 2;
    }

    if(ev->key() == Qt::Key_Space)
    {
        if(bulletDestroyed)
        {
            shotFired = true;
            firstFire = true;
            bullet_timer->start();
        }
    }

}

void GameWindow::keyReleaseEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Right || ev->key() == Qt::Key_Left)
    {
        direction = 0;
    }
}

void GameWindow::fireShot(QPainter* paint)
{
    QRect bullet;
    bulletDestroyed = false;
    QColor color2 = QColor(255,255,255);
    if(firstFire)
    {
        bullet_xcord = ship_xcord+10;
    }
    bullet.setCoords(bullet_xcord,bullet_ycord,bullet_xcord+10,bullet_ycord-10);
    paint->drawRect(bullet);
    paint->fillRect(bullet,color2);
}

void GameWindow::drawPlayerShip(QPainter *paint)
{
    QRect r;
    QColor color2 = QColor(76,230,23);
    r.setCoords(ship_xcord,this->height()-10,ship_xcord+20,this->height()-30);
    paint->drawRect(r);
    paint->fillRect(r,color2);
}

void GameWindow::updateBulletCoordinates()
{
    bullet_ycord-=10;
    if(bullet_ycord<0)
    {
        bulletDestroyed = true;
        bullet_timer->stop();
        shotFired = false;
        bullet_ycord = this->height()-10;
    }
    firstFire = false;
    this->update();
}

void GameWindow::updateShipCoordinates()
{
    if(direction == 1)
    {
        ship_xcord-=5;

    }else if(direction == 2)
    {
        ship_xcord+=5;
    }
    this->update();
}



