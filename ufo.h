#ifndef UFO_H
#define UFO_H
#include <QWidget>

class UFO
{
public:
    UFO(QWidget *parent=0);
    void drawUFO(QPainter& paint);
    void updateCoordinates();
    void setShow(bool shown);
    bool getShow();
private:
    QWidget* parent;
    QRect ufo;
    int xcord;
    bool show;
};

#endif // UFO_H
