#include "TournamentInfoCommand.h"

#include "dialogs/TournamentInfoDialog.h"

TournamentInfoCommand::TournamentInfoCommand(QObject *parent)
    : BaseCommand(parent)
{

}

TournamentInfoCommand::~TournamentInfoCommand()
{

}

bool TournamentInfoCommand::run()
{
    TournamentInfoDialog dlg(dynamic_cast<QWidget *>(parent()));
    dlg.exec();
}

