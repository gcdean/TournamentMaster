#include "JudoMasterMainWindow.h"
#include "ui_JudoMasterMainWindow.h"

#include "data/Bracket.h"
#include "controllers/CompetitorController.h"
#include "JudoMasterApplication.h"
#include "data/Tournament.h"
#include "actions/PrintBracketsAction.h"
#include "commands/PrintBrancketsCommand.h"
#include "commands/PrintRegistrationCommand.h"

#include <QDebug>



JudoMasterMainWindow::JudoMasterMainWindow(QWidget *parent) :
    QMainWindow(parent)
    , ui(new Ui::JudoMasterMainWindow)
    , m_printBracketsAction(0)
    , m_tournamentInfoCommand(this)
    , m_createTournamentCommand(this)
    , m_printBracketsCommand(this)
    , m_saveCommand(false, this)
    , m_saveAsCommand(true, this)
    , m_openCommand(this)
    , m_importDataCommand(this)
    , m_exportCSVCommand(this)
{
    ui->setupUi(this);

    m_saveDir = QDir::home();


    ui->mainToolBar->setVisible(false);

    ui->tabWidget->setTabText(0, QString("General"));
    ui->tabWidget->setTabText(1, QString("Brackets"));

    m_printBracketsAction = new PrintBracketsAction(this);
    ui->menuPrint->addAction(m_printBracketsAction);

    connect(&m_openCommand, &BaseCommand::commandSuccessful, this, &JudoMasterMainWindow::updateControls);
    connect(&m_closeCommand, &BaseCommand::commandSuccessful, this, &JudoMasterMainWindow::updateControls);
    connect(&m_saveAsCommand, &BaseCommand::commandSuccessful, this, &JudoMasterMainWindow::resetTitle);
    connect(&m_createTournamentCommand, &BaseCommand::commandComplete, this, &JudoMasterMainWindow::updateControls);
    connect(&m_createTournamentCommand, &BaseCommand::commandComplete, [=] () {JMApp()->tournamentEditor()->doCommand(QSharedPointer<BaseCommand>(&m_tournamentInfoCommand));/* m_tournamentInfoCommand.run(JMApp()->tournamentEditor());*/});
    connect(&m_importDataCommand, &BaseCommand::commandSuccessful, this, &JudoMasterMainWindow::fileImported);


    ///////// NEW
    connect(ui->actionNew, &QAction::triggered, [=] (){JMApp()->tournamentEditor()->doCommand(QSharedPointer<BaseCommand>(&m_createTournamentCommand));});

    connect(ui->actionSave_As, &QAction::triggered, [=] (){JMApp()->tournamentEditor()->doCommand(QSharedPointer<BaseCommand>(&m_saveAsCommand));});
    connect(ui->actionSave, &QAction::triggered, [=] (){JMApp()->tournamentEditor()->doCommand(QSharedPointer<BaseCommand>(&m_saveCommand));});

    connect(ui->actionClose, &QAction::triggered, [=] (){JMApp()->tournamentEditor()->doCommand(QSharedPointer<BaseCommand>(&m_closeCommand));});
    connect(ui->actionOpen, &QAction::triggered, [=] (){JMApp()->tournamentEditor()->doCommand(QSharedPointer<BaseCommand>(&m_openCommand));});
    ///////// OLD
//    connect(ui->actionNew, &QAction::triggered, &m_createTournamentCommand, &BaseCommand::run);

//    connect(ui->actionSave_As, &QAction::triggered, &m_saveAsCommand, &BaseCommand::run);
//    connect(ui->actionSave, &QAction::triggered, &m_saveCommand, &BaseCommand::run);

//    connect(ui->actionClose, &QAction::triggered, &m_closeCommand, &BaseCommand::run);
//    connect(ui->actionOpen, &QAction::triggered, &m_openCommand, &BaseCommand::run);

    //////////// END OLD


    connect(ui->actionPrint_Registration, &QAction::triggered, this, &JudoMasterMainWindow::printRegistration);
    connect(m_printBracketsAction, &QAction::triggered, [=] (){JMApp()->tournamentEditor()->doCommand(QSharedPointer<BaseCommand>(&m_printBracketsCommand));});
    connect(ui->actionImport, &QAction::triggered, [=](){JMApp()->tournamentEditor()->doCommand(QSharedPointer<BaseCommand>(&m_importDataCommand));});
    connect(ui->actionExport, &QAction::triggered, [=](){JMApp()->tournamentEditor()->doCommand(QSharedPointer<BaseCommand>(&m_exportCSVCommand));});
    connect(ui->actionTournamentInfo, &QAction::triggered, [=] (){JMApp()->tournamentEditor()->doCommand(QSharedPointer<BaseCommand>(&m_tournamentInfoCommand));});

    connect(JMApp(), &QCoreApplication::aboutToQuit, [=] (){JMApp()->tournamentEditor()->doCommand(QSharedPointer<BaseCommand>(&m_closeCommand));});
    connect(ui->actionExit, &QAction::triggered, this, &QApplication::quit);
    updateControls();
}

JudoMasterMainWindow::~JudoMasterMainWindow()
{
    delete ui;
}

void JudoMasterMainWindow::printRegistration()
{
    PrintRegistrationCommand cmd(this);
    cmd.run(nullptr);
}

void JudoMasterMainWindow::fileImported()
{

    const QList<Competitor *> imported = m_importDataCommand.importedCompetitors();
    const QList<Competitor *> skipped = m_importDataCommand.skippedCompetitors();

    qDebug() << "Imported Competitors:";
    foreach(Competitor *comp, imported)
    {
        qDebug() << comp->lastName() << ", " << comp->firstName() << ", " << dynamic_cast<Club *>(JMApp()->clubController()->find(comp->clubId()))->clubName();
    }

    qDebug() << "\n\nSkipped Competitors:";
    foreach(Competitor *comp, skipped)
    {
        qDebug() << comp->lastName() << ", " << comp->firstName();

    }

}

void JudoMasterMainWindow::resetTitle()
{
    if(JMApp()->tournament())
    {
        QString tfilename = JMApp()->tournament()->fileName();
        QFileInfo fi(tfilename);
        setWindowTitle(QString("Judo Master (%1.%2)").arg(fi.completeBaseName()).arg(fi.completeSuffix()));
    }
    else
    {
        setWindowTitle("Bracket Master");
    }
}

void JudoMasterMainWindow::updateControls()
{
    bool enabled = JMApp()->tournament() ? true : false;

    ui->detailsWidget->setEnabled(enabled);

    ui->actionSave->setEnabled(enabled);
    ui->actionSave_As->setEnabled(enabled);

    resetTitle();
}
