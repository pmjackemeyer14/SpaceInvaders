#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent* e);
    void keyPressEvent(QKeyEvent* ev);
    void keyReleaseEvent(QKeyEvent* ev);
    void fireShot(QPainter *paint);
    void drawPlayerShip(QPainter *paint);
    void drawEnemyShips(QPainter * paint);

signals:

public slots:

private slots:
    void updateBulletCoordinates();
    void updateShipCoordinates();
    void updateAlienCoordinates();

private:
    bool shotFired;
    bool firstFire;
    bool bulletDestroyed;
    int direction;// 0 = Stop, 1 = Left, 2 = Right
    int alienDirection;// 1 = Left, 2 = Right
    int bullet_xcord;
    int bullet_ycord;
    int ship_xcord;
    int alien_xcord[55];
    int alien_ycord[55];
    QTimer* bullet_timer;
    QTimer* ship_timer;
    QTimer* alien_timer;
};

#endif // GAMEWINDOW_H
