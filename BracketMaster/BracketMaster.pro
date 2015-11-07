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

#DEPENDPATH += . ../TMCore
#INCLUDEPATH += ../TMCore
#OBJECTS_DIR = ../gdeanobjs

SOURCES += main.cpp\
        JudoMasterMainWindow.cpp \
    ClubsEditor.cpp \
    ClubEditor.cpp \
    CompetitorList.cpp \
    JudoMasterApplication.cpp \
    ClubListModel.cpp \
    CompetitorTableModel.cpp \
    BracketEditor.cpp \
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
    MatchTableModel.cpp \
    MatchItemDelegate.cpp \
    controllers/BaseController.cpp \
    controllers/BracketController.cpp \
    controllers/CompetitorController.cpp \
    controllers/MatchController.cpp \
    controllers/PrintController.cpp \
    controllers/ClubController.cpp \
    dialogs/TournamentInfoDialog.cpp \
    commands/TournamentInfoCommand.cpp \
    commands/CreateTournamentCommand.cpp \
    controllers/TournamentController.cpp \
    commands/CloseCommand.cpp \
    commands/SaveCommand.cpp \
    commands/OpenCommand.cpp \
    commands/ExportCSVCommand.cpp

HEADERS  += JudoMasterMainWindow.h \
    ClubsEditor.h \
    ClubEditor.h \
    CompetitorList.h \
    JudoMasterApplication.h \
    ClubListModel.h \
    CompetitorTableModel.h \
    BracketEditor.h \
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
    MatchTableModel.h \
    MatchItemDelegate.h \
    controllers/BaseController.h \
    controllers/BracketController.h \
    controllers/ClubController.h \
    controllers/CompetitorController.h \
    controllers/MatchController.h \
    controllers/PrintController.h \
    dialogs/TournamentInfoDialog.h \
    commands/TournamentInfoCommand.h \
    commands/CreateTournamentCommand.h \
    controllers/TournamentController.h \
    commands/CloseCommand.h \
    commands/SaveCommand.h \
    commands/OpenCommand.h \
    commands/ExportCSVCommand.h

FORMS    += JudoMasterMainWindow.ui \
    ClubsEditor.ui \
    ClubEditor.ui \
    CompetitorList.ui \
    BracketEditor.ui \
    BracketManager.ui \
    CompetitorFilterWidget.ui \
    CompetitorFilterWidget.ui \
    CompetitorEditor.ui \
    dialogs/TournamentInfoDialog.ui

RESOURCES += \
    Resources.qrc

DISTFILES += \
    BracketMaster.pri \
    Notes.txt

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
