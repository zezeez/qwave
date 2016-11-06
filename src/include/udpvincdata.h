#ifndef UDPVINCDATA_H
#define UDPVINCDATA_H
#include <QDataStream>
#include <QUdpSocket>
#include <QMessageBox>
#include <QList>
#include <QFile>
#include "mystruct.h"
#include "writevincdata.h"

#define PORT 5000

class UdpVinCData : public QObject
{
    Q_OBJECT
public:
    explicit UdpVinCData(QObject *parent = 0);
    ~UdpVinCData();
public:
    //qint32 loadvincFile();
    void setPathName(QString);
    //void setStatusForWrite(QString);
    void readyWrite();
    void writeFinished();
private:
    vincData vinc;
    WriteVinCData writevinc;

    QList<vincData> list;
    QUdpSocket *socket;
    QByteArray recvData;

    QString pathName;
private:
    void readPendingDatagram();
    void processDatagram();

    friend QDataStream &operator>>(QDataStream &,UdpVinCData &);
    //friend QDataStream &operator<<(QDataStream &,vincData &);
};

#endif // UDPVINCDATA_H
