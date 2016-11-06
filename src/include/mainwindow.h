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
#include <QUdpSocket>
#include <QCategoryAxis>
#include "udpprocess.h"
#include "fileoperate.h"
#include "udpvincdata.h"

QT_CHARTS_USE_NAMESPACE

#define MAXDRAWPOINTS 2000
#define MAXREMOVEPOINTS 1000
#define MAXSTEP 1
#define MAXAXISX 10
#define MAXAXISY 20

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
public slots:
    //void setClientInfo(QString,quint16);
    void resetSaveFileButtonStatus(int);
private slots:
    void comboBoxChoseChanged(int);
    void comboBox2ChoseChanged(int);
    void comboBox3ChoseChanged(int);
    void onDraw();      //绘制点坐标
    void sendIntr(int);
    void curTunelChange(int);
    //void loadFile(QList<QPointF> &);
    //void saveFileNow();
    //void loadFileNow();
private:
    QThread udpDatagram,recvVinc;
protected:
    struct showType{
        QChart *cView;
        QList<QPointF> axiData;
    };
    showType volatoge,strongelectric,weakelectric;      //电压 强电流 弱电流

    //UdpVinCData vinc;
    QUdpSocket *udpSocket;
    UdpProcess *udpData;
    QLineSeries *vline,*sline,*wline;
    QValueAxis *vaxisY,*saxisY,*waxisY;
    QCategoryAxis *vaxisX,*saxisX,*waxisX;
    FileOperate file;
    Ui::MainWindow *ui;
//private:
    //friend QDataStream &operator<<(QDataStream &,const MainWindow &);
};

#endif // MAINWINDOW_H
