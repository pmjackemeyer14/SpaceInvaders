#include "highscore.h"
#include "ui_highscore.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QTableWidget>
#include <QHeaderView>

HighScore::HighScore(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HighScore)
{
    ui->setupUi(this);
    //Display top 10 scores
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(2);
    QVector <QTableWidgetItem*> names;
    QVector <QTableWidgetItem*> scores;
    //Load high scores from JSON file
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
    for(int i = 0; i < nameArray.size(); i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText(nameArray.at(i).toString());
        names.push_back(item);
    }
    for(int i = 0; i < scoreArray.size(); i++)
    {
        QTableWidgetItem* item2 = new QTableWidgetItem();
        int x;
        x = scoreArray.at(i).toInt();
        item2->setData(Qt::DisplayRole, x);
        scores.push_back(item2);
    }
    QStringList headers;
    headers << "Name" << "Score";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    //Add elements to table
    for(int i = 0; i < names.size();i++)
    {
        ui->tableWidget->setItem(i,0,names.at(i));
    }
    for(int i =0; i < scores.size();i++)
    {
        ui->tableWidget->setItem(i,1,scores.at(i));
    }
    ui->tableWidget->setSortingEnabled(true);
    Qt::SortOrder order = Qt::DescendingOrder;
    ui->tableWidget->sortItems(1,order);
    this->update();
}

HighScore::~HighScore()
{
    delete ui;
}




