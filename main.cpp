#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setStyleSheet("background-color: black;");
    w.show();

    return a.exec();
}
