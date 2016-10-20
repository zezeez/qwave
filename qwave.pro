#-------------------------------------------------
#
# Project created by QtCreator 2016-09-27T09:23:28
#
#-------------------------------------------------

QT       += core gui widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qwave
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp \
    fileoperate.cpp \
    udpprocess.cpp \
    chartview.cpp \
    chart.cpp

HEADERS  += mainwindow.h \
    fileoperate.h \
    udpprocess.h \
    chart.h \
    chartview.h

FORMS    += mainwindow.ui

QT += network

#INCLUDEPATH += /usr/include/qwt6

#LIBS += -L/usr/lib64 -lqwt
