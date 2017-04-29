#ifndef BULLET_H
#define BULLET_H
#include <QWidget>

class Bullet
{
public:
    Bullet(QWidget *parent=0);
    void drawBullet(QPainter& paint);
    void updateCoordinates();
    void setShipXCord(int x);
    bool getBulletDestroyed();
    int getBulletYCord();
private:
    QWidget* parent;
    QRect bullet;
    bool bulletDestroyed;
    bool initialShot;
    int ycord;
    int xcord;
    int shipXCord;

};

#endif // BULLET_H
