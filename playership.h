#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H
#include <QWidget>
#include <QPainter>
#include "alienbullets.h"

class PlayerShip
{
public:
    PlayerShip(QWidget *parent=0,AlienBullets* bullet = 0);
    void drawShip(QPainter& paint);
    void updateCoordinates();
    int getShipXCord();
    int getDirection();
    bool getGameOver();
    void setDirection(int d);
    void checkForCollisions();
private:
    QWidget* parent;
    AlienBullets* enemyBullet;
    QRect ship;
    int xcord;
    int direction;// 0 = Stop, 1 = Left, 2 = Right
    bool gameOver;


};

#endif // PLAYERSHIP_H
