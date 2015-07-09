#-------------------------------------------------
#
# Project created by QtCreator 2015-05-31T20:58:20
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BracketMaster
TEMPLATE = app

QMAKE_CXXFLAGS += -Wunused-parameter
QMAKE_CXXFLAGS += -Wunused-function
CONFIG += c++11

#OBJECTS_DIR = ../gdeanobjs

SOURCES += main.cpp\
        JudoMasterMainWindow.cpp \
    Competitor.cpp \
    Club.cpp \
    Tournament.cpp \
    ClubsEditor.cpp \
    ClubEditor.cpp \
    CompetitorList.cpp \
    JudoMasterApplication.cpp \
    ClubListModel.cpp \
    CompetitorTableModel.cpp \
    Bracket.cpp \
    JMUtil.cpp \
    BracketEditor.cpp \
    JMDataObj.cpp \
    BracketManager.cpp \
    BracketTableModel.cpp \
    CompetitorItemDelegate.cpp \
    commands/BaseCommand.cpp \
    commands/PrintBracketsCommand.cpp \
    actions/PrintBracketsAction.cpp \
    CompetitorFilterWidget.cpp \
    CompetitorFilter.cpp \
    commands/PrintRegistrationCommand.cpp \
    BracketCompetitorTableModel.cpp \
    commands/MergeClubsCommand.cpp \
    commands/ImportDataCommand.cpp \
    BracketTypeItemDelegate.cpp \
    CompetitorEditor.cpp \
    Match.cpp \
    MatchTableModel.cpp \
    MatchItemDelegate.cpp \
    controllers/BaseController.cpp \
    controllers/BracketController.cpp \
    controllers/CompetitorController.cpp \
    controllers/MatchController.cpp \
    controllers/PrintController.cpp \
    controllers/ClubController.cpp

HEADERS  += JudoMasterMainWindow.h \
    Competitor.h \
    Club.h \
    Tournament.h \
    ClubsEditor.h \
    ClubEditor.h \
    CompetitorList.h \
    JudoMasterApplication.h \
    ClubListModel.h \
    CompetitorTableModel.h \
    Bracket.h \
    JMUtil.h \
    BracketEditor.h \
    JMDataObj.h \
    BracketManager.h \
    BracketTableModel.h \
    CompetitorItemDelegate.h \
    commands/BaseCommand.h \
    commands/PrintBrancketsCommand.h \
    actions/PrintBracketsAction.h \
    CompetitorFilterWidget.h \
    CompetitorFilter.h \
    commands/PrintRegistrationCommand.h \
    BracketCompetitorTableModel.h \
    commands/MergeClubsCommand.h \
    commands/ImportDataCommand.h \
    BracketTypeItemDelegate.h \
    CompetitorEditor.h \
    Match.h \
    MatchTableModel.h \
    MatchItemDelegate.h \
    controllers/BaseController.h \
    controllers/BracketController.h \
    controllers/ClubController.h \
    controllers/CompetitorController.h \
    controllers/MatchController.h \
    controllers/PrintController.h

FORMS    += JudoMasterMainWindow.ui \
    ClubsEditor.ui \
    ClubEditor.ui \
    CompetitorList.ui \
    BracketEditor.ui \
    BracketManager.ui \
    CompetitorFilterWidget.ui \
    CompetitorFilterWidget.ui \
    CompetitorEditor.ui

RESOURCES += \
    Resources.qrc

DISTFILES += \
    BracketMaster.pri
