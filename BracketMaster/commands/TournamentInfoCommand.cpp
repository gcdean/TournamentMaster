#include "TournamentInfoCommand.h"

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
    const std::unique_ptr<Tournament> &tournament = JMApp()->tournament();

    // Pass to the dialog
    TournamentInfoDialog dlg(dynamic_cast<QWidget *>(parent()));
    dlg.setName(tournament->name());
    dlg.setDate(tournament->date());
    dlg.setTime(tournament->startTime());
    dlg.setUseMatchCards(tournament->useTexasMatchCards());
    if(dlg.exec() == QDialog::Accepted)
    {
        // Check return type and if ok, update the tournament info.
        tournament->setName(dlg.name());
        tournament->setDate(dlg.date());
        tournament->setStartTime(dlg.time());
        tournament->setTexasMatchCards(dlg.useMatchCards());

        return done(true);
    }

    return done(false);
}

