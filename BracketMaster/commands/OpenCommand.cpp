#include "OpenCommand.h"

#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>

#include "JudoMasterApplication.h"

OpenCommand::OpenCommand(QObject *parent) :
    BaseCommand(parent)
{

}

OpenCommand::~OpenCommand()
{

}



bool OpenCommand::run()
{
    QString openFileName = QFileDialog::getOpenFileName(dynamic_cast<QWidget *>(parent()), "Open JudoMaster Tournament File", JMApp()->lastSaveDir().absolutePath(), "Tournament Files (*.ecj);;JSON Files (*.json)");

    if(openFileName.isEmpty())
    {
        return false;
    }

    QFile tournFile(openFileName);

    if(!tournFile.open(QIODevice::ReadOnly))
    {
        qWarning("Could not open file for reading");
        return done(false);
    }

    QByteArray saveData = tournFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    std::unique_ptr<Tournament> tournament(new Tournament);
    tournament->setFileName(openFileName);

    QJsonObject jobj = loadDoc.object();
    tournament->read(jobj);

    JMApp()->setTournament(std::move(tournament));

    return done(true);
}
