#include "../include/fileoperate.h"
#include <QDebug>
#include <QDateTime>
#include <regex>
#include <QRegularExpression>

FileOperate::FileOperate()
{
    pathName=tr("");
    writeCount=0;
}

qint32 FileOperate::prepareToRead(bool *filetype)
{
    fileName=QFileDialog::getOpenFileName(nullptr,tr("打开"),pathName,tr("文本文件(*.txt)"));

    if(fileName.isNull())
        return 1;

    file.setFileName(fileName);

    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(nullptr,tr("警告"),tr("打开文件%1时遇到错误:%2").arg(pathName).arg(file.errorString()),QMessageBox::Ok);
        return -1;
    }
    inData.setDevice(&file);
    //inData.setFieldWidth(2);

    //inData.setFieldAlignment(QTextStream::AlignLeft);
    /*switch(fileName) {
    case "volatoge.txt":
        filetype[0]=true;
        break;
    case "strelectric.txt":
        filetype[1]=true;
        break;
    case "weakelectric.txt":
        filetype[2]=true;
        break;
    default:
        return 2;
    }*/
    if(fileName.endsWith("volatoge.txt"))
        filetype[0]=true;
    else if(fileName.endsWith("strongelectric.txt"))
        filetype[1]=true;
    else if(fileName.endsWith("weakelectric.txt"))
        filetype[2]=true;
    else
        return 2;

    //qDebug()<<filetype[0]<<" "<<filetype[1]<<" "<<filetype[2]<<endl;
    return 0;
}

qint32 FileOperate::loadFile(QList<dataFormat> &readdata, bool *filetype, quint32 count)
{
    quint32 i,j;
    dataFormat pack;
    char space;
    if(filetype[0]) {
        for(i=0;i<count;i++) {
            for(j=0;j<16 && !inData.atEnd();j++)
                inData>>pack.vola[j]>>space;
            readdata.append(pack);
            if(inData.atEnd())
                return 1;
        }
    }
    else if(filetype[1]) {
        for(i=0;i<count;i++) {
            for(j=0;j<8 && !inData.atEnd();j++)
                inData>>pack.stre[j]>>space;
            readdata.append(pack);
            if(inData.atEnd())
                return 1;
        }
    }
    else if(filetype[2]) {
        for(i=0;i<count;i++) {
            for(j=0;j<4 && !inData.atEnd();j++)
                inData>>pack.weae[j]>>space;
            readdata.append(pack);
            if(inData.atEnd())
                return 1;
        }
    }
    return 0;
}

qint32 FileOperate::prepareToWrite()
{
    pathName=QFileDialog::getExistingDirectory(nullptr,tr("保存到..."),pathName);

    if(!pathName.isNull()) {
        //QStringList lst=QDateTime::currentDateTime().toString().split(tr(" "));   //获取当前时间作为文件名
        //pathName+=(tr("/")+lst[4]+lst[1].left(2)+lst[2]+lst[3].left(2)+lst[3].mid(3,2)+lst[3].mid(6,2)).toLocal8Bit();

        pathName+=tr("/")+QDateTime::currentDateTime().toString("yyyyMMddHHmmss").toLocal8Bit();
        qDebug()<<pathName<<endl;
        fileName=pathName+tr("volatoge").toLocal8Bit()+tr(".txt").toLocal8Bit();
        volaFile.setFileName(fileName);
        if(!volaFile.open(QIODevice::WriteOnly | QFile::Text)) {
            QMessageBox::warning(nullptr,tr("警告"),tr("打开文件%1时遇到错误:%2").arg(pathName).arg(file.errorString()),QMessageBox::Ok);
            return -1;
        }
        volaData.setDevice(&volaFile);
        //volaData.setFieldWidth(2);
        //volaData.setFieldAlignment(QTextStream::AlignLeft);

        fileName=pathName+tr("strongelectric").toLocal8Bit()+tr(".txt").toLocal8Bit();
        streFile.setFileName(fileName);
        if(!streFile.open(QIODevice::WriteOnly | QFile::Text | QIODevice::Append)) {
            QMessageBox::warning(nullptr,tr("警告"),tr("打开文件%1时遇到错误:%2").arg(pathName).arg(file.errorString()),QMessageBox::Ok);
            return -1;
        }
        streData.setDevice(&streFile);
        //streData.setFieldWidth(2);
        //streData.setFieldAlignment(QTextStream::AlignLeft);

        fileName=pathName+tr("weakelectric").toLocal8Bit()+tr(".txt").toLocal8Bit();
        weaeFile.setFileName(fileName);
        if(!weaeFile.open(QIODevice::WriteOnly | QFile::Text | QIODevice::Append)) {
           QMessageBox::warning(nullptr,tr("警告"),tr("打开文件%1时遇到错误:%2").arg(pathName).arg(file.errorString()),QMessageBox::Ok);
           return -1;
        }
        weaeData.setDevice(&weaeFile);
        //weaeData.setFieldWidth(2);
        //weaeData.setFieldAlignment(QTextStream::AlignLeft);

        fileName=pathName+tr("ttl").toLocal8Bit()+tr(".txt").toLocal8Bit();
        ttlFile.setFileName(fileName);
        if(!ttlFile.open(QIODevice::WriteOnly | QFile::Text | QIODevice::Append)) {
            QMessageBox::warning(nullptr,tr("警告"),tr("打开文件%1时遇到错误:%2").arg(pathName).arg(file.errorString()),QMessageBox::Ok);
            return -1;
        }
        ttlData.setDevice(&ttlFile);
        //ttlData.setFieldWidth(2);
        //ttlData.setFieldAlignment(QTextStream::AlignLeft);
    }
    else
        return 1;
    return 0;
}

qint32 FileOperate::saveFile(QList<dataFormat> &savedata)
{
    quint8 i;
    QList<dataFormat>::const_iterator it;
    for(it=savedata.cbegin();it!=savedata.cend();it++)  {
        for(i=0;i<16;i++) {
            volaData<<it->vola[i]<<" ";//<<qSetFieldWidth(10);
            //qDebug()<<it->vola[i]<<" ";
        }
        //qDebug()<<endl;
        for(i=0;i<8;i++)
            streData<<it->stre[i]<<" ";//<<qSetFieldWidth(10);
        for(i=0;i<4;i++) {
            weaeData<<it->weae[i]<<" ";//<<qSetFieldWidth(2);
            ttlData<<it->ttlout[i]<<" ";//<<qSetFieldWidth(2);
        }
    }
    writeCount=savedata.size();
    savedata.erase(savedata.begin(),savedata.end());
    return writeCount;
}

void FileOperate::setPathName(QString &pathname)
{
    pathname=pathName;
}

void FileOperate::closeFile()
{
    volaFile.close();
    streFile.close();
    weaeFile.close();
    ttlFile.close();
}

void FileOperate::readClose(bool *file)
{
    /*file[0]?volaFile.close(),0:1;
    file[1]?streFile.close(),0:1;
    file[2]?weaeFile.close(),0:1;*/
    if(file[0] && volaData.atEnd()) {
        volaFile.close();
        file[0]=false;
    }
    if(file[1] && streData.atEnd()) {
        streFile.close();
        file[1]=false;
    }
    if(file[2] && weaeData.atEnd()) {
        weaeFile.close();
        file[2]=false;
    }
}

FileOperate::~FileOperate()
{

}
