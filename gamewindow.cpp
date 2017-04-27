#include "gamewindow.h"
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>
#include "alien.h"

GameWindow::GameWindow(QWidget *parent) : QWidget(parent)
{

    direction = 0;
    alienDirection = 2;
    bulletDestroyed = true;
    shotFired = false;
    firstFire = false;
    bullet_timer = new QTimer();
    ship_timer = new QTimer();
    alien_timer = new QTimer();
    connect(alien_timer,SIGNAL(timeout()),this,SLOT(updateAlienCoordinates()));
    //connect(bullet_timer,SIGNAL(timeout()),this,SLOT(updateBulletCoordinates()));
    //connect(ship_timer,SIGNAL(timeout()),this,SLOT(updateShipCoordinates()));
    alien_timer->start();
    alien_timer->setInterval(2000);
    ship_timer->start();
    ship_timer->setInterval(50);
    bullet_timer->setInterval(50);
    bullet_xcord = 0;
    bullet_ycord = this->height()-10;
    ship_xcord = this->width()/2;
    aliens = new Alien(this);



}

void GameWindow::paintEvent(QPaintEvent *e)
{
    QPainter* paint = new QPainter(this);
    drawPlayerShip(paint);
    aliens->drawAlien(*paint);
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
//    bullet_ycord-=10;
//    if(bullet_ycord<0)
//    {
//        bulletDestroyed = true;
//        bullet_timer->stop();
//        shotFired = false;
//        bullet_ycord = this->height()-10;
//    }
//    int offset = 0;
//    if(alienDirection == 1)
//    {
//        offset = -10;
//    }else
//    {
//        offset = 10;
//    }
//    for(int i = 0; i<55;i++)
//    {
//        if(bullet_ycord==alien_ycord[i] && bullet_xcord-alien_xcord[i] <= offset)
//        {
//            bulletDestroyed = true;
//            bullet_timer->stop();
//            shotFired = false;
//            bullet_ycord = this->height()-10;
//            alien_ycord[i] = 0;
//            alienDestroyed[i] = 1;
//        }
//    }
//    firstFire = false;
//    this->update();
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

void GameWindow::updateAlienCoordinates()
{
    aliens->updateCoordindates();
    this->update();
}



