#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <QFileDialog>
#include <QMessageBox>
#include "udpprocess.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setBackgroundRole(QPalette::Dark);
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setFocusPolicy(Qt::StrongFocus);

    //QChart *chart;

    /*ui->lhLayout->addWidget(ui->label);
    ui->lhLayout->addWidget(ui->volatoge);
    ui->lhLayout->addWidget(ui->label_4);
    ui->lhLayout->addWidget(ui->label_2);
    ui->lhLayout->addWidget(ui->strongelectric);
    ui->lhLayout->addWidget(ui->label_5);
    ui->lhLayout->addWidget(ui->label_3);
    ui->lhLayout->addWidget(ui->weakelectric);
    ui->lhLayout->addWidget(ui->label_6);

    ui->rhLayout->addWidget(ui->label_7);
    ui->rhLayout->addWidget(ui->comboBox);
    ui->rhLayout->addWidget(ui->label_8);
    ui->rhLayout->addWidget(ui->comboBox_2);
    ui->rhLayout->addWidget(ui->label_9);
    ui->rhLayout->addWidget(ui->comboBox_3);

    ui->rhLayout->addWidget(ui->loadfile);
    ui->rhLayout->addWidget(ui->savefile);
    ui->rhLayout->addWidget(ui->close);

    ui->vLayout->addLayout(ui->lhLayout);
    ui->vLayout->addLayout(ui->rhLayout);*/


    //chart = new QChart();
    /*volatoge.cView = ui->volatoge;
    strongelectric.cView = ui->strongelectric;
    weakelectric.cView = ui->weakelectric;*/

    initCharts();
    initAxis();
    setCharts();
    customUi();
    //volatoge.cView->axisX()->setRange(1,10);
    //volatoge.cView->axisY()->setRange(1,10);

    //ui->volatoge->geometry();
    //ui->strongelectric->geometry();
    //ui->weakelectric->geometry();

    /*for(int i=0;i<10;i++) {
        line->append(i,sin(i));
    }*/
    /*QChart *chart=new QChart();
    chart->addSeries(line);
    chart->createDefaultAxes();
    ui->volatoge->setChart(chart);*/

    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxChoseChanged(int)));
    connect(ui->comboBox_2,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBox2ChoseChanged(int)));
    connect(ui->comboBox_3,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBox3ChoseChanged(int)));
    connect(ui->comboBox_4,SIGNAL(currentIndexChanged(int)),&udpData,SLOT(sendIntr(int)));
    connect(ui->loadfile,&QPushButton::clicked,this,&MainWindow::loadFileNow);
    connect(ui->savefile,&QPushButton::clicked,this,&MainWindow::saveFileNow);
    connect(this,&MainWindow::readyForWrite,&file,&FileOperate::saveFile);
    connect(this,&MainWindow::readyForRead,&file,&FileOperate::loadFile);
    connect(ui->close,SIGNAL(clicked(bool)),this,SLOT(close()));

    //chart = new QChart
    //connect(ui->close,&QPushButton::clicked,this,QCoreApplication::exit(0));
    //qRegisterMetaType<QList<QPointF>&>("QList<QPointF>&");

    //drawCurve *draw=new drawCurve;
    //UdpProcess *pcs=new UdpProcess;
    udpData.moveToThread(&udpDatagram);
    //connect(&udpDatagram,&QThread::finished,&udpData,&QObject::deleteLater);
    //connect(this,&MainWindow::readyForDraw,draw,&drawCurve::onDraw);
    //connect(draw,&drawCurve::readyDraw,this,&MainWindow::onDraw);
    udpDatagram.start();

    //for ( int i = 0; i < HISTORY; i++ )
        //timeData[HISTORY - 1 - i] = i;

    startTimer(1000);  //1 second
}

void MainWindow::initCharts()
{
    line1=new QLineSeries();
    line1->setPen(QPen(Qt::green,1,Qt::SolidLine));
    volatoge.cView = new QChart();
   // volatoge.cView->setAnimationOptions(QChart::SeriesAnimations);
    volatoge.cView->addSeries(line1);
    volatoge.cView->createDefaultAxes();



    line2=new QLineSeries();
    line2->setPen(QPen(Qt::red,1,Qt::SolidLine));
    strongelectric.cView = new QChart();
    //strongelectric.cView->setAnimationOptions(QChart::SeriesAnimations);  //展示动画效果
    strongelectric.cView->addSeries(line2);
    strongelectric.cView->createDefaultAxes();


    line3=new QLineSeries();
    line3->setPen(QPen(Qt::blue,1,Qt::SolidLine));
    weakelectric.cView = new QChart();
    //weakelectric.cView->setAnimationOptions(QChart::SeriesAnimations);
    weakelectric.cView->addSeries(line3);
    weakelectric.cView->createDefaultAxes();
}

void MainWindow::initAxis()
{
    vaxisX=new QValueAxis;
    vaxisX->setRange(1,MAXAXISX);
    vaxisX->setLabelFormat(tr("%d"));
    vaxisX->setTitleText(tr("时间/s"));
    vaxisX->setGridLineVisible(false);   //显示网格
    vaxisX->setMinorTickCount(4);
    vaxisX->setLabelsVisible(true);

    vaxisY=new QValueAxis;
    vaxisY->setRange(0,MAXAXISY);
    vaxisY->setTitleText(tr("电压/V"));
    vaxisY->setLabelFormat(tr("%.2f"));
    vaxisY->setGridLineVisible(false);

    saxisX=new QValueAxis;
    saxisX->setRange(1,MAXAXISX);
    saxisX->setLabelFormat(tr("%d"));
    saxisX->setTitleText(tr("时间/s"));
    saxisX->setGridLineVisible(false);
    saxisX->setMinorTickCount(4);
    saxisX->setLabelsVisible(true);

    saxisY=new QValueAxis;
    saxisY->setRange(0,MAXAXISY);
    saxisY->setTitleText(tr("强电流/A"));
    saxisY->setLabelFormat(tr("%.2f"));
    saxisY->setGridLineVisible(false);

    waxisX=new QValueAxis;
    waxisX->setRange(1,MAXAXISX);
    waxisX->setLabelFormat(tr("%d"));
    waxisX->setTitleText(tr("时间/s"));
    waxisX->setGridLineVisible(false);
    waxisX->setMinorTickCount(4);
    waxisX->setLabelsVisible(true);

    waxisY=new QValueAxis;
    waxisY->setRange(0,MAXAXISY);
    waxisY->setTitleText(tr("弱电流/A"));
    waxisY->setLabelFormat(tr("%.2f"));
    waxisY->setGridLineVisible(false);
}

void MainWindow::setCharts()
{
    volatoge.cView->setAxisX(vaxisX,line1);
    strongelectric.cView->setAxisX(saxisX,line2);
    weakelectric.cView->setAxisX(waxisX,line3);

    volatoge.cView->setAxisY(vaxisY,line1);
    strongelectric.cView->setAxisY(saxisY,line2);
    weakelectric.cView->setAxisY(waxisY,line3);

    volatoge.cView->legend()->hide();    //隐藏颜色图例
    strongelectric.cView->legend()->hide();
    weakelectric.cView->legend()->hide();
}

void MainWindow::customUi()
{
    ui->volatoge->setChart(volatoge.cView);
    ui->strongelectric->setChart(strongelectric.cView);
    ui->weakelectric->setChart(weakelectric.cView);

    ui->volatoge->setRenderHint(QPainter::Antialiasing);    //抗锯齿渲染
    ui->strongelectric->setRenderHint(QPainter::Antialiasing);
    ui->weakelectric->setRenderHint(QPainter::Antialiasing);

    ui->volatoge->setBackgroundRole(QPalette::Dark);
    ui->volatoge->setAutoFillBackground(true);
    ui->volatoge->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->volatoge->setFocusPolicy(Qt::StrongFocus);

    ui->strongelectric->setBackgroundRole(QPalette::Dark);
    ui->strongelectric->setAutoFillBackground(true);
    ui->strongelectric->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->strongelectric->setFocusPolicy(Qt::StrongFocus);

    ui->weakelectric->setBackgroundRole(QPalette::Dark);
    ui->weakelectric->setAutoFillBackground(true);
    ui->weakelectric->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->weakelectric->setFocusPolicy(Qt::StrongFocus);

    ui->comboBox->setBackgroundRole(QPalette::Dark);
    ui->comboBox->setAutoFillBackground(true);
}

void MainWindow::loadFileNow()
{
    emit readyForRead(volatoge.axiData);
}

void MainWindow::saveFileNow()
{
    emit readyForWrite(volatoge.axiData,strongelectric.axiData,weakelectric.axiData);
}

void MainWindow::timerEvent(QTimerEvent *)
{
    onDraw();
}

void MainWindow::onDraw()
{
    static int xs=0;

    volatoge.axiData.clear();
    strongelectric.axiData.clear();
    weakelectric.axiData.clear();

    udpData.addPoint(volatoge.axiData,strongelectric.axiData,weakelectric.axiData);
    if(!volatoge.axiData.isEmpty()) {
        volatoge.cView->axisX()->setRange(1+xs,MAXAXISX+xs);  //动态更新x轴坐标
        strongelectric.cView->axisX()->setRange(1+xs,MAXAXISX+xs);
        weakelectric.cView->axisX()->setRange(1+xs,MAXAXISX+xs);
        //ui->volatoge->setChart(volatoge.cView);
        xs+=MAXSTEP;

        line1->append(volatoge.axiData);
        line2->append(strongelectric.axiData);
        line3->append(weakelectric.axiData);
        //qDebug()<<"line2:"<<strongelectric.axiData[0].x()<<","<<strongelectric.axiData[0].y()<<endl;
        //qDebug()<<"line3"<<weakelectric.axiData[0].x()<<","<<weakelectric.axiData[0].y()<<endl;
        (line1->count()>=MAXDRAWPOINTS)?(line1->removePoints(0,MAXREMOVEPOINTS),0):1; //尽量使用条件传送
        (line2->count()>=MAXDRAWPOINTS)?(line2->removePoints(0,MAXREMOVEPOINTS),0):1;
        (line3->count()>=MAXDRAWPOINTS)?(line3->removePoints(0,MAXREMOVEPOINTS),0):1;

        ui->volatoge->update();
        ui->strongelectric->update();
        ui->weakelectric->update();
    }
}

void MainWindow::comboBoxChoseChanged(int index)
{
    udpData.selectVolAData(index);
}

void MainWindow::comboBox2ChoseChanged(int index)
{
    udpData.selectStrEData(index);
}

void MainWindow::comboBox3ChoseChanged(int index)
{
    udpData.selectWeaEData(index);
}

MainWindow::~MainWindow()
{
    udpDatagram.quit();
    udpDatagram.wait();

    delete line1;
    delete line2;
    delete line3;

    delete vaxisX;
    delete vaxisY;
    delete saxisX;
    delete saxisY;
    delete waxisX;
    delete waxisY;

    delete ui;
}
