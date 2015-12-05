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
    PrintBracketsCmdPtr m_printBracketsCommand;
    CloseCmdPtr m_closeCommand;
    SaveCmdPtr m_saveCommand;
    SaveCmdPtr m_saveAsCommand;
    OpenCmdPtr m_openCommand;
    ImportDataCmdPtr m_importDataCommand;
    ExportCSVCmdPtr m_exportCSVCommand;

};

