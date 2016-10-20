#ifndef UdpProcess_H
#define UdpProcess_H

#include <QObject>
#include <QtNetwork>
#include <QDebug>
#include <QList>
#include <QPointF>
#include <QDataStream>
#include <QMessageBox>
#include <QMutex>

#define PORT 49223
#define STARTPOS 0xFD55
#define ENDPOS 0x55FF
#define MAXSTEP 10
#define MAXAXIS 100

struct dataFormat {
    quint16 vola[16],stre[8],weae[4],vinc[4];
    quint8 ttlout[4];
};

struct Intr {
    quint16 startpos,endpos;
    quint8 intr;
    //QString context;
    quint8 crc;
};

class UdpProcess: public QObject
{
    Q_OBJECT
public:
    UdpProcess(QUdpSocket *parent=0);
    ~UdpProcess();
public:
    void initSocket();
    void parseDataFormat();
    void addPoint(QList<QPointF> &,QList<QPointF> &,QList<QPointF> &);
    void selectVolAData(int);
    void selectStrEData(int);
    void selectWeaEData(int);
private:
    void processDatagram();
    void setcrcCheck();
public slots:
    void sendIntr(int);
private slots:
    void readPendingDatagram();
private:
    QUdpSocket *udpSocket;
    QByteArray recvData;
    QList<dataFormat> list;     //数据缓存
    QList<QPointF> points;

    dataFormat format;
    Intr sendData;
    quint8 dataLength;
    quint16 start,end;      //帧头和帧尾
    int volaStatus,streStatus,weaeStatus;       //选择数据帧

    QHostAddress senderAddress;
    quint16 senderPort;

    QMutex lock;
private:
    friend QDataStream &operator<<(QDataStream &,const UdpProcess &);
    friend QDataStream &operator>>(QDataStream &,UdpProcess &);
};

#endif // UdpProcess_H
