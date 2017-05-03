#include "ufo.h"
#include <QPainter>
#include <QMediaPlayer>

UFO::UFO(QWidget *parent, Bullet *b):parent(parent),bullet(b)
{
    show = false;
    xcord = 0;
    ufo.setCoords(xcord,40,xcord+30,60);
    ufoPic = new QImage("../SpaceInvaders/UFO.jpg");
    *ufoPic = ufoPic->scaled(30,20);
    musicPlayer = new QMediaPlayer();
    musicPlayer->setMedia(QUrl::fromLocalFile("../SpaceInvaders/invaderkilled.wav"));
    UFOmusicPlayer = new QMediaPlayer();
    UFOmusicPlayer->setMedia(QUrl::fromLocalFile("../SpaceInvaders/ufo_highpitch.wav"));
}

void UFO::drawUFO(QPainter &paint)
{
    QColor ufoColor = QColor(255,0,23);
    if(show)
    {
        ufo.setCoords(xcord,40,xcord+30,60);
        paint.drawRect(ufo);
        //paint.fillRect(ufo,ufoColor);
        paint.drawImage(xcord,40,*ufoPic);
    }

}

void UFO::updateCoordinates()
{
    if(show)
    {
        xcord+=20;
        UFOmusicPlayer->setVolume(50);
        UFOmusicPlayer->play();
        if(xcord > parent->width()-20)
        {
            xcord = 0;
            show = false;
        }
    }
}

bool UFO::checkForCollisions()
{
    bool destroyed = false;
        if(bullet->getBulletRect().intersects(ufo))
        {

            musicPlayer->setVolume(50);
            musicPlayer->play();
            xcord = 0;
            show = false;
            bullet->setCollision(true);
            destroyed = true;
        }
    return destroyed;
}

void UFO::setShow(bool shown)
{
    this->show = shown;
}

bool UFO::getShow()
{
    return this->show;
}
