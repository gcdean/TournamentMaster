#-------------------------------------------------
#
# Project created by QtCreator 2015-05-31T21:16:12
#
#-------------------------------------------------

QT       += testlib

QT       += gui

QMAKE_CXXFLAGS += -Wunused-parameter
QMAKE_CXXFLAGS += -std=c++11

TARGET = BracketMasterTests
CONFIG   += console
CONFIG   -= app_bundle

#OBJECTS_DIR = ../BracketMaster

TEMPLATE = app


SOURCES += \
    main.cpp \
    BracketTests.cpp \
    ClubTests.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += ../BracketMaster

HEADERS += \
    AutoTest.h \
    BracketTests.h \
    ClubTests.h


# Bracket Master Source & Header Files
SOURCES +=\
    ../BracketMaster/Bracket.cpp \
    ../BracketMaster/Club.cpp \
    ../BracketMaster/Competitor.cpp \
    ../BracketMaster/JMDataObj.cpp \
    ../BracketMaster/JMUtil.cpp

#HEADERS += \
#    ../BracketMaster/Bracket.h \
#    ../BracketMaster/Club.h \
#    ../BracketMaster/JMDataObj.h \
#    ../BracketMaster/JMUtil.h
