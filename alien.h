#ifndef ALIEN_H
#define ALIEN_H

#include <QRect>
#include <QWidget>

class Alien
{
public:
    Alien(QWidget *parent=0);
    void drawAlien(QPainter& paint);
    void updateCoordindates();
private:
    QWidget* parent;
    QRect aliens[55];
    QRect boundingBox;
    int boundBox_xcord;
    int boundBox_ycord;
    int xcord[55];
    int ycord[55];
    int alienDestroyed[55];
    int alienDirection;
};

#endif // ALIEN_H
