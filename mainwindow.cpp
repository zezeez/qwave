#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <QFileDialog>
#include <QMessageBox>
#include "udphandle.h"

#define WIDTH 1220
#define D1 50
#define D2 50
#define D3 70
#define D4 80
#define READ_DATA false
#define DISPLAY_DATA true

typedef unsigned short uint16;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Udphandle recv_data;
    recv_data.initSocket();
    ui->setupUi(this);
    //connect(ui->close,&QPushButton::clicked,this,QCoreApplication::exit(0));
    connect(ui->close,SIGNAL(clicked(bool)),this,SLOT(close()));
    /*
    rect=QRect(0,0,WIDTH,600);
    pointt=new int[rect.width()];
    height=rect.height();
    width=rect.width();
    flag_load=false;
    high_data=false;
    left_data=65535;
    start=true;

    column=DATA_ARRAY_SIZE;
    valy=1;
    rect_height=rect.height();
    display_wave_flag=false;

    m_pen_width=1;
    m_other_pen_width=1;

    flag1=false;
    flag=0;
    initPoint.setX(40);
    initPoint.setY(20);
    n=1;
    val=2;

    num=new int[DATA_ARRAY_SIZE];
    memset(num,65535,sizeof(int)*DATA_ARRAY_SIZE);

    sum1=new int[column/n];
    sum2=new int[column-n];
    sum3=new int[column/n];
    sum4=new int[column/n];

    //connect(ui->loadFileBtn,SIGNAL(clicked()),this,SLOT(loadFile()));
    //connect(ui->showWaveBtn,SIGNAL(clicked()),this,SLOT(showNumber()));
    //connect(ui->saveFileBtn,SIGNAL(clicked()),this,SLOT(saveShowData(int*))); */
}

/*void MainWindow::paintEvent(QPaintEvent *e)
{
    painter=new QPainter(this);
    painter->translate(initPoint.x(),initPoint.y());
    painter->begin(this);
    painter->drawRect(rect);
    painter->setPen(Qt::red);
    setXYCord();
    painter->fillRect(rect,QBrush(QColor(Qt::black),Qt::SolidPattern));

    realTimeWave();
    painter->end();
}

void MainWindow::setXYCord()
{
    //draw x
    painter->setPen(QPen(Qt::blue));
    for(int i=0;i<rect.width();i++) {
        point[0].setX(i*10);
        point[0].setY(height);
        point[1].setX(i*10);
        point[1].setY(height-3);
        painter->drawLine(QPoint(point[0].x(),point[0].y()),QPoint(point[1].x(),point[1].y()));
    }
    painter->drawLine(QPoint(0,height),QPoint(width,height));

    //draw y
    painter->setPen(QPen(Qt::red));
    for(int i=height/10;i>0;i--) {
        point[0].setX(0);
        point[0].setY(i*10);
        point[1].setX(3);
        point[1].setY(i*10);
        painter->drawLine(QPoint(point[0].x(),point[0].y()),QPoint(point[1].x(),point[1].y()));
    }
    painter->drawLine(QPoint(0,0),QPoint(0,height));

    //draw y point
    int j=height/10-1;
    QFont font("Arial",6,QFont::Normal,true);
    painter->setFont(font);
    for(int i=-200;i<=height-200;i+=10) {
        painter->drawText(rect.x()-13,height-(i+200)+3,QString::number((height-3)/10-j-20,10));
        j--;
    }

    //draw x point
    j=1;
    painter->setFont(font);
    painter->setPen(QPen(Qt::black));
    for(int i=10;i<width;i+=10) {
        painter->drawText(rect.x()+i-3,height+10,QString::number(j,10));
        j++;
    }
}

void MainWindow::realTimeWave()
{
    int startt=0;
    for(int j=0;j<column;j++) {
        painter->setPen(QPen(QPen(Qt::green,m_pen_width,Qt::SolidLine)));
        painter->drawPoint(QPoint(startt,(rect_height-num[j]/valy-D1)));
        startt+=val;
        if(startt>WIDTH || num[j]>=65535)
            break;
    }
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    this->close();
}*/

MainWindow::~MainWindow()
{
    /*delete painter;
    delete []sum2;
    delete []sum3;
    delete []sum4;
    sum2=NULL;
    sum3=NULL;
    sum4=NULL;
    delete pointt;*/
    delete ui;
}
