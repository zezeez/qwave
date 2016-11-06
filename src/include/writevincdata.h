#ifndef WRITEVINCDATA_H
#define WRITEVINCDATA_H

#include <QObject>
#include <QList>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include "mystruct.h"

class WriteVinCData : public QObject
{
    Q_OBJECT
public:
    explicit WriteVinCData(QObject *parent = 0);

public:
    quint32 savevincFile(QList<vincData>&);
    qint32 prepareToWrite(QString);
    void closeFile();
signals:

public slots:

//private:
    //friend QTextStream &operator<<(QTextStream&,const vincData&);
private:
    vincData vinc;
    quint32 writeCount;
    QString fileName;
    QFile vincFile;
    QTextStream outData;
};

#endif // WRITEVINCDATA_H
