#include "gamewindow.h"
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>

GameWindow::GameWindow(QWidget *parent) : QWidget(parent)
{

    direction = 0;
    alienDirection = 2;
    bulletDestroyed = true;
    shotFired = false;
    firstFire = false;
    bullet_timer = new QTimer();
    ship_timer = new QTimer();
    alien_timer = new QTimer();
    connect(alien_timer,SIGNAL(timeout()),this,SLOT(updateAlienCoordinates()));
    connect(bullet_timer,SIGNAL(timeout()),this,SLOT(updateBulletCoordinates()));
    connect(ship_timer,SIGNAL(timeout()),this,SLOT(updateShipCoordinates()));
    alien_timer->start();
    alien_timer->setInterval(1000);
    ship_timer->start();
    ship_timer->setInterval(50);
    bullet_timer->setInterval(100);
    bullet_xcord = 0;
    bullet_ycord = this->height()-10;
    ship_xcord = this->width()/2;
    int xtemp = 0;
    int ytemp = 60;
    for(int i = 0;i<55;i++)
    {
        if(i<11)
        {
           alien_ycord[i] = ytemp;
        }else if(i >= 11 && i < 22)
        {
           alien_ycord[i] = ytemp+40;
        }else if(i >= 22 && i < 33)
        {
           alien_ycord[i] = ytemp+80;
        }else if(i >= 33 && i < 44)
        {
           alien_ycord[i] = ytemp+120;
        }else
        {
           alien_ycord[i] = ytemp+160;
        }

    }
    for(int i = 0;i<11;i++)
    {
        int k = i;
        for(k; k < 55;k+=11)
        {
            alien_xcord[k] = xtemp;
        }
        xtemp+=40;
    }


}

void GameWindow::paintEvent(QPaintEvent *e)
{
    QPainter* paint = new QPainter(this);
    drawPlayerShip(paint);
    drawEnemyShips(paint);
    if(shotFired)
    {
        fireShot(paint);
    }

}

void GameWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_Left)
    {
        direction = 1;

    }else if(ev->key()==Qt::Key_Right)
    {
        direction = 2;
    }

    if(ev->key() == Qt::Key_Space)
    {
        if(bulletDestroyed)
        {
            shotFired = true;
            firstFire = true;
            bullet_timer->start();
        }
    }

}

void GameWindow::keyReleaseEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Right || ev->key() == Qt::Key_Left)
    {
        direction = 0;
    }
}

void GameWindow::fireShot(QPainter* paint)
{
    QRect bullet;
    bulletDestroyed = false;
    QColor color2 = QColor(255,255,255);
    if(firstFire)
    {
        bullet_xcord = ship_xcord+10;
    }
    bullet.setCoords(bullet_xcord,bullet_ycord,bullet_xcord+10,bullet_ycord-10);
    paint->drawRect(bullet);
    paint->fillRect(bullet,color2);
}

void GameWindow::drawPlayerShip(QPainter *paint)
{
    QRect r;
    QColor color2 = QColor(76,230,23);
    r.setCoords(ship_xcord,this->height()-10,ship_xcord+20,this->height()-30);
    paint->drawRect(r);
    paint->fillRect(r,color2);
}

void GameWindow::drawEnemyShips(QPainter *paint)
{
    QRect r[55];
    QColor color3 = QColor(230,230,23);
    for(int i = 0; i<55;i++)
    {
        qDebug()<<"WIDTH: "<<this->width();
        r[i].setCoords(alien_xcord[i],alien_ycord[i],alien_xcord[i]+20,alien_ycord[i]-20);
        paint->drawRect(r[i]);
        paint->fillRect(r[i],color3);
    }

}

void GameWindow::updateBulletCoordinates()
{
    bullet_ycord-=10;
    if(bullet_ycord<0)
    {
        bulletDestroyed = true;
        bullet_timer->stop();
        shotFired = false;
        bullet_ycord = this->height()-10;
    }
    firstFire = false;
    this->update();
}

void GameWindow::updateShipCoordinates()
{
    if(direction == 1)
    {
        ship_xcord-=5;

    }else if(direction == 2)
    {
        ship_xcord+=5;
    }
    this->update();
}

void GameWindow::updateAlienCoordinates()
{
    if(alienDirection == 2)
    {
        if(alien_xcord[10]+40>=this->width())
        {
            for(int i=0; i<55; i++)
            {
                alien_ycord[i]+=40;
            }
            alienDirection = 1;
        }else if(alien_ycord[44]>=this->height()-30)
        {
            alien_timer->stop();
            QMessageBox m;
            m.setText("GAME OVER");
            m.exec();

        }else
        {
            for(int i=0; i<55; i++)
            {
                alien_xcord[i]+=40;
            }
        }

    }else if(alienDirection == 1)
    {
        if(alien_xcord[0]<=10)
        {
            for(int i=0; i<55; i++)
            {
                alien_ycord[i]+=40;
            }
            alienDirection = 2;
        }else if(alien_ycord[44]>=this->height()-30)
        {
            alien_timer->stop();
            QMessageBox m;
            m.setText("GAME OVER");
            m.exec();
        }else
        {
            for(int i=0; i<55; i++)
            {
                alien_xcord[i]-=40;
            }
        }
    }
    this->update();
}



