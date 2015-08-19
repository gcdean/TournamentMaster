#include "JudoMasterMainWindow.h"
#include "ui_JudoMasterMainWindow.h"

#include "Bracket.h"
#include "controllers/CompetitorController.h"
#include "JudoMasterApplication.h"
#include "Tournament.h"
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
    connect(&m_createTournamentCommand, &BaseCommand::commandComplete, &m_tournamentInfoCommand, &BaseCommand::run);
    connect(&m_importDataCommand, &BaseCommand::commandSuccessful, this, &JudoMasterMainWindow::fileImported);

    connect(ui->actionNew, &QAction::triggered, &m_createTournamentCommand, &BaseCommand::run);

    connect(ui->actionSave_As, &QAction::triggered, &m_saveAsCommand, &BaseCommand::run);
    connect(ui->actionSave, &QAction::triggered, &m_saveCommand, &BaseCommand::run);

    connect(ui->actionClose, &QAction::triggered, &m_closeCommand, &BaseCommand::run);
    connect(ui->actionOpen, &QAction::triggered, &m_openCommand, &BaseCommand::run);

    connect(ui->actionPrint_Registration, &QAction::triggered, this, &JudoMasterMainWindow::printRegistration);
    connect(m_printBracketsAction, &QAction::triggered, &m_printBracketsCommand, &BaseCommand::run);
    connect(ui->actionImport, &QAction::triggered, &m_importDataCommand, &BaseCommand::run);
    connect(ui->actionExport, &QAction::triggered, &m_exportCSVCommand, &BaseCommand::run);
    connect(ui->actionTournamentInfo, &QAction::triggered, &m_tournamentInfoCommand, &BaseCommand::run);

    connect(JMApp(), &QCoreApplication::aboutToQuit, &m_closeCommand, &BaseCommand::run);
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
    cmd.run();
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
