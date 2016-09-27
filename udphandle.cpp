#include "udphandle.h"

Udphandle::Udphandle(QUdpSocket *parent): QUdpSocket(parent),recv(NULL), data(NULL)
{
}

void Udphandle::processpendingDatagram()
{
    while(recv->hasPendingDatagrams()){
        //QByteArray datagram;
        data.resize(recv->pendingDatagramSize());
        recv->readDatagram(data.data(),data.size());
        //ui->label->setText(datagram);
        //now handling the receive data
        //...
    }
}

void Udphandle::initSocket()
{
    recv=new QUdpSocket(this);
    recv->bind(QHostAddress::LocalHost,49162);
    //connect(recv,&QIODevice::readyRead(),this,&Udphandle::processpendingDatagram());
    connect(recv,SIGNAL(readyRead()),this,SLOT(processpendingDatagram()));
}

void Udphandle::parseDataFormat()
{

}

Udphandle::~Udphandle()
{
    delete recv;
}
