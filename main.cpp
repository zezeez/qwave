#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //connect(close,SIGNAL(clicked()),this,SLOT(Qt::quit()));

    return a.exec();
}
