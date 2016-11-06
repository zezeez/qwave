#include "udpvincdata.h"

UdpVinCData::UdpVinCData(QObject *parent): QObject(parent)
{

    socket=new QUdpSocket(this);
    QHostAddress address("192.168.1.101");
    socket->bind(address,PORT);
    connect(socket,&QUdpSocket::readyRead,this,&UdpVinCData::readPendingDatagram);
}

void UdpVinCData::readPendingDatagram()
{
    while(socket->hasPendingDatagrams()) {
        recvData.resize(socket->pendingDatagramSize());
        socket->readDatagram(recvData.data(),recvData.size());

        processDatagram();
    }
}

void UdpVinCData::processDatagram()
{
    QDataStream dsIn(&recvData,QIODevice::ReadWrite);

    if(dsIn.status()!=QDataStream::Ok) {
        QMessageBox::warning(nullptr,tr("读取数据包出错:"),tr("警告"),QMessageBox::Ok);
        return;
    }

    while(!dsIn.atEnd()) {
        dsIn>>*this;
        list.append(vinc);
    }
    recvData.clear();
}

void UdpVinCData::readyWrite()
{
    writevinc.savevincFile(list);
}

void UdpVinCData::setPathName(QString pathname)
{
    pathName=pathname;
    writevinc.prepareToWrite(pathName);
}

void UdpVinCData::writeFinished()
{
    writevinc.closeFile();
}

QDataStream &operator>>(QDataStream &in,UdpVinCData &data)
{
    int i;
    quint16 startpos,endpos;
    in>>startpos;
    for(i=0;i<64;i++) {
        in>>data.vinc.vinc0[i];
        //qDebug()<<data.vinc0[i]<<" ";
    }
    qDebug()<<endl;
    for(i=0;i<64;i++) {
        in>>data.vinc.vinc1[i];
        //qDebug()<<data.vinc1[i]<<" ";
    }
    for(i=0;i<64;i++) {
        in>>data.vinc.vinc2[i];
        //qDebug()<<data.vinc2[i]<<" ";
    }
    for(i=0;i<64;i++) {
        in>>data.vinc.vinc3[i];
        qDebug()<<data.vinc.vinc3[i]<<" ";
    }
    in>>endpos;
    return in;
}

UdpVinCData::~UdpVinCData()
{

}
