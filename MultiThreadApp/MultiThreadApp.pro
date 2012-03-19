#-------------------------------------------------
#
# Project created by QtCreator 2012-02-17T18:14:20
#
#-------------------------------------------------

QT       += core gui

#CONFIG += qtestlib

TARGET = MultiThreadApp
TEMPLATE = app


SOURCES += main.cpp \
    multithreadapp.cpp \
    worker.cpp \
    case1.cpp \
    case2.cpp \
    case3.cpp

HEADERS  += multithreadapp.h \
    worker.h \
    case2.cpp \
    case3.cpp

DESTDIR = ../bin
