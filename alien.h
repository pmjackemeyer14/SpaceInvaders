#ifndef ALIEN_H
#define ALIEN_H

#include <QRect>
#include <QWidget>
#include "bullet.h"

class Alien
{
public:
    Alien(QWidget *parent=0,Bullet* bullet = 0);
    void drawAlien(QPainter& paint);
    void updateCoordindates();
    int checkforCollisions();
    bool getGameOver();
    int getAlienBulletX();
    int getAlienBulletY();

private:
    QWidget* parent;
    Bullet* bullet;
    QRect aliens[55];
    QRect boundingBox;
    int boundBox_xcord;
    int boundBox_ycord;
    int xcord[55];
    int ycord[55];
    int alienIndex;
    int alienDestroyed[55];
    int alienDirection;
    int max;
    bool gameOver;
};

#endif // ALIEN_H
