#ifndef UDPHANDLE_H
#define UDPHANDLE_H

#include <QObject>
#include <QtNetwork>

class Udphandle: public QUdpSocket
{
    Q_OBJECT
public:
    Udphandle(QUdpSocket *parent=0);
    void initSocket();
    void parseDataFormat();
    ~Udphandle();
private slots:
    void processpendingDatagram();
private:
    QUdpSocket *recv;
    QByteArray data;
};

#endif // UDPHANDLE_H
