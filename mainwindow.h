#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QTimerEvent>
#include <QByteArray>
#include <QCloseEvent>
#include <QtCharts>
#include <QComboBox>
#include <QList>
#include <QThread>
#include "udpprocess.h"
#include "fileoperate.h"

QT_CHARTS_USE_NAMESPACE

#define HISTORY 30
#define MAXDRAWPOINTS 610
#define MAXREMOVEPOINTS 600
#define MAXSTEP 10
#define MAXAXISX 100
#define MAXAXISY 10

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(qreal width,qreal height,QObject *parent=0);
    ~MainWindow();
private:
    void initAxis();
    void initCharts();
    void setCharts();
    void customUi();
protected:
    void timerEvent(QTimerEvent *);
    void showWave();
signals:
    void readyForWrite(QList<QPointF> &,QList<QPointF> &,QList<QPointF> &);
    //void readyForDraw(QList<QPointF> &/*,QLineSeries &,MainWindow &*/);
    void readyForRead(QList<QPointF> &);
private slots:
    void comboBoxChoseChanged(int);
    void comboBox2ChoseChanged(int);
    void comboBox3ChoseChanged(int);
    void onDraw();      //绘制点坐标
    //void loadFile(QList<QPointF> &);
    void saveFileNow();
    void loadFileNow();
private:
    QThread udpDatagram;
protected:
    struct showType{
        QChart *cView;
        QList<QPointF> axiData;
    };
    showType volatoge,strongelectric,weakelectric;      //电压 强电流 弱电流
    //int dataCount;
    //int timeData[HISTORY];
    UdpProcess udpData;
    QLineSeries *line1,*line2,*line3;
    QValueAxis *vaxisX,*vaxisY,*saxisX,*saxisY,*waxisX,*waxisY;
    FileOperate file;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
