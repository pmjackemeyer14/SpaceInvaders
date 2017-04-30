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
    alienBulletTimer = new QTimer();
    connect(alien_timer,SIGNAL(timeout()),this,SLOT(updateAlienCoordinates()));
    connect(bullet_timer,SIGNAL(timeout()),this,SLOT(updateBulletCoordinates()));
    connect(ship_timer,SIGNAL(timeout()),this,SLOT(updateShipCoordinates()));
    connect(alienBulletTimer,SIGNAL(timeout()),this,SLOT(updateAlienBulletCoordinates()));
    alien_timer->start();
    alien_timer->setInterval(2000);
    ship_timer->start();
    ship_timer->setInterval(30);
    bullet_timer->setInterval(50);
    alienBulletTimer->start();
    alienBulletTimer->setInterval(50);
    bullet = new Bullet(this);
    aliens = new Alien(this,bullet);
    alienBullet = new AlienBullets(this);
    alienBullet->setBulletCoordinates(aliens->getAlienBulletX(),aliens->getAlienBulletY());
    ship = new PlayerShip(this,alienBullet);
    barrier = new Barriers(this,bullet,alienBullet);
}

void GameWindow::paintEvent(QPaintEvent *e)
{
    QPainter* paint = new QPainter(this);
    aliens->drawAlien(*paint);
    alienBullet->drawAlienBullets(*paint);
    ship->drawShip(*paint);
    barrier->DrawBarriers(*paint);
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
    aliens->checkforCollisions();
    barrier->CheckforCollisions();
    if(bullet->getBulletYCord()<20 || bullet->getBulletCollision() )
    {
        bullet_timer->stop();
        shotFired = false;
    }
    bullet->updateCoordinates();
    this->update();
}

void GameWindow::updateShipCoordinates()
{
    ship->checkForCollisions();
    if(ship->getGameOver())
    {
        alien_timer->stop();
        ship_timer->stop();
        bullet_timer->stop();
        alienBulletTimer->stop();
        QMessageBox mBox;
        mBox.setText("GAME OVER");
        mBox.exec();
        this->close();
    }
    ship->updateCoordinates();
    bullet->setShipXCord(ship->getShipXCord());
    this->update();
}

void GameWindow::updateAlienCoordinates()
{
    if(aliens->getGameOver())
    {
        alien_timer->stop();
        ship_timer->stop();
        bullet_timer->stop();
        alienBulletTimer->stop();
        QMessageBox mBox;
        mBox.setText("GAME OVER");
        mBox.exec();
        this->close();
    }
    aliens->checkforCollisions();
    aliens->updateCoordindates();
    this->update();
}

void GameWindow::collisionCheck()
{
    //aliens->checkforCollisions();
    //this->update();
}

void GameWindow::updateAlienBulletCoordinates()
{
    ship->checkForCollisions();
    barrier->CheckforCollisions();
    alienBullet->updateCoordinates();
    if(alienBullet->getBulletDestroyed())
    {
        alienBullet->setBulletCoordinates(aliens->getAlienBulletX(),aliens->getAlienBulletY());
    }
    this->update();
}



