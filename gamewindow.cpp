#include "gamewindow.h"
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>
#include "alien.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QInputDialog>
#include <QDir>

GameWindow::GameWindow(QWidget *parent) : QWidget(parent)
{
    playerScore = 0;
    shotFired = false;
    bullet_timer = new QTimer();
    ship_timer = new QTimer();
    alien_timer = new QTimer();
    alienBulletTimer = new QTimer();
    connect(alien_timer,SIGNAL(timeout()),this,SLOT(updateAlienCoordinates()));
    connect(bullet_timer,SIGNAL(timeout()),this,SLOT(updateBulletCoordinates()));
    connect(ship_timer,SIGNAL(timeout()),this,SLOT(updateShipCoordinates()));
    connect(alienBulletTimer,SIGNAL(timeout()),this,SLOT(updateAlienBulletCoordinates()));
    alien_timer->start();
    alien_timer->setInterval(2000);
    ship_timer->start();
    ship_timer->setInterval(30);
    bullet_timer->setInterval(50);
    alienBulletTimer->start();
    alienBulletTimer->setInterval(50);
    bullet = new Bullet(this);
    aliens = new Alien(this,bullet);
    alienBullet = new AlienBullets(this);
    alienBullet->setBulletCoordinates(aliens->getAlienBulletX(),aliens->getAlienBulletY());
    ship = new PlayerShip(this,alienBullet);
    barrier = new Barriers(this,bullet,alienBullet);
}

void GameWindow::paintEvent(QPaintEvent *e)
{
    QColor textColor = QColor(255,0,0);
    QPainter* paint = new QPainter(this);
    aliens->drawAlien(*paint);
    alienBullet->drawAlienBullets(*paint);
    ship->drawShip(*paint);
    barrier->DrawBarriers(*paint);
    if(shotFired)
    {
        bullet->drawBullet(*paint);
    }
    QString score = "Score: ";
    QString num = num.number(playerScore);
    score.append(num);
    QPen penHText(textColor);
    paint->setPen(penHText);
    paint->drawText(25,20,score);

}

void GameWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_Left)
    {
        ship->setDirection(1);

    }else if(ev->key()==Qt::Key_Right)
    {
        ship->setDirection(2);
    }

    if(ev->key() == Qt::Key_Space)
    {
        if(bullet->getBulletDestroyed())
        {
            shotFired = true;
            bullet_timer->start();
        }
    }

}

void GameWindow::keyReleaseEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Right || ev->key() == Qt::Key_Left)
    {
        ship->setDirection(0);
    }
}

void GameWindow::updateHighScores(QString name)
{
    QFile HighScoreSaveFile("../SpaceInvaders/SpaceInvaders_HighScores.json");
    if(!HighScoreSaveFile.open(QIODevice::ReadOnly))
    {
        qWarning("Could not open last High Score save file");
        this->close();
        return;
    }
    QByteArray hsSave = HighScoreSaveFile.readAll();
    QJsonDocument hsDoc = QJsonDocument::fromJson(hsSave);
    QJsonObject hsObj = hsDoc.object();
    QJsonArray nameArray = hsObj["name"].toArray();
    QJsonArray scoreArray = hsObj["score"].toArray();
    int size = nameArray.size();
    int index;
    int min = INT_MAX;
    HighScoreSaveFile.remove();
    QFile newHSsaveFile("../SpaceInvaders/SpaceInvaders_HighScores.json");
    if(!newHSsaveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Could not open last High Score save file");
        this->close();
        return;
    }
    //Find lowest value of the 10
    for(int i = 0; i < size; i++)
    {
        if(scoreArray.at(i).toInt()< min)
        {
            min = scoreArray.at(i).toInt();
            index = i;
        }
    }
    //If there are less than 10 high scores add score to high score list
    if(size < 10)
    {
        nameArray.insert(index,name);
        scoreArray.insert(index,playerScore);
    }
    else
    {
        //If high score is greater than lowest value on high score list it is added to the high score list
        if(playerScore > min)
        {
            nameArray.removeAt(index);
            scoreArray.removeAt(index);
            nameArray.insert(index,name);
            scoreArray.insert(index,playerScore);
        }
    }
    //Write the JSON file
    hsObj["name"] = nameArray;
    hsObj["score"] = scoreArray;
    QJsonDocument nhsDoc;
    nhsDoc.setObject(hsObj);
    newHSsaveFile.write(nhsDoc.toJson());
    newHSsaveFile.flush();
    newHSsaveFile.close();
}


void GameWindow::updateBulletCoordinates()
{
    int shipIndex = aliens->checkforCollisions();
    barrier->CheckforCollisions();
    if(bullet->getBulletYCord()<20 || bullet->getBulletCollision() )
    {
        //alienBullet->setBulletCoordinates(aliens->getAlienBulletX(),aliens->getAlienBulletY());
        if(shipIndex>=0 && shipIndex <11)
        {
            playerScore+=100;
        }else if(shipIndex>=11 && shipIndex < 33)
        {
            playerScore+=25;
        }else if(shipIndex>=33 && shipIndex < 55)
        {
            playerScore+=10;
        }
        bullet_timer->stop();
        shotFired = false;
    }
    bullet->updateCoordinates();
    this->update();
}

void GameWindow::updateShipCoordinates()
{
    ship->checkForCollisions();
    if(ship->getGameOver())
    {
        bool ok;
        alien_timer->stop();
        ship_timer->stop();
        bullet_timer->stop();
        alienBulletTimer->stop();
        QMessageBox mBox;
        mBox.setText("GAME OVER");
        mBox.exec();
        QInputDialog d(this);
        d.setStyleSheet("background-color: white;");
        d.exec();
        QString name = d.textValue();
        qDebug()<<"NAME: "<<name;
        updateHighScores(name);
        this->close();
    }
    ship->updateCoordinates();
    bullet->setShipXCord(ship->getShipXCord());
    this->update();
}

void GameWindow::updateAlienCoordinates()
{
    if(aliens->getGameOver())
    {
        bool ok;
        alien_timer->stop();
        ship_timer->stop();
        bullet_timer->stop();
        alienBulletTimer->stop();
        QMessageBox mBox;
        mBox.setText("GAME OVER");
        mBox.exec();
        QInputDialog d(this);
        d.setStyleSheet("background-color: white;");
        d.exec();
        QString name = d.textValue();
        updateHighScores(name);
        this->close();
    }
    aliens->checkforCollisions();
    aliens->updateCoordindates();
    this->update();
}

void GameWindow::collisionCheck()
{
    //aliens->checkforCollisions();
    //this->update();
}

void GameWindow::updateAlienBulletCoordinates()
{
    ship->checkForCollisions();
    barrier->CheckforCollisions();
    alienBullet->updateCoordinates();
    if(alienBullet->getBulletDestroyed())
    {
        alienBullet->setBulletCoordinates(aliens->getAlienBulletX(),aliens->getAlienBulletY());
    }
    this->update();
}



