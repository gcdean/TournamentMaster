#include "ExportCSVCommand.h"

#include <QFileDialog>

#include <QDebug>

#include "JudoMasterApplication.h"

ExportCSVCommand::ExportCSVCommand(QObject *parent) :
    BaseCommand(parent)
{

}

ExportCSVCommand::~ExportCSVCommand()
{

}



bool ExportCSVCommand::run(IEditor* const editor)
{
    QString dir = QFileDialog::getExistingDirectory(dynamic_cast<QWidget *>(parent()), "Select Directory to export to.");
    if(dir.isEmpty())
    {
        return done(false);
    }
    qDebug() << "EXPORT TO: (" << dir << ")";
    JMApp()->tournament()->write(dir);

    return done(true);
}
