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
    shotFired = false;
    bullet_timer = new QTimer();
    ship_timer = new QTimer();
    alien_timer = new QTimer();
    connect(alien_timer,SIGNAL(timeout()),this,SLOT(updateAlienCoordinates()));
    connect(bullet_timer,SIGNAL(timeout()),this,SLOT(updateBulletCoordinates()));
    connect(ship_timer,SIGNAL(timeout()),this,SLOT(updateShipCoordinates()));
    alien_timer->start();
    alien_timer->setInterval(2000);
    ship_timer->start();
    ship_timer->setInterval(50);
    bullet_timer->setInterval(50);
    aliens = new Alien(this);
    bullet = new Bullet(this);
    ship = new PlayerShip(this);
}

void GameWindow::paintEvent(QPaintEvent *e)
{
    QPainter* paint = new QPainter(this);
    ship->drawShip(*paint);
    aliens->drawAlien(*paint);
    if(shotFired)
    {
        bullet->drawBullet(*paint);
    }

}

void GameWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_Left)
    {
        ship->setDirection(1);

    }else if(ev->key()==Qt::Key_Right)
    {
        ship->setDirection(2);
    }

    if(ev->key() == Qt::Key_Space)
    {
        if(bullet->getBulletDestroyed())
        {
            shotFired = true;
            bullet_timer->start();
        }
    }

}

void GameWindow::keyReleaseEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Right || ev->key() == Qt::Key_Left)
    {
        ship->setDirection(0);
    }
}


void GameWindow::updateBulletCoordinates()
{
    if(bullet->getBulletYCord()<20)
    {
        bullet_timer->stop();
        shotFired = false;
    }
    bullet->updateCoordinates();
    this->update();
}

void GameWindow::updateShipCoordinates()
{
    ship->updateCoordinates();
    bullet->setShipXCord(ship->getShipXCord());
    this->update();
}

void GameWindow::updateAlienCoordinates()
{
    aliens->updateCoordindates();
    this->update();
}



