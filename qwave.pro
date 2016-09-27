#-------------------------------------------------
#
# Project created by QtCreator 2016-09-27T09:23:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qwave
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    udphandle.cpp \
    fileoperate.cpp

HEADERS  += mainwindow.h \
    udphandle.h \
    fileoperate.h

FORMS    += mainwindow.ui

QT += network

QT += widgets
