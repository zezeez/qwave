#include "fileoperate.h"
#include <QDebug>
#include <QDateTime>
#include <regex>
#include <QRegularExpression>

FileOperate::FileOperate()
{

}

void FileOperate::loadFile(QList<QPointF> &readdata)
{
    QString path=tr("./").toLocal8Bit();
    
    QString fileName=QFileDialog::getOpenFileName(this,tr("打开"),path,tr("文本文件(.txt)"));
    
    if(!fileName.isEmpty()) {
        QFile file;
        //QByteArray readData;
        
        file.setFileName(fileName);

        if(!file.open(QIODevice::ReadOnly|QIODevice::Text)) {
            QMessageBox::warning(this,tr("错误"),tr("文件打开错误：")+file.errorString(),QMessageBox::Ok);
        }
        else {
            QTextStream inData(&file);
            qreal px,py;
            while(!inData.atEnd()) {
                inData>>px;
                inData.seek(inData.pos()+1);
                inData>>py;
                readdata.append(QPointF(px,py));
            }
            file.close();
        }
    }

}

void FileOperate::saveFile(QList<QPointF> &vola,QList<QPointF> &stre,QList<QPointF> &weae)  //保存为文件
{
    QString path=tr("./").toLocal8Bit(),saveName;
    //QString dataSave;

    //QString fileName=QFileDialog::getSaveFileName(this,"另存为...",path,"文本文件(.txt)");
    //QFileDialog suffix;
    //suffix.setDefaultSuffix("txt");
    QString fileName=QFileDialog::getExistingDirectory(this,tr("另存为..."),tr("文本文件(.txt)"));

    if(!fileName.isNull()) {
        QFile file;
        QByteArray dataSave;

        QStringList lst=QDateTime::currentDateTime().toString().split(tr(" "));   //获取当前时间作为文件名
        fileName+=(tr("/")+lst[4]+lst[1].left(2)+lst[2]+lst[3].left(2)+lst[3].mid(3,2)+lst[3].mid(6,2)).toLocal8Bit();
        saveName=fileName+tr("volatoge").toLocal8Bit()+tr(".txt").toLocal8Bit();
        file.setFileName(saveName);

        //保存电压值
        if(!file.open(QIODevice::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this,tr("错误"),tr("文件打开错误：")+file.errorString(),QMessageBox::Abort);
            return;
        }
        else {
            QTextStream outData(&file);
            for(auto i:vola) {
                dataSave.append(QByteArray::number(i.x()));
                dataSave.append(":");
                dataSave.append(QByteArray::number(i.y(),'g',2));
                dataSave.append(" ");
                //array.append()
            }
            outData<<dataSave;
            //outData.atEnd();
            file.close();
        }

        //保存强电流值
        saveName=fileName+tr("strongelectric").toLocal8Bit()+tr(".txt").toLocal8Bit();
        file.setFileName(saveName);

        if(!file.open(QIODevice::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this,tr("错误"),tr("文件打开错误：")+file.errorString(),QMessageBox::Abort);
            return;
        }
        else {
            QTextStream outData(&file);
            for(auto i:stre) {
                dataSave.append(QByteArray::number(i.x()));
                dataSave.append(":");
                dataSave.append(QByteArray::number(i.y(),'g',2));
                dataSave.append(" ");
                //array.append()
            }
            outData<<dataSave;
            //outData.atEnd();
            file.close();
        }

        //保存弱电流值
        saveName=fileName+tr("weakelectric").toLocal8Bit()+tr(".txt").toLocal8Bit();
        file.setFileName(saveName);

        if(!file.open(QIODevice::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this,tr("错误"),tr("文件打开错误：")+file.errorString(),QMessageBox::Abort);
            return;
        }
        else {
            QTextStream outData(&file);
            for(auto i:weae) {
                dataSave.append(QByteArray::number(i.x()));
                dataSave.append(":");
                dataSave.append(QByteArray::number(i.y(),'g',2));
                dataSave.append(" ");
                //array.append()
            }
            outData<<dataSave;
            //outData.atEnd();
            file.close();
        }
    }
}

FileOperate::~FileOperate()
{

}
