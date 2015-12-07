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



bool ExportCSVCommand::run(IDocument *const doc)
{
    QString dir = QFileDialog::getExistingDirectory(dynamic_cast<QWidget *>(parent()), "Select Directory to export to.");
    if(dir.isEmpty())
    {
        return done(false);
    }
    qDebug() << "EXPORT TO: (" << dir << ")";

    // TODO - Fix this. Use editor/doc
    doc->save();

    return done(true);
}
