#include "TournamentInfoCommand.h"

#include "commands/TournamentCommands.h"
#include "JudoMasterApplication.h"
#include "dialogs/TournamentInfoDialog.h"

TournamentInfoCommand::TournamentInfoCommand(QObject *parent)
    : BaseCommand(parent)
{

}

TournamentInfoCommand::~TournamentInfoCommand()
{

}

bool TournamentInfoCommand::run(IDocument *const doc)
{
    // Get the tournament info
    GetTournamentCmdPtr getTrnCmd = GetTournamentCmdPtr(new GetTournamentCommand);
    // TODO - Maybe replace with direct doc call?
    if(JMApp()->commandController()->doCommand(getTrnCmd))
    {

        Tournament tournament = getTrnCmd->tournament();

        // Pass to the dialog
        TournamentInfoDialog dlg(dynamic_cast<QWidget *>(parent()));
        dlg.setName(tournament.name());
        dlg.setDate(tournament.date());
        dlg.setTime(tournament.startTime());
        dlg.setUseMatchCards(tournament.useTexasMatchCards());
        if(dlg.exec() == QDialog::Accepted)
        {
            // Check return type and if ok, update the tournament info.
            tournament.setName(dlg.name());
            tournament.setDate(dlg.date());
            tournament.setStartTime(dlg.time());
            tournament.setTexasMatchCards(dlg.useMatchCards());

            UpdateTournamentCmdPtr updateCmd = UpdateTournamentCmdPtr(new UpdateTournamentCommand(tournament));

            return done(JMApp()->commandController()->doCommand(updateCmd));
        }
    }

    return done(false);
}

