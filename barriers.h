#ifndef BARRIERS_H
#define BARRIERS_H
#include <QWidget>
#include "alienbullets.h"
#include "bullet.h"
class Barriers
{
public:
    Barriers(QWidget *parent=0,Bullet* b = 0,AlienBullets* ab = 0 );
    void DrawBarriers(QPainter& paint);
    void CheckforCollisions();
private:
    QWidget* parent;
    QPainterPath barrier[4];
    Bullet* playerBullet;
    AlienBullets* alienBullet;
    int hitCount[4];
};

#endif // BARRIERS_H
