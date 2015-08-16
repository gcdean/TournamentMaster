#-------------------------------------------------
#
# Project created by QtCreator 2015-07-30T22:03:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TimerMaster
TEMPLATE = app

QMAKE_CXXFLAGS += -Wunused-parameter
QMAKE_CXXFLAGS += -Wunused-function
CONFIG += c++11


SOURCES += main.cpp\
        TimerMasterMainWindow.cpp \
    TimerWidget.cpp

HEADERS  += TimerMasterMainWindow.h \
    TimerWidget.h

FORMS    += TimerMasterMainWindow.ui \
    TimerWidget.ui
