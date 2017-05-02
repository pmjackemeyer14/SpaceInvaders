#include "alien.h"
#include <QDebug>
#include <QPainter>
#include <QMessageBox>
#include <ctime>
#include <QMediaPlayer>


Alien::Alien(QWidget *parent, Bullet *bullet):parent(parent),bullet(bullet)
{
    srand( time(0));

    alien3 = new QImage("../SpaceInvaders/alien4.png");
    *alien3 = alien3->scaled(30,30);
    alien2 = new QImage("../SpaceInvaders/alien2.png");
    *alien2 = alien2->scaled(30,30);
    alien1 = new QImage("../SpaceInvaders/alien1.png");
    *alien1 = alien1->scaled(30,30);
    musicPlayer = new QMediaPlayer();
    musicPlayerExplosion = new QMediaPlayer();
    musicPlayer->setMedia(QUrl::fromLocalFile("../SpaceInvaders/fastinvader1.wav"));
    musicPlayerExplosion->setMedia(QUrl::fromLocalFile("../SpaceInvaders/invaderkilled.wav"));
    numberDestroyed = 0;
    max = 50;
    phase = 0;
    alienIndex = rand()%11+44;
    alienDirection = 2;
    gameOver = false;
    int xtemp = 0;
    int ytemp = 60;
    boundBox_xcord = 0;
    boundBox_ycord = 40;
    boundingBox.setCoords(0,40,430,220);
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
         aliens[i].setCoords(xcord[i],ycord[i],xcord[i]+30,ycord[i]-30);
    }

}

void Alien::drawAlien(QPainter &paint)
{
    QColor hardAlienColor = QColor(230,230,23);
    QColor mediumAlienColor = QColor(205,0,205);
    QColor easyAlienColor = QColor(205,0,120);
    boundingBox.setCoords(boundBox_xcord,boundBox_ycord,boundBox_xcord+430,boundBox_ycord+180);
    paint.drawRect(boundingBox);
    //paint.fillRect(boundingBox,hardAlienColor);
    for(int i = 0; i<55;i++)
    {
        if(alienDestroyed[i] == 1)
        {
            continue;
        }
        else
        {
                aliens[i].setCoords(xcord[i],ycord[i],xcord[i]+30,ycord[i]-30);
                paint.drawRect(aliens[i]);
                //paint.fillRect(aliens[i],hardAlienColor);
                if(i < 11)
                {
                    paint.drawImage(xcord[i],ycord[i]-30,*alien3);
                    //paint.fillRect(aliens[i],hardAlienColor);
                }else if(i >= 11 && i<33)
                {
                    //paint.fillRect(aliens[i],mediumAlienColor);
                    paint.drawImage(xcord[i],ycord[i]-30,*alien1);
                }else{
                    //paint.fillRect(aliens[i],easyAlienColor);
                    paint.drawImage(xcord[i],ycord[i]-30,*alien2);
                }


        }

    }
}

void Alien::updateCoordindates()
{
    if(phase == 0)
    {
         musicPlayer->setMedia(QUrl::fromLocalFile("../SpaceInvaders/fastinvader1.wav"));
    }else if(phase == 1)
    {
         musicPlayer->setMedia(QUrl::fromLocalFile("../SpaceInvaders/fastinvader2.wav"));
    }else if(phase == 2)
    {
         musicPlayer->setMedia(QUrl::fromLocalFile("../SpaceInvaders/fastinvader3.wav"));
    }else if(phase == 3)
    {
         musicPlayer->setMedia(QUrl::fromLocalFile("../SpaceInvaders/fastinvader4.wav"));
    }
    musicPlayer->setVolume(50);
    musicPlayer->play();

    phase++;
    if(phase > 3)
    {
        phase = 0;
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
                       ycord[i]+=10;
                    }
                }
                boundBox_ycord+=10;
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
                       xcord[i]+=10;

                    }
                }
             boundBox_xcord+=10;
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
                       ycord[i]+=10;
                    }
                }
                boundBox_ycord += 10;
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
                       xcord[i]-=10;

                    }
                }
                boundBox_xcord -= 10;
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

int Alien::checkforCollisions()
{
    int indexOfShipdestroyed = -1;
    for(int i = 0; i<55; i++)
    {
        if(alienDestroyed[i] == 1)
        {
            continue;
        }
        if(bullet->getBulletRect().intersects(aliens[i]))
        {

            musicPlayerExplosion->setVolume(50);
            musicPlayerExplosion->play();
            indexOfShipdestroyed = i;
            numberDestroyed++;
            alienDestroyed[i] = 1;
            xcord[i] = 0;
            ycord[i] = 0;
            bullet->setCollision(true);
        }
    }
    return indexOfShipdestroyed;
}

bool Alien::getGameOver()
{
    return this->gameOver;
}

int Alien::getAlienBulletX()
{
    int count = 0;
    if(max >= 44 && max < 55)
    {
        alienIndex = rand()%11+44;
        while(alienDestroyed[alienIndex] == 1 && count < 12)
        {
            alienIndex = rand()%11+44;
            if(count>=11)
            {
                alienIndex = rand()%11+33;
            }
            count++;
        }

    }else if(max >=33 && max < 44)
    {
        alienIndex = rand()%11+33;
        while(alienDestroyed[alienIndex] == 1 && count < 12)
        {
            alienIndex = rand()%11+33;
            if(count>=11)
            {
                alienIndex = rand()%11+22;
            }
            count++;
        }
    }else if(max >= 22 && max < 33 )
    {
        alienIndex = rand()%11+22;
        while(alienDestroyed[alienIndex] == 1 && count < 12)
        {
            alienIndex = rand()%11+22;
            if(count>=11)
            {
                alienIndex = rand()%11+11;
            }
            count++;
        }
    }else if(max >= 11 && max < 22)
    {
        alienIndex = rand()%11+11;
        while(alienDestroyed[alienIndex] == 1 && count < 12)
        {
            alienIndex = rand()%11+11;
            if(count>=11)
            {
                alienIndex = rand()%11;
            }
            count++;
        }
    }else
    {
        alienIndex = rand()%11;
        while(alienDestroyed[alienIndex] == 1 && count < 12)
        {
            alienIndex = rand()%11;
            count++;
        }
    }

    return xcord[alienIndex];
}

int Alien::getAlienBulletY()
{

    return ycord[alienIndex];
}

int Alien::getNumDestroyed()
{
    return this->numberDestroyed;
}
