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

class FileOperate: public QWidget
{
    Q_OBJECT
public:
    FileOperate();
    //void getFileName();

    ~FileOperate();
//private slots:
    //void openFile();

public slots:
    void loadFile(QList<QPointF> &);
    void saveFile(QList<QPointF> &vola, QList<QPointF> &stre, QList<QPointF> &weae);
private:
    bool isWriteable;
    bool isReadable;
    //QString filename;
    QString operation;
    QString mode;
    qint64 size;
};

#endif // FILEOPERATE_H
