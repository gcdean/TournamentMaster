#include "JudoMasterMainWindow.h"
#include "ui_JudoMasterMainWindow.h"

#include "Bracket.h"
#include "controllers/CompetitorController.h"
#include "JudoMasterApplication.h"
#include "Tournament.h"
#include "actions/PrintBracketsAction.h"
#include "commands/ImportDataCommand.h"
#include "commands/PrintBrancketsCommand.h"
#include "commands/PrintRegistrationCommand.h"

#include <QFileDialog>  // delete

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
{
    ui->setupUi(this);

    m_saveDir = QDir::home();


    ui->mainToolBar->setVisible(false);

    ui->tabWidget->setTabText(0, QString("General"));
    ui->tabWidget->setTabText(1, QString("Brackets"));

    m_printBracketsAction = new PrintBracketsAction(this);
    ui->menuPrint->addAction(m_printBracketsAction);

    connect(&m_openCommand, &BaseCommand::commandSuccesful, this, &JudoMasterMainWindow::updateControls);
    connect(&m_closeCommand, &BaseCommand::commandSuccesful, this, &JudoMasterMainWindow::updateControls);
    connect(&m_saveAsCommand, &BaseCommand::commandSuccesful, this, &JudoMasterMainWindow::resetTitle);
    connect(&m_createTournamentCommand, &BaseCommand::commandComplete, this, &JudoMasterMainWindow::updateControls);
    connect(&m_createTournamentCommand, &BaseCommand::commandComplete, &m_tournamentInfoCommand, &BaseCommand::run);

    connect(ui->actionNew, &QAction::triggered, &m_createTournamentCommand, &BaseCommand::run);

    connect(ui->actionSave_As, &QAction::triggered, &m_saveAsCommand, &BaseCommand::run);
    connect(ui->actionSave, &QAction::triggered, &m_saveCommand, &BaseCommand::run);

    connect(ui->actionClose, &QAction::triggered, &m_closeCommand, &BaseCommand::run);
    connect(ui->actionOpen, &QAction::triggered, &m_openCommand, &BaseCommand::run);

    connect(ui->actionPrint_Registration, &QAction::triggered, this, &JudoMasterMainWindow::printRegistration);
    connect(m_printBracketsAction, &QAction::triggered, &m_printBracketsCommand, &BaseCommand::run);
    connect(ui->actionImport, &QAction::triggered, this, &JudoMasterMainWindow::import);
    connect(ui->actionExport, &QAction::triggered, this, &JudoMasterMainWindow::exportData);
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

void JudoMasterMainWindow::import()
{
    QString openFileName = QFileDialog::getOpenFileName(this, "Import CSV File", m_saveDir.absolutePath(), "CSV Files (*.csv)");

    if(openFileName.isEmpty())
    {
        return;
    }

    importFile(openFileName);
    resetTitle();
}

void JudoMasterMainWindow::exportData()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select Directory to export to.");
    qDebug() << "EXPORT TO: (" << dir << ")";
    JMApp()->tournament()->write(dir);
}

void JudoMasterMainWindow::importFile(QString filename)
{
    ImportDataCommand importCmd(filename);
    importCmd.run();

    const QList<Competitor *> imported = importCmd.importedCompetitors();
    const QList<Competitor *> skipped = importCmd.skippedCompetitors();

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

bool JudoMasterMainWindow::getFilename()
{
    QString newfileName = QFileDialog::getSaveFileName(this, "Save", m_saveDir.absolutePath(), "Tournament Files (*.ecj);;JSON Files (*.json)");
    if(newfileName.isEmpty())
    {
        return false;
    }

    QFileInfo finfo(newfileName);
    m_saveDir = finfo.absoluteDir();
    m_fileName = newfileName;

//    m_tournament->setFileName(newfileName);
    JMApp()->tournament()->setFileName(newfileName);
    return true;
}

void JudoMasterMainWindow::updateControls()
{
    bool enabled = JMApp()->tournament() ? true : false;

    ui->detailsWidget->setEnabled(enabled);

    ui->actionSave->setEnabled(enabled);
    ui->actionSave_As->setEnabled(enabled);

    resetTitle();
}
