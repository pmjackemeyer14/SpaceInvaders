#ifndef ALIEN_H
#define ALIEN_H

#include <QRect>
#include <QWidget>
#include "bullet.h"
#include <QMediaPlayer>

class Alien
{
public:
    Alien(QWidget *parent=0,Bullet* bullet = 0);
    void drawAlien(QPainter& paint);
    void updateCoordindates();
    void generateNewNumber();
    int checkforCollisions();
    bool getGameOver();
    int getAlienBulletX();
    int getAlienBulletY();
    int getNumDestroyed();

private:
    QWidget* parent;
    Bullet* bullet;
    //11 columns and 5 rows of aliens
    QRect aliens[55];
    QRect boundingBox;
    int boundBox_xcord;
    int boundBox_ycord;
    int xcord[55];
    int ycord[55];
    int alienIndex;
    int alienDestroyed[55];
    int alienDirection;// 2 = right, 1 = left
    int max[11];
    //determines what phase of the music the game is on
    int phase;
    //keeps track of the number of destroyed aliens
    int numberDestroyed;
    QMediaPlayer* musicPlayer;
    QMediaPlayer* musicPlayerExplosion;
    QImage* alien1;
    QImage* alien2;
    QImage* alien3;
    bool gameOver;
};

#endif // ALIEN_H
