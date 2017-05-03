#ifndef UFO_H
#define UFO_H
#include <QWidget>
#include "bullet.h"
#include <QMediaPlayer>

class UFO
{
public:
    UFO(QWidget *parent=0,Bullet* b = 0);
    void drawUFO(QPainter& paint);
    void updateCoordinates();
    bool checkForCollisions();
    void setShow(bool shown);
    bool getShow();
private:
    QWidget* parent;
    Bullet* bullet;
    QMediaPlayer* musicPlayer;
    QMediaPlayer* UFOmusicPlayer;
    QRect ufo;
    QImage* ufoPic;
    int xcord;
    bool show;
};

#endif // UFO_H
