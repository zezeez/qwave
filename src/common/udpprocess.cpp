#include "udpprocess.h"

UdpProcess::UdpProcess(QUdpSocket *parent): QObject(parent)
{
    udpSocket=new QUdpSocket(this);
    QHostAddress address("127.0.0.1");
    udpSocket->bind(address,PORT);

    volaStatus=0;
    streStatus=0;
    weaeStatus=0;
    isSecondClick=1;
    isReading=false;
    isWriting=false;
    alreadyWriteBytes=0;

    senderAddress.setAddress("0.0.0.0");
    senderPort=0;
    sendData.tunel=0;
    sendData.startpos=(qint16)SENDSTARTPOS;
    sendData.endpos=(qint16)SENDENDPOS;

    for(int i=0;i<3;i++)
        readFileType[i]=false;

    connect(udpSocket,&QUdpSocket::readyRead,this,&UdpProcess::readPendingDatagram);
}

void UdpProcess::readPendingDatagram()
{
    while(udpSocket->hasPendingDatagrams()){
        recvData.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(recvData.data(),recvData.size(),&senderAddress,&senderPort);

        //emit updateClientInfo(senderAddress.toString(),senderPort);
        processDatagram();
    }
}

void UdpProcess::addPoint(QList<QPointF> &vola, QList<QPointF> &stre, QList<QPointF> &weae)
{
    static double step=0;
    quint32 psize=points.size();
    if(!points.isEmpty() && MAXCOUNT<=psize) {  //从网络接口读
        for(unsigned int i=0;i<MAXCOUNT;i++) {
            vola.push_back(QPointF(step+MAXAXIS,points.first().curvola));
            stre.push_back(QPointF(step+MAXAXIS,points.first().curstre));
            weae.push_back(QPointF(step+MAXAXIS,points.first().curweae));
            points.removeFirst();
            step+=0.01;
        }
    }
    else if(isReading) {  //从文件读
        qint32 val=readFile.loadFile(readData,readFileType,MAXCOUNT);
        if(val==-1)
            isReading=false;
        else if(val==1)
            readFinished();
        quint32 rsize=readData.size();
        //qDebug()<<rsize;
        //qDebug()<<readFileType[0]<<" "<<readFileType[1]<<" "<<readFileType[2]<<endl;
        if(MAXCOUNT<=rsize && readFileType[0]) {
                for(unsigned int i=0;i<MAXCOUNT;i++) {
                    vola.push_back(QPointF(step+MAXAXIS,readData.first().vola[volaStatus]));
                    stre.push_back(QPointF(step+MAXAXIS,readData.first().vola[volaStatus]));
                    weae.push_back(QPointF(step+MAXAXIS,readData.first().vola[volaStatus]));
                    //qDebug()<<"("<<step<<","<<readData.first().vola[volaStatus]<<")";
                    readData.removeFirst();

                    step+=0.01;
                }
                //qDebug()<<"control reach here"<<endl;
        }
        else if(MAXCOUNT<=rsize && readFileType[1]) {
                for(unsigned int i=0;i<MAXCOUNT;i++) {
                    stre.push_back(QPointF(step+MAXAXIS,readData.first().stre[streStatus]));
                    readData.removeFirst();

                    step+=0.01;
                }
        }
        else if(MAXCOUNT<=rsize && readFileType[2]) {
                for(unsigned int i=0;i<MAXCOUNT;i++) {
                    weae.push_back(QPointF(step+MAXAXIS,readData.first().weae[weaeStatus]));
                    readData.removeFirst();

                    step+=0.01;
                }
        }
    }
}

void UdpProcess::processDatagram()
{
    lock.lock();
    QDataStream dsIn(&recvData,QIODevice::ReadWrite);

    if(dsIn.status()!=QDataStream::Ok) {
        QMessageBox::warning(NULL,tr("警告"),tr("读取数据包出错：%1").arg(dsIn.status()));
        return;
    }
    while(!dsIn.atEnd())
        dsIn>>*this;
    recvData.clear();
    lock.unlock();
}

void UdpProcess::timerEvent(QTimerEvent *event)
{
    /*if(event->timerId()==readTimer) {
        quint32 val=readFile.loadFile(readData,MAXCOUNT);
        qDebug()<<readData.size()<<endl;
       if(val==1)
           readFinished();
       else if(val==-1) {
           killTimer(readTimer);
           isReading=false;
       }
    }*/
    //else if(event->timerId()==writeTimer && !writeData.isEmpty()){
    if(alreadyWriteBytes<MAXWRITEBYTES) {
        alreadyWriteBytes+=writeFile.saveFile(writeData);
        vinc.readyWrite();
    }
    else {
        isSecondClick++;
        writeFinished();
    }
}

void UdpProcess::parseDataFormat()
{

}

void UdpProcess::selectVolAData(int index)  //更新选择状态
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

/*void UdpProcess::setcrcCheck()
{
    //qint8 data=sendData.intr;
    //qint8 crc=0x0b; 1011,crc多项式
    //data<<2;  左移k-1位，k为多项式位数
    //因为数据比较简单，所以直接计算crc校验码，多项式为0x0b,00001011
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
}*/

void UdpProcess::forLoadFile()
{
    qint32 reval=readFile.prepareToRead(readFileType);
    if(reval==-1) {
        QMessageBox::warning(nullptr,tr("警告"),tr("读操作未就绪"),QMessageBox::Ok);
        return;
    }
    else if(reval==1) {
        return;
    }
    else if(reval==2) {
        QMessageBox::warning(nullptr,tr("警告"),tr("不可识别的文件格式"),QMessageBox::Ok);
        return;
    }

    isReading=true;
    //readTimer=startTimer(1000);
}

void UdpProcess::forSaveFile()  //保存文件
{
    if(points.isEmpty()) {
        QMessageBox::warning(nullptr,tr("警告"),tr("当前没有数据可以保存"),QMessageBox::Ok);
        return;
    }

    isSecondClick++;
    if(isSecondClick%2==0)
        isSecondClick=0;

    if(isSecondClick) {
        writeFinished();
    }
    else {
        int val=writeFile.prepareToWrite();
        writeFile.setPathName(pathName);
        vinc.setPathName(pathName);
        if(val==-1) {
            QMessageBox::warning(nullptr,tr("警告"),tr("写操作未就绪"),QMessageBox::Ok);
            return;
        }
        else if(val==1)
            return;
        writeTimer=startTimer(1000);
        //vinc.setStatusForWrite(pathName);
        emit resetSaveFileButtonStatus(1);
        isWriting=true;
    }

}

void UdpProcess::readFinished()
{
    //killTimer(readTimer);
    //readFile.closeFile();
    readFile.readClose(readFileType);
    isReading=false;
    QMessageBox::information(nullptr,tr("通知"),tr("文件读已完成"),QMessageBox::Ok);
}

void UdpProcess::writeFinished()
{
    alreadyWriteBytes=0;
    killTimer(writeTimer);
    isWriting=false;
    writeFileFlag=false;
    writeFile.closeFile();
    vinc.writeFinished();
    emit resetSaveFileButtonStatus(0);
    QMessageBox::information(nullptr,tr("通知"),tr("文件写已完成"),QMessageBox::Ok);
}

void UdpProcess::sendIntr(int index)  //发送指令
{
    //static bool flag=true;
    //if(flag) {
        //udpSocket->bind(senderAddress,senderPort);  //发送数据需要绑定，且只需绑定一次
        //flag=false;
    //}
    sendData.intr=(quint8)(index);
    qDebug()<<sendData.intr<<" "<<sendData.tunel<<endl;
    sendData.intr=(sendData.intr<<4) | sendData.tunel;
    //setcrcCheck();

    QByteArray waitSend;
    QDataStream dsOut(&waitSend,QIODevice::ReadWrite);
    dsOut<<*this;
    udpSocket->writeDatagram(waitSend,senderAddress,senderPort);
    qDebug()<<senderAddress<<" "<<senderPort<<" "<<sendData.intr<<endl;
}

void UdpProcess::curTunelChange(int index)
{
    sendData.tunel=static_cast<quint8>(index);
}

QDataStream &operator>>(QDataStream &in,UdpProcess &data)
{
    quint8 i,ttlout,lowbit;
    in>>data.start;
    for(i=0;i<4;i++) {
        in>>data.format.weae[i];
        data.format.weae[i]&=0x0fff;
    }

    for(i=0;i<8;i++) {
        in>>data.format.stre[i];
        data.format.stre[i]&=0x0fff;
    }

    for(i=0;i<16;i++) {
        in>>data.format.vola[i];
        data.format.vola[i]&=0x0fff;
    }

    in>>ttlout;
    for(i=0;i<4;i++) {
        lowbit=ttlout-(ttlout>>1);
        ttlout>>=1;
        data.format.ttlout[i]=lowbit;
    }
    in>>data.end;
    data.cursel.curvola=data.format.vola[data.volaStatus];
    data.cursel.curstre=data.format.stre[data.streStatus];
    data.cursel.curweae=data.format.weae[data.weaeStatus];
    data.points.append(data.cursel);
    if(data.isWriting)
        data.writeData.append(data.format);
    return in;
}

QDataStream &operator<<(QDataStream &out,const UdpProcess &data)
{
    out<<data.sendData.startpos;
    out<<data.sendData.intr;
    out<<data.sendData.endpos;

    return out;
}

UdpProcess::~UdpProcess()
{
    delete udpSocket;
}
