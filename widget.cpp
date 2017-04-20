#include "widget.h"
#include "ui_widget.h"
#include "gamewindow.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->StartGame->setStyleSheet("background-color: grey;color : yellow;");
    ui->Exit->setStyleSheet("background-color: grey;color : yellow;");
    ui->HighScores->setStyleSheet("background-color: grey;color : yellow;");

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

}

void Widget::on_StartGame_clicked()
{
    GameWindow* gw = new GameWindow();
    //Background = black or image
    gw->setStyleSheet("background-color: black;");
    gw->show();
    gw->setAttribute(Qt::WA_DeleteOnClose);
}
