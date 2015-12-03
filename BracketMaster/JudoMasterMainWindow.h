#pragma once

#include <QDir>
#include <QMainWindow>
#include <QString>

#include "commands/CloseCommand.h"
#include "commands/CreateTournamentCommand.h"
#include "commands/ExportCSVCommand.h"
#include "commands/ImportDataCommand.h"
#include "commands/OpenCommand.h"
#include "commands/PrintBrancketsCommand.h"
#include "commands/TournamentInfoCommand.h"
#include "commands/SaveCommand.h"

namespace Ui {
class JudoMasterMainWindow;
}

class PrintBracketsAction;

class JudoMasterMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit JudoMasterMainWindow(QWidget *parent = 0);
    ~JudoMasterMainWindow();

public slots:
    void printRegistration();

private slots:
    void updateControls();
    void fileImported();
    void resetTitle();

private:
    Ui::JudoMasterMainWindow *ui;

    PrintBracketsAction* m_printBracketsAction;
    QString m_fileName;
    QDir m_saveDir;

    // Commands.
    BaseCommandPtr m_tournamentInfoCommand;
    BaseCommandPtr m_createTournamentCommand;
    // TODO - Either convert all to BaseCommandPtr or specific typedef
    PrintBracketsCommand m_printBracketsCommand;
    CloseCommand m_closeCommand;
    SaveCommand m_saveCommand;
    SaveCommand m_saveAsCommand;
    OpenCommand m_openCommand;
    ImportDataCommand m_importDataCommand;
    ExportCSVCommand m_exportCSVCommand;

};

