#include "../include/mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QTextCodec *codec = QTextCodec::codecForName("utf-8");
    //QTextCodec::setCodecForLocale(codec);
    //QTextCodec::setCodecForCStrings(codec);
    //QTextCodec::setCodecForTr(codec);

    MainWindow w;
    w.setWindowTitle("实时监测");
    w.show();
    //connect(close,SIGNAL(clicked()),this,SLOT(Qt::quit()));

    return a.exec();
}
