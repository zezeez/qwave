#ifndef UdpProcess_H
#define UdpProcess_H

//#include <QObject>
#include <QtNetwork>
#include <QDebug>
#include <QList>
#include <QPointF>
#include <QDataStream>
#include <QMessageBox>
#include <QMutex>
#include "mystruct.h"
#include "fileoperate.h"
#include "udpvincdata.h"

#define PORT 5000
#define MAXCOUNT 100
#define MAXAXIS 10
#define MAXWRITEBYTES 10240 //524288000 //500m 500*1024*1024byte
#define SENDSTARTPOS 0xfaa5
#define SENDENDPOS 0xf55f

/*struct dataFormat {
    quint16 vola[16],stre[8],weae[4];//,vinc[4];
    quint8 ttlout[4];
};*/

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
    //void setcrcCheck();
    void readFinished();
    void writeFinished();
signals:
    //void updateClientInfo(QString,quint16);
    void readyForRead(QList<dataFormat>&);
    void readyForWrite(QList<dataFormat>&);
    void resetSaveFileButtonStatus(int);
protected:
    void timerEvent(QTimerEvent *event);
public slots:
    void forLoadFile();
    void forSaveFile();
    void sendIntr(int);
    void curTunelChange(int);
private slots:
    void readPendingDatagram();
private:
    QUdpSocket *udpSocket;
    QByteArray recvData;
    //QList<dataFormat> list;     //数据缓存
    QList<dataFormat> readData,writeData;
    QList<dataCurSelected> points;

    dataFormat format;
    dataCurSelected cursel;

    quint8 dataLength;
    quint16 start,end;      //帧头和帧尾
    int volaStatus,streStatus,weaeStatus;       //选择数据帧

    QHostAddress senderAddress;
    quint16 senderPort;
    Intr sendData;

    bool isReading,isWriting,writeFileFlag,readFileFlage;
    quint8 isSecondClick;
    quint32 alreadyWriteBytes;
    FileOperate readFile,writeFile;

    QString pathName;

    UdpVinCData vinc;
    bool readFileType[3];
    int readTimer,writeTimer;
    QMutex lock;
private:
    friend QDataStream &operator<<(QDataStream &,const UdpProcess &);
    friend QDataStream &operator>>(QDataStream &,UdpProcess &);
};

#endif // UdpProcess_H
