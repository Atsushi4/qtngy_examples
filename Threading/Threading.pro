#-------------------------------------------------
#
# Project created by QtCreator 2012-04-18T16:45:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Threading
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
    manager.cpp \
    worker.cpp \
    mainwindow.cpp \
    threadrunmanager.cpp \
    nothreadmanger.cpp \
    threadnewmanager.cpp \
    movemanager.cpp \
    poolmanager.cpp \
    runmanager.cpp \
    mapmanager.cpp \
    lamdamapmanager.cpp

HEADERS  += \
    manager.h \
    worker.h \
    mainwindow.h \
    threadrunmanager.h \
    nothreadmanger.h \
    threadnewmanager.h \
    movemanager.h \
    poolmanager.h \
    runmanager.h \
    mapmanager.h \
    lamdamapmanager.h

FORMS += \
    mainwindow.ui
