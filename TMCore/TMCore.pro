#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T13:56:09
#
#-------------------------------------------------

QT       -= gui

TARGET = TMCore
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    TMCore.cpp \
    data/TMBaseData.cpp

HEADERS += \
    TMCore.h \
    data/TMBaseData.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

DEFINES += BUILD_TMCORE
