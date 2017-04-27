#include "alien.h"
#include <QDebug>
#include <QPainter>


Alien::Alien(QWidget *parent):parent(parent)
{
    alienDirection = 2;
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
    QColor bbcolor = QColor(0,0,0);
    boundingBox.setCoords(boundBox_xcord,boundBox_ycord,boundBox_xcord+420,boundBox_ycord+180);
    paint.drawRect(boundingBox);
    paint.fillRect(boundingBox,bbcolor);
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
        int max = 0;
        for(int i = 0; i<55; i++)
        {
         if(ycord[i] > max)
         {
             max = ycord[i];
         }
        }

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
}
