#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "alien.h"
#include "bullet.h"
#include "playership.h"
#include "alienbullets.h"
#include "barriers.h"

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

private:
    bool shotFired;
    bool paused;
    Alien* aliens;
    AlienBullets* alienBullet;
    Bullet* bullet;
    Barriers* barrier;
    PlayerShip* ship;
    QTimer* bullet_timer;
    QTimer* ship_timer;
    QTimer* alien_timer;
    QTimer* collision_timer;
    QTimer* alienBulletTimer;

    int playerScore;
};

#endif // GAMEWINDOW_H
