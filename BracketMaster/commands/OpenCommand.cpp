#include "OpenCommand.h"

#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>

#include <QDebug>

#include "JudoMasterApplication.h"
#include "data/TournamentDoc.h"

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
    qDebug() << "Data Size: " << saveData.size();


    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    std::unique_ptr<Tournament> tournament(new Tournament);
    tournament->setFileName(openFileName);

    QJsonObject jobj = loadDoc.object();
    tournament->read(jobj);

    // New Document
    tournFile.close();

    std::unique_ptr<TournamentDoc> doc(new TournamentDoc);
    doc->load(openFileName);


    JMApp()->setTournament(std::move(tournament));


    return done(true);
}
