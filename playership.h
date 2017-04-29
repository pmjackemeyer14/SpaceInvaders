#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H
#include <QWidget>
#include <QPainter>

class PlayerShip
{
public:
    PlayerShip(QWidget *parent=0);
    void drawShip(QPainter& paint);
    void updateCoordinates();
    int getShipXCord();
    int getDirection();
    void setDirection(int d);
private:
    QWidget* parent;
    QRect ship;
    int xcord;
    int direction;// 0 = Stop, 1 = Left, 2 = Right


};

#endif // PLAYERSHIP_H
