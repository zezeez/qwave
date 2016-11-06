#include "writevincdata.h"

QTextStream &operator<<(QTextStream &,const vincData &);

WriteVinCData::WriteVinCData(QObject *parent) : QObject(parent)
{
    fileName=tr("");
    writeCount=0;
}

qint32 WriteVinCData::prepareToWrite(QString pathname)
{
    if(!pathname.isNull()) {
        fileName=pathname+tr("vinc.txt").toLocal8Bit();
        vincFile.setFileName(fileName);
        if(!vincFile.open(QIODevice::WriteOnly | QFile::Text)) {
            QMessageBox::warning(nullptr,tr("警告"),tr("打开文件%1时遇到错误:%2").arg(pathname).arg(vincFile.errorString()),QMessageBox::Ok);
            return -1;
        }
        outData.setDevice(&vincFile);
    }
    else
        return 1;
    return 0;
}

quint32 WriteVinCData::savevincFile(QList<vincData> &data)
{
    QList<vincData>::const_iterator it;
    for(it=data.cbegin();it!=data.cend();it++)
        outData<<*it;
    writeCount=data.size();
    data.erase(data.begin(),data.end());
    return writeCount;
}

void WriteVinCData::closeFile()
{
    vincFile.close();
}

QTextStream &operator<<(QTextStream &out,const vincData &data)
{
    quint8 i;
    for(i=0;i<64;i++)
        out<<data.vinc0[i]<<" ";
    for(i=0;i<64;i++)
        out<<data.vinc1[i]<<" ";
    for(i=0;i<64;i++)
        out<<data.vinc2[i]<<" ";
    for(i=0;i<64;i++)
        out<<data.vinc3[i]<<" ";
    return out;
}
