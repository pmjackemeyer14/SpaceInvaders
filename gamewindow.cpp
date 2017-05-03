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
#include <QMediaPlayer>
#include <QTime>

GameWindow::GameWindow(QWidget *parent) : QWidget(parent)
{
    playerScore = 0;
    timesUpdated = 0;
    bulletSound = new QMediaPlayer();
    bulletSound->setMedia(QUrl::fromLocalFile("../SpaceInvaders/shoot.wav"));
    paused = false;
    shotFired = false;
    bullet_timer = new QTimer();
    ship_timer = new QTimer();
    alien_timer = new QTimer();
    alienBulletTimer = new QTimer();
    generateUFO_timer = new QTimer();
    update_UFOTimer = new  QTimer();
    milliseconds = new QTimer();
    connect(alien_timer,SIGNAL(timeout()),this,SLOT(updateAlienCoordinates()));
    connect(bullet_timer,SIGNAL(timeout()),this,SLOT(updateBulletCoordinates()));
    connect(ship_timer,SIGNAL(timeout()),this,SLOT(updateShipCoordinates()));
    connect(alienBulletTimer,SIGNAL(timeout()),this,SLOT(updateAlienBulletCoordinates()));
    connect(generateUFO_timer,SIGNAL(timeout()),this,SLOT(generateUFO()));
    connect(update_UFOTimer,SIGNAL(timeout()),this,SLOT(updateUFOCoordinates()));
    connect(milliseconds,SIGNAL(timeout()),this,SLOT(incrementSecondsElapsed()));
    milliseconds->start();
    alien_timer->start();
    alienBulletTimer->start();
    generateUFO_timer->start();
    ship_timer->start();
    milliseconds->setInterval(1000);
    alien_timer->setInterval(2000);
    ship_timer->setInterval(30);
    bullet_timer->setInterval(50);
    alienBulletTimer->setInterval(50);
    generateUFO_timer->setInterval(10000);
    update_UFOTimer->setInterval(200);
    bullet = new Bullet(this);
    ufo = new UFO(this,bullet);
    ufo->setShow(false);
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
    ufo->drawUFO(*paint);
    aliens->drawAlien(*paint);
    alienBullet->drawAlienBullets(*paint);
    ship->drawShip(*paint);
    barrier->DrawBarriers(*paint);
    if(shotFired)
    {
        bullet->drawBullet(*paint);
    }
    QString score = "Score: ";
    QString str = "Time Elapsed: ";
    QTime n(0, 0, 0,0);
    QTime t;
    int secs = timesUpdated;
    t = n.addSecs(secs);
    QString time = t.toString("hh:mm:ss");
    str.append(time);
    QString num = num.number(playerScore);
    score.append(num);
    QPen penHText(textColor);
    paint->setPen(penHText);
    paint->drawText(this->width()-80,20,score);
    paint->drawText(25,20,str);

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

    if(ev->key() == Qt::Key_P)
    {
        if(paused)
        {
            alien_timer->start();
            ship_timer->start();
            bullet_timer->start();
            alienBulletTimer->start();
            paused = false;
        }else
        {
            alien_timer->stop();
            ship_timer->stop();
            bullet_timer->stop();
            alienBulletTimer->stop();
            paused = true;
        }
    }

    if(ev->key() == Qt::Key_Space)
    {
        if(bullet->getBulletDestroyed())
        {
            bulletSound->setVolume(50);
            bulletSound->play();
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
    bool ufoDestoyed = ufo->checkForCollisions();
    if(bullet->getBulletYCord()<20 || bullet->getBulletCollision())
    {
        if(shipIndex>=0 && shipIndex <11)
        {
            playerScore+=100;
        }else if(shipIndex>=11 && shipIndex < 33)
        {
            playerScore+=25;
        }else if(shipIndex>=33 && shipIndex < 55)
        {
            playerScore+=10;
        }else if(ufoDestoyed)
        {
            playerScore+=500;
        }
        //bullet->setCollision(false);
        bullet_timer->stop();
        shotFired = false;
    }
    bullet->updateCoordinates();
    this->update();
}

void GameWindow::updateShipCoordinates()
{

    if(ship->getGameOver())
    {
        QMediaPlayer *musicPlayer = new QMediaPlayer();
        musicPlayer->setMedia(QUrl::fromLocalFile("../SpaceInvaders/explosion.wav"));
        musicPlayer->setVolume(50);
        musicPlayer->play();
        bool ok;
        alien_timer->stop();
        ship_timer->stop();
        bullet_timer->stop();
        alienBulletTimer->stop();
        generateUFO_timer->stop();
        update_UFOTimer->stop();
        milliseconds->stop();
        QMessageBox mBox;
        mBox.setText("GAME OVER");
        mBox.exec();
        QInputDialog d(this);
        d.setLabelText("ENTER NAME:");
        d.setStyleSheet("background-color: white;");
        d.exec();
        QString name = d.textValue();
        qDebug()<<"NAME: "<<name;
        updateHighScores(name);
        this->close();
    }
    ship->checkForCollisions();
    ship->updateCoordinates();
    bullet->setShipXCord(ship->getShipXCord());
    this->update();
}

void GameWindow::updateAlienCoordinates()
{
    if(aliens->getGameOver())
    {
        QMediaPlayer *musicPlayer = new QMediaPlayer();
        musicPlayer->setMedia(QUrl::fromLocalFile("../SpaceInvaders/explosion.wav"));
        musicPlayer->setVolume(50);
        musicPlayer->play();
        bool ok;
        alien_timer->stop();
        ship_timer->stop();
        bullet_timer->stop();
        alienBulletTimer->stop();
        generateUFO_timer->stop();
        update_UFOTimer->stop();
        milliseconds->stop();
        QMessageBox mBox;
        mBox.setText("GAME OVER");
        mBox.exec();
        QInputDialog d(this);
        d.setLabelText("ENTER NAME:");
        d.setStyleSheet("background-color: white;");
        d.exec();
        QString name = d.textValue();
        updateHighScores(name);
        this->close();
    }
    int numDestroyed = aliens->getNumDestroyed();
    if(numDestroyed >= 15 && numDestroyed < 33)
    {
        alien_timer->setInterval(1000);
    }else if(numDestroyed >= 33 && numDestroyed < 44)
    {
        alien_timer->setInterval(500);
    }else if(numDestroyed >= 44 && numDestroyed < 55)
    {
        alien_timer->setInterval(200);
    }else if(numDestroyed == 55)
    {
        playerScore+=(10000/timesUpdated);
        QMediaPlayer* musicPlayer = new QMediaPlayer();
        musicPlayer->setMedia(QUrl::fromLocalFile("../SpaceInvaders/TaDa.wav"));
        musicPlayer->setVolume(50);
        musicPlayer->play();
        bool ok;
        alien_timer->stop();
        ship_timer->stop();
        bullet_timer->stop();
        alienBulletTimer->stop();
        generateUFO_timer->stop();
        update_UFOTimer->stop();
        milliseconds->stop();
        QMessageBox mBox;
        mBox.setText("CONGRATS! YOU WON!");
        mBox.exec();
        QInputDialog d(this);
        d.setLabelText("ENTER NAME:");
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
        aliens->generateNewNumber();
        alienBullet->setBulletCoordinates(aliens->getAlienBulletX(),aliens->getAlienBulletY());
    }
    this->update();
}

void GameWindow::generateUFO()
{
    ufo->setShow(true);
    update_UFOTimer->start();
}

void GameWindow::updateUFOCoordinates()
{

    if(ufo->getShow())
    {
        ufo->updateCoordinates();
    }else
    {
        update_UFOTimer->stop();
    }
}

void GameWindow::incrementSecondsElapsed()
{
    timesUpdated++;
}



