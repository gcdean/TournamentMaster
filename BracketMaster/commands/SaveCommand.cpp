#include "SaveCommand.h"

#include "JudoMasterApplication.h"
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



bool SaveCommand::run(IEditor* const editor)
{
    // Get the tournament info
    const std::unique_ptr<Tournament> &tournament = JMApp()->tournament();

    if(tournament->fileName().isEmpty() || m_enableSaveAs)
    {
        QString newfileName = QFileDialog::getSaveFileName(dynamic_cast<QWidget *>(parent()), "Save", JMApp()->lastSaveDir().absolutePath(), "Tournament Files (*.ecj);;JSON Files (*.json)");
        if(newfileName.isEmpty())
        {
            return done(false);
        }

        QFileInfo finfo(newfileName);
        JMApp()->setLastSaveDir(finfo.absoluteDir());

        tournament->setFileName(newfileName);
    }

    QFile saveFile(tournament->fileName());

    if(!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Could not open file for writing");
    }

    QJsonObject trnObj;
    tournament->write(trnObj);

    QJsonDocument saveDoc(trnObj);
    if(-1 == saveFile.write(saveDoc.toJson()))
    {
        return done(false);
    }

    return done(true);
}
