#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent* e);

signals:

public slots:
};

#endif // GAMEWINDOW_H
