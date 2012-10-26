#-------------------------------------------------
#
# Project created by QtCreator 2012-10-26T21:02:15
#
#-------------------------------------------------

QT       += testlib network

QT       -= gui

TARGET = tst_test_tcpsockettest
CONFIG   += console testcase
CONFIG   -= app_bundle

TEMPLATE = app
LIBS += -L../../lib
LIBS += -lnetwork
INCLUDEPATH += ../../network

SOURCES += tst_test_tcpsockettest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

DESTDIR = ../bin

QMAKE_POST_LINK += make check
