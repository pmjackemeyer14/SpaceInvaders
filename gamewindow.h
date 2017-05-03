#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QMediaPlayer>
#include "alien.h"
#include "bullet.h"
#include "playership.h"
#include "alienbullets.h"
#include "barriers.h"
#include "ufo.h"

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent* e);
    void keyPressEvent(QKeyEvent* ev);
    void keyReleaseEvent(QKeyEvent* ev);
    void drawPlayerShip(QPainter *paint);
    void updateHighScores(QString name);

signals:

public slots:

private slots:
    void updateBulletCoordinates();
    void updateShipCoordinates();
    void updateAlienCoordinates();
    void collisionCheck();
    void updateAlienBulletCoordinates();
    void generateUFO();
    void updateUFOCoordinates();
    void incrementSecondsElapsed();

private:
    bool shotFired;
    bool paused;
    Alien* aliens;
    AlienBullets* alienBullet;
    Bullet* bullet;
    Barriers* barrier;
    PlayerShip* ship;
    UFO* ufo;
    QTimer* bullet_timer;
    QTimer* ship_timer;
    QTimer* alien_timer;
    QTimer* collision_timer;
    QTimer* alienBulletTimer;
    QTimer* generateUFO_timer;
    QTimer* update_UFOTimer;
    QTimer* milliseconds;
    QMediaPlayer* bulletSound;
    int timesUpdated;
    int playerScore;
};

#endif // GAMEWINDOW_H
