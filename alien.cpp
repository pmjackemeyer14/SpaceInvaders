#include "alien.h"
#include <QDebug>
#include <QPainter>
#include <QMessageBox>
#include <ctime>


Alien::Alien(QWidget *parent, Bullet *bullet):parent(parent),bullet(bullet)
{
    srand( time(0));
    max = 50;
    alienIndex = rand()%11+44;
    alienDirection = 2;
    gameOver = false;
    int xtemp = 0;
    int ytemp = 60;
    boundBox_xcord = 0;
    boundBox_ycord = 40;
    boundingBox.setCoords(0,40,420,220);
    for(int i = 0;i<55;i++)
    {
        alienDestroyed[i] = 0;
        if(i<11)
        {
           ycord[i] = ytemp;
        }else if(i >= 11 && i < 22)
        {
           ycord[i] = ytemp+40;
        }else if(i >= 22 && i < 33)
        {
           ycord[i] = ytemp+80;
        }else if(i >= 33 && i < 44)
        {
           ycord[i] = ytemp+120;
        }else
        {
           ycord[i] = ytemp+160;
        }
    }
    for(int i = 0;i<11;i++)
    {
        int k = i;
        for(k; k < 55;k+=11)
        {
            xcord[k] = xtemp;
        }
        xtemp+=40;
    }
    for(int i = 0; i < 55;i++)
    {
         aliens[i].setCoords(xcord[i],ycord[i],xcord[i]+20,ycord[i]-20);
    }

}

void Alien::drawAlien(QPainter &paint)
{
    QColor alienColor = QColor(230,230,23);
    boundingBox.setCoords(boundBox_xcord,boundBox_ycord,boundBox_xcord+420,boundBox_ycord+180);
    paint.drawRect(boundingBox);
    for(int i = 0; i<55;i++)
    {
        if(alienDestroyed[i] == 1)
        {
            continue;
        }
        else
        {
            for(int i = 0; i <55; i++)
            {
                aliens[i].setCoords(xcord[i],ycord[i],xcord[i]+20,ycord[i]-20);
                paint.drawRect(aliens[i]);
                paint.fillRect(aliens[i],alienColor);
            }
        }

    }
}

void Alien::updateCoordindates()
{


        if(alienDirection == 2)
        {

            if(boundingBox.right() >= parent->width())
            {
                for(int i=0; i<55; i++)
                {
                    if(alienDestroyed[i] == 1)
                    {
                        continue;
                    }else
                    {
                       ycord[i]+=40;
                    }
                }
                boundBox_ycord+=40;
                alienDirection = 1;
            }else
            {
                for(int i=0; i<55; i++)
                {
                    if(alienDestroyed[i] == 1)
                    {
                        continue;
                    }else
                    {
                       xcord[i]+=40;

                    }
                }
             boundBox_xcord+=40;
            }
        }else if(alienDirection == 1)
        {
            if(boundingBox.left() <= 10)
            {
                for(int i=0; i<55; i++)
                {
                    if(alienDestroyed[i] == 1)
                    {
                        continue;
                    }else
                    {
                       ycord[i]+=40;
                    }
                }
                boundBox_ycord += 40;
                alienDirection = 2;
            }else
            {
                for(int i=0; i<55; i++)
                {
                    if(alienDestroyed[i] == 1)
                    {
                        continue;
                    }else
                    {
                       xcord[i]-=40;

                    }
                }
                boundBox_xcord -= 40;
            }
        }

        int max = 0;
        for(int i = 0; i<55; i++)
        {
         if(ycord[i] > max)
         {
             max = ycord[i];
             this->max = i;
         }
        }
        if(max >= parent->height()-20)
        {
            gameOver = true;
        }
}

void Alien::checkforCollisions()
{
    for(int i = 0; i<55; i++)
    {
        if(bullet->getBulletRect().intersects(aliens[i]))
        {
            alienDestroyed[i] = 1;
            xcord[i] = 0;
            ycord[i] = 0;
            bullet->setCollision(true);
        }
    }
}

bool Alien::getGameOver()
{
    return this->gameOver;
}

int Alien::getAlienBulletX()
{
    if(max >= 44 && max < 55)
    {
        alienIndex = rand()%11+44;
        while(alienDestroyed[alienIndex] == 1)
        {
            alienIndex = rand()%11+44;
        }

    }else if(max >=33 && max < 44)
    {
        alienIndex = rand()%11+33;
        while(alienDestroyed[alienIndex] == 1)
        {
            alienIndex = rand()%11+33;
        }
    }else if(max >= 22 && max < 33)
    {
        alienIndex = rand()%11+22;
        while(alienDestroyed[alienIndex] == 1)
        {
            alienIndex = rand()%11+22;
        }
    }else if(max >= 11 && max < 22)
    {
        alienIndex = rand()%11+11;
        while(alienDestroyed[alienIndex] == 1)
        {
            alienIndex = rand()%11+11;
        }
    }else
    {
        alienIndex = rand()%11;
        while(alienDestroyed[alienIndex] == 1)
        {
            alienIndex = rand()%11;
        }
    }

    return xcord[alienIndex];
}

int Alien::getAlienBulletY()
{

    return ycord[alienIndex];
}
