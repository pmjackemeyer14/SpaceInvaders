#ifndef ALIENBULLETS_H
#define ALIENBULLETS_H
#include <QWidget>

class AlienBullets
{
public:
    AlienBullets(QWidget *parent);
    void setBulletCoordinates(int x, int y);
    void drawAlienBullets(QPainter& paint);
    void updateCoordinates();
    void setCollision(bool collision);
    bool getBulletDestroyed();
    QRect getBulletRect();
private:
    QWidget* parent;
    QRect bullet;
    bool bulletDestroyed;
    bool collision;
    bool initialShot;
    int ycord;
    int xcord;
    int alienXCord;
    int alienYCord;
    int alienIndex;
};

#endif // ALIENBULLETS_H
