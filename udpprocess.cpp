#include "udpprocess.h"
#include <time.h>
#include <random>

UdpProcess::UdpProcess(QUdpSocket *parent): QObject(parent)
{
    udpSocket=new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any,PORT);

    volaStatus=0;
    streStatus=0;
    weaeStatus=0;

    sendData.startpos=(qint16)0xfaa5;
    sendData.endpos=(qint16)0xf55f;

    connect(udpSocket,&QUdpSocket::readyRead,this,&UdpProcess::readPendingDatagram);
}

void UdpProcess::readPendingDatagram()
{
    while(udpSocket->hasPendingDatagrams()){
        recvData.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(recvData.data(),recvData.size(),&senderAddress,&senderPort);

        processDatagram();
    }
}

void UdpProcess::addPoint(QList<QPointF> &vola, QList<QPointF> &stre, QList<QPointF> &weae)
{
    /*
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(0,10);
    QList<QPointF> lst;
    quint32 x=10;
    //static double data[10000];
    for(int i=0;i<100000;i++) {
        //data[i]=u(e);
        lst.push_back(QPointF(x,u(e)));
        x++;
    }
    static int count=3000;
    for(int i=count;i<count+300;i++) {
        vola.push_back(lst[i]);
    }

    count+=300;
    */
    //quint32 x=1;
    static unsigned int count=0;
    static double step=0;
    dataCurSelected pack;
    quint16 v,s,w;
    quint32 size=points.size();
    if(!points.isEmpty() && count+MAXCOUNT<=size) {
        for(unsigned int i=count;i<count+MAXCOUNT;i++) {
            pack=points[i];
            v=pack.curvola;
            s=pack.curstre;
            w=pack.curweae;

            vola.push_back(QPointF(step+MAXAXIS,v));
            stre.push_back(QPointF(step+MAXAXIS,s));
            weae.push_back(QPointF(step+MAXAXIS,w));
            step+=0.01;
        }
        count+=MAXCOUNT;
    }
}

void UdpProcess::processDatagram()
{
    /*if((recvData>>start)==STARTPOS)
        parseDataFormat();
    else
        processLastData();*/
    lock.lock();
    QDataStream dsIn(&recvData,QIODevice::ReadWrite);

    if(dsIn.status()!=QDataStream::Ok) {
        QMessageBox::warning(NULL,tr("警告"),tr("读取数据包出错：%1").arg(dsIn.status()));
        return;
    }
    //qDebug()<<"recive data"<<endl;
    //qDebug()<<"size:"<<recvData.size()<<endl;
    while(!dsIn.atEnd())
        dsIn>>*this;
    lock.unlock();
}

void UdpProcess::parseDataFormat()
{

}

void UdpProcess::selectVolAData(int index)
{
    volaStatus=index;
}

void UdpProcess::selectStrEData(int index)
{
    streStatus=index;
}

void UdpProcess::selectWeaEData(int index)
{
    weaeStatus=index;
}

void UdpProcess::sendIntr(int index)
{
    sendData.intr=(quint8)index;
    setcrcCheck();

    QByteArray waitSend;
    QDataStream dsOut(&waitSend,QIODevice::ReadWrite);
    dsOut<<*this;
    udpSocket->writeDatagram(waitSend,senderAddress,senderPort);
    qDebug()<<senderAddress<<" "<<senderPort<<endl;
}

void UdpProcess::setcrcCheck()
{
    //qint8 data=sendData.intr;
    //qint8 crc=0x0b; 1011,crc多项式
    //data<<2;  左移k-1位，k为多项式位数
    //因为数据比较简单，所以直接计算crc校验码，多项式为0x0b,1011
    //data<<3;
    switch(sendData.intr) {
    case 0: sendData.crc=(quint8)0x0;
        break;
    case 1: sendData.crc=(quint8)0x3;
        break;
    case 2: sendData.crc=(quint8)0x6;
        break;
    case 3: sendData.crc=(quint8)0x5;
        break;
    default:
        break;
    }
}

QDataStream &operator<<(QDataStream &out,const UdpProcess &data)
{
    out<<data.sendData.startpos;

    out<<data.sendData.intr;
    out<<data.sendData.crc;

    out<<data.sendData.endpos;

    return out;
}

QDataStream &operator>>(QDataStream &in,UdpProcess &data)
{
    quint8 i;
    in>>data.start;
    in>>data.dataLength;
    for(i=0;i<data.dataLength/sizeof(quint16);i++)
        in>>data.format.weae[i];

    in>>data.dataLength;
    for(i=0;i<data.dataLength/sizeof(quint16);i++)
        in>>data.format.stre[i];

    in>>data.dataLength;
    for(i=0;i<data.dataLength/sizeof(quint16);i++)
        in>>data.format.vola[i];

    in>>data.dataLength;
    for(i=0;i<data.dataLength/sizeof(quint16);i++)
        in>>data.format.vinc[i];

    for(i=0;i<4;i++) {
        in>>data.dataLength;
        in>>data.format.ttlout[i];
    }
    in>>data.end;
    data.cursel.curvola=data.format.vola[data.volaStatus];
    data.cursel.curstre=data.format.stre[data.streStatus];
    data.cursel.curweae=data.format.weae[data.weaeStatus];
    data.points.append(data.cursel);
    //data.list.append(data.format);
    return in;
}

UdpProcess::~UdpProcess()
{
    delete udpSocket;
}
