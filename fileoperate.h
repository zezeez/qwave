#ifndef FILEOPERATE_H
#define FILEOPERATE_H
#include <QIODevice>

class FileOperate//: public QIODevice
{
    //Q_OBJECT
public:
    FileOperate();
    void getFileName();
    ~FileOperate();
//private slots:
    void openFile();
    void saveFile();
private:
    bool isWriteable;
    bool isReadable;
    QString filename;
    QString operation;
    QString mode;
    qint64 size;
};

#endif // FILEOPERATE_H
