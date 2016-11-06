#-------------------------------------------------
#
# Project created by QtCreator 2016-09-27T09:23:28
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qwave
TEMPLATE = app


SOURCES += common/main.cpp \
        common/mainwindow.cpp \
    common/fileoperate.cpp \
    common/udpprocess.cpp \
    common/chartview.cpp \
    common/chart.cpp \
    common/udpvincdata.cpp \
    common/writevincdata.cpp

HEADERS  += include/mainwindow.h \
    include/fileoperate.h \
    include/udpprocess.h \
    include/chart.h \
    include/chartview.h \
    include/udpvincdata.h \
    include/mystruct.h \
    include/writevincdata.h

FORMS    += mainwindow.ui

QT += network

#INCLUDEPATH += /usr/include/qwt6

#LIBS += -L/usr/lib64 -lqwt
