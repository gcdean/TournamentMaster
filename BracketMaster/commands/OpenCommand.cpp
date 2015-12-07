#include "OpenCommand.h"

#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>

#include <QDebug>

#include "JudoMasterApplication.h"
#include "TournamentDoc.h"

OpenCommand::OpenCommand(QObject *parent) :
    BaseCommand(parent)
{

}

OpenCommand::~OpenCommand()
{

}



bool OpenCommand::run(IDocument *const doc)
{
    // editor is not used because a new one is created.
    Q_UNUSED(doc)

    QString openFileName = QFileDialog::getOpenFileName(dynamic_cast<QWidget *>(parent()), "Open JudoMaster Tournament File", JMApp()->lastSaveDir().absolutePath(), "Tournament Files (*.ecj);;JSON Files (*.json)");

    if(openFileName.isEmpty())
    {
        return false;
    }

    QFileInfo finfo(openFileName);
    JMApp()->setLastSaveDir(finfo.absoluteDir());


    QFile tournFile(openFileName);


    if(!tournFile.open(QIODevice::ReadOnly))
    {
        qWarning("Could not open file for reading");
        return done(false);
    }


    // New Document
    tournFile.close();

    // Create a new editor here? If so, what type?
    QSharedPointer<TournamentDoc> newdoc = QSharedPointer<TournamentDoc>(new TournamentDoc);
    QSharedPointer<CommandController> teditor = QSharedPointer<CommandController>(new CommandController(newdoc));
    newdoc->load(openFileName);

    JMApp()->setCommandController(teditor);

    return done(true);
}
