#ifndef BULLET_H
#define BULLET_H
#include <QWidget>

class Bullet
{
public:
    Bullet(QWidget *parent=0);
    void drawBullet(QPainter& paint);
    void updateCoordinates();
private:
    QWidget* parent;
    QRect bullet;
    bool bulletDestroyed;
    int ycord;
    int xcord;

};

#endif // BULLET_H
