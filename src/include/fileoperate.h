#ifndef FILEOPERATE_H
#define FILEOPERATE_H
#include <QIODevice>
#include <QList>
#include <QFileDialog>
#include <QMessageBox>
#include <QErrorMessage>
#include <QTextStream>
#include <QByteArray>
#include <QIODevice>
#include "mystruct.h"

class FileOperate: public QObject
{
    Q_OBJECT
public:
    FileOperate();
    //void getFileName();

    ~FileOperate();
//private slots:
    //void openFile();
public:
    void closeFile();
    void readClose(bool *);
    void setPathName(QString &);
signals:
    void userCanceled();
    void fileStatusNotReady();
public slots:
    qint32 loadFile(QList<dataFormat> &,bool *,quint32);
    qint32 saveFile(QList<dataFormat> &);
    qint32 prepareToRead(bool *);
    qint32 prepareToWrite();
private:
    //bool isWriteable;
    //bool isReadable;
    //QString filename;
    //QString operation;
    //QString mode;
    //qint64 size;
    QString pathName,fileName;
    quint32 writeCount;
    //QString volaName,streName,weaeName,ttlName;
    QFile volaFile,streFile,weaeFile,ttlFile,file;
    QTextStream volaData,streData,weaeData,ttlData,inData;
};

#endif // FILEOPERATE_H
