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
    void setCollision(bool collision);
    void setBulletDestroyed(bool destroyed);
    bool getBulletDestroyed();
    bool getBulletCollision();
    int getBulletYCord();
    QRect getBulletRect();
private:
    QWidget* parent;
    QRect bullet;
    bool bulletDestroyed;
    bool collision;
    bool globalCollision;
    bool initialShot;
    int ycord;
    int xcord;
    int shipXCord;

};

#endif // BULLET_H
