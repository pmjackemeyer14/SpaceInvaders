#include "widget.h"
#include "ui_widget.h"
#include "gamewindow.h"
#include "highscore.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->StartGame->setStyleSheet("background-color: grey;color : yellow;");
    ui->Exit->setStyleSheet("background-color: grey;color : yellow;");
    ui->HighScores->setStyleSheet("background-color: grey;color : yellow;");
    QPixmap* mp = new QPixmap("../SpaceInvaders/SPACE_INVADERS.gif");
    ui->label->setPixmap(*mp);
    ui->label->setScaledContents(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_Exit_clicked()
{
    this->close();
}

void Widget::on_HighScores_clicked()
{
    HighScore* hs = new HighScore();
    hs->setAttribute(Qt::WA_DeleteOnClose);
    hs->setStyleSheet("background-color: black;");
    hs->show();

}

void Widget::on_StartGame_clicked()
{
    GameWindow* gw = new GameWindow();
    gw->setMinimumHeight(480);
    gw->setMaximumHeight(480);
    gw->setMinimumWidth(660);
    gw->setMaximumWidth(660);
    gw->setStyleSheet("background-color: black;");
    gw->show();
    gw->setAttribute(Qt::WA_DeleteOnClose);
}
