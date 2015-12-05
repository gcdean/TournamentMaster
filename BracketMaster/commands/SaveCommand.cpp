#include "SaveCommand.h"

#include "JudoMasterApplication.h"
#include "commands/TournamentCommands.h"
#include "data/Tournament.h"

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonDocument>

#include <QDebug>

SaveCommand::SaveCommand(bool saveAs, QObject *parent)
    : BaseCommand(parent),
      m_enableSaveAs(saveAs)
{

}

SaveCommand::~SaveCommand()
{

}



bool SaveCommand::run(IDocument *const doc)
{
    // TODO - need a tournament controller to encapsulate the commands.
    GetTournamentCmdPtr cmd = GetTournamentCmdPtr(new GetTournamentCommand);
    JMApp()->commandController()->doCommand(cmd);
    Tournament tournament = cmd->tournament();
    QString name = doc->name();

    if(name.isEmpty() || m_enableSaveAs)
    {
        QString newfileName = QFileDialog::getSaveFileName(dynamic_cast<QWidget *>(parent()), "Save", JMApp()->lastSaveDir().absolutePath(), "Tournament Files (*.ecj);;JSON Files (*.json)");
        if(newfileName.isEmpty())
        {
            return done(false);
        }

        QFileInfo finfo(newfileName);
        JMApp()->setLastSaveDir(finfo.absoluteDir());

        if(!doc->save(newfileName))
        {
            // TODO - error msg here.
        }
    }
    else
    {
        if(!doc->save())
        {
            // TODO - error msg here.
        }
    }


    return done(true);
}
