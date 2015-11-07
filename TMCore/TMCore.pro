#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T13:56:09
#
#-------------------------------------------------

QT       -= gui

TARGET = TMCore
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11

SOURCES += \
    TMCore.cpp \
    data/TMBaseData.cpp \
    data/JMDataObj.cpp \
    data/Club.cpp \
    JMUtil.cpp \
    data/Competitor.cpp \
    data/Bracket.cpp \
    TournamentDoc.cpp \
    data/Match.cpp \
    data/Tournament.cpp

HEADERS += \
    TMCore.h \
    data/TMBaseData.h \
    data/JMDataObj.h \
    data/Club.h \
    JMUtil.h \
    data/Competitor.h \
    data/Bracket.h \
    TournamentDoc.h \
    data/Match.h \
    data/Tournament.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

DEFINES += BUILD_TMCORE
