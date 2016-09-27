#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QTimerEvent>
#include <QPaintEvent>
#include <QByteArray>
#include <QCloseEvent>

#define DATA_ARRAY_SIZE 1000

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(qreal width,qreal height,QObject *parent=0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

/*public:
    void paintEvent(QPaintEvent *e);
    void processdata();

private:
    QPainter *painter;
    int column;

    QPen m_scaleLinePen;
    QPen m_waveDataPen;

    QRect rect;
    bool flag1;
    QPoint point[2];
    int height,width;
    QPoint initPoint;
    int timerId;
    qreal x;

    unsigned int gridnum;
    int *pointt;
    QString strSelectFileData;
    int flag;
    int n;
    int val;
    bool flag_load;
    bool display_wave_flag;
    int *num;

    int m_pen_width;
    int m_other_pen_width;
    int valy;
    int rect_height;
    int *sum1,*sum2,*sum3,*sum4;
    int left_data;
    bool high_data;
    bool start;

    QTimer *time;

public:
    QByteArray temp;
    void setXYCord();
    void showGrid();

    void setDefaultScaleLinePen();
    void setDefaultWaveDataPen();
    void setDefaultScope();
    void realTimeWave();

public slots:
    void drawGridBtn();
    void gridSpin();
    void saveShowData(int *point);
    void loadFile();
    void showNumber();

    void closeEvent(QCloseEvent *e);
    void processShareFile(); */

};

#endif // MAINWINDOW_H
