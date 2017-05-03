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
    phase = 0;
    alienIndex = rand()%10;
    alienDirection = 2;
    gameOver = false;
    int xtemp = 0;
    int ytemp = 100;
    boundBox_xcord = 0;
    boundBox_ycord = 80;
    boundingBox.setCoords(0,80,430,260);
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
        max[i] = 50;
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
    boundingBox.setCoords(boundBox_xcord,boundBox_ycord,boundBox_xcord+430,boundBox_ycord+180);
    paint.drawRect(boundingBox);
    for(int i = 0; i<55;i++)
    {
        if(alienDestroyed[i] == 1)
        {
            continue;//IF alien has been destoyred don't draw it
        }
        else
        {
                aliens[i].setCoords(xcord[i],ycord[i],xcord[i]+30,ycord[i]-30);
                paint.drawRect(aliens[i]);
                if(i < 11)
                {
                    paint.drawImage(xcord[i],ycord[i]-30,*alien3);
                }else if(i >= 11 && i<33)
                {
                    paint.drawImage(xcord[i],ycord[i]-30,*alien1);
                }else
                {
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
         }
        }
        //THIS LOOP FINDS THE LOWEST (CLOSEST TO PLAYER) ALIEN IN EACH COLUMN
        int maxColumn1 = 0;
        for(int j = 0; j < 11; j++)
        {
            int i = j;
            int upperBound = 44+j;
            for(i; i <= upperBound;i+=11)
            {
                if(ycord[i] > maxColumn1)
                {
                    this->max[j] = i;
                }
            }
        }

        if(max >= parent->height()-40)
        {
            gameOver = true;
        }
}

void Alien::generateNewNumber()
{
    alienIndex = rand()%10;
    int count = 0;
    //IF THE XCORD IS 0, THE ALIEN HAS BEEN DESTROYED SO GENERATE A NEW RANDOM NUM
    while(xcord[max[alienIndex]] == 0 && count < 100 )
    {
        alienIndex = rand()%10;
        count++;
    }

}

int Alien::checkforCollisions()
{
    int indexOfShipdestroyed = -1;
    for(int i = 0; i<55; i++)
    {
        if(alienDestroyed[i] == 1)
        {
            continue;//DONT NEED TO CHECK ALREADY DESTROYED ALIENS
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
    int alienx = 0;

    switch(alienIndex)
    {
        case 0:  alienx = xcord[max[0]];
        break;
        case 1:  alienx = xcord[max[1]];
        break;
        case 2:  alienx = xcord[max[2]];
        break;
        case 3:  alienx = xcord[max[3]];
        break;
        case 4:  alienx = xcord[max[4]];
        break;
        case 5:  alienx = xcord[max[5]];
        break;
        case 6:  alienx = xcord[max[6]];
        break;
        case 7:  alienx = xcord[max[7]];
        break;
        case 8:  alienx = xcord[max[8]];
        break;
        case 9:  alienx = xcord[max[9]];
        break;
        case 10: alienx = xcord[max[10]];
    }

    return alienx;
}

int Alien::getAlienBulletY()
{
    int alieny = 0;
    switch(alienIndex)
    {
        case 0:  alieny = ycord[max[0]];
        break;
        case 1:  alieny = ycord[max[1]];
        break;
        case 2:  alieny = ycord[max[2]];
        break;
        case 3:  alieny = ycord[max[3]];
        break;
        case 4:  alieny = ycord[max[4]];
        break;
        case 5:  alieny = ycord[max[5]];
        break;
        case 6:  alieny = ycord[max[6]];
        break;
        case 7:  alieny = ycord[max[7]];
        break;
        case 8:  alieny = ycord[max[8]];
        break;
        case 9:  alieny = ycord[max[9]];
        break;
        case 10: alieny = ycord[max[10]];
    }
    return alieny;
}

int Alien::getNumDestroyed()
{
    return this->numberDestroyed;
}
