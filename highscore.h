#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <QWidget>
#include <QTableWidget>

namespace Ui {
class HighScore;
}

class HighScore : public QWidget
{
    Q_OBJECT

public:
    explicit HighScore(QWidget *parent = 0);
    ~HighScore();


private:
    Ui::HighScore *ui;

};

#endif // HIGHSCORE_H
