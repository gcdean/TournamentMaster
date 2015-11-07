#-------------------------------------------------
#
# Project created by QtCreator 2015-05-31T21:16:12
#
#-------------------------------------------------

QT       += testlib

QT       += gui

QMAKE_CXXFLAGS += -Wunused-parameter
CONFIG += c++11

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../TMCore/release/ -lTMCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../TMCore/debug/ -lTMCore
else:unix: LIBS += -L$$OUT_PWD/../TMCore/ -lTMCore

INCLUDEPATH += $$PWD/../TMCore
DEPENDPATH += $$PWD/../TMCore

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../TMCore/release/libTMCore.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../TMCore/debug/libTMCore.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../TMCore/release/TMCore.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../TMCore/debug/TMCore.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../TMCore/libTMCore.a
