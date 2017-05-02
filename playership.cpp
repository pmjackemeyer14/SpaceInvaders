#include "playership.h"
#include <QDebug>

PlayerShip::PlayerShip(QWidget *parent, AlienBullets *bullet):parent(parent),enemyBullet(bullet)
{
    gameOver = false;
    direction = 0;
    xcord = parent->width()/2;
    ship.setCoords(xcord,parent->height()-10,xcord+20,parent->height()-30);
}

void PlayerShip::drawShip(QPainter &paint)
{
    QColor shipColor = QColor(76,230,23);
    ship.setCoords(xcord,parent->height()-10,xcord+20,parent->height()-30);
    paint.drawRect(ship);
    paint.fillRect(ship,shipColor);
}

void PlayerShip::updateCoordinates()
{
    if(direction == 1 && xcord > 0)
    {
        xcord-=5;

    }else if(direction == 2 && xcord < (parent->width()-20))
    {
        xcord+=5;
    }
}

int PlayerShip::getShipXCord()
{
    return this->xcord;
}

int PlayerShip::getDirection()
{
    return this->direction;
}

bool PlayerShip::getGameOver()
{
    return this->gameOver;
}

void PlayerShip::setDirection(int d)
{
    direction = d;
}

void PlayerShip::checkForCollisions()
{
    if(enemyBullet->getBulletRect().intersects(ship))
    {
        gameOver = true;
        enemyBullet->setCollision(true);
    }
}
