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
    data/Tournament.cpp \
    commands/BaseCommand.cpp \
    commands/BaseUndoCommand.cpp \
    commands/ClubCommands.cpp \
    commands/BracketCommands.cpp \
    CommandController.cpp \
    commands/CompetitorCommands.cpp \
    commands/MatchCommands.cpp \
    commands/TournamentCommands.cpp

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
    data/Tournament.h \
    commands/BaseCommand.h \
    commands/BaseUndoCommand.h \
    IEditor.h \
    commands/ClubCommands.h \
    data/ClubData.h \
    data/CompetitorData.h \
    data/BracketData.h \
    data/MatchData.h \
    data/TournamentData.h \
    commands/BracketCommands.h \
    IDocument.h \
    CommandController.h \
    commands/CompetitorCommands.h \
    commands/MatchCommands.h \
    commands/TournamentCommands.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

DEFINES += BUILD_TMCORE
