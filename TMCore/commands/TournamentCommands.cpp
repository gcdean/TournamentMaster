#include "TournamentCommands.h"




UpdateTournamentCommand::UpdateTournamentCommand(Tournament src, QObject *parent)
    : BaseUndoCommand(parent)
    , m_tournament(src)
{

}

Tournament UpdateTournamentCommand::tournament()
{
    return m_tournament;
}

bool UpdateTournamentCommand::run(IDocument *const doc)
{
    Tournament orig = doc->tournament();

    doc->updateTournament(m_tournament);

    m_tournament = orig;

    return true;
}

bool UpdateTournamentCommand::undo(IDocument *doc)
{
    return run(doc);
}


GetTournamentCommand::GetTournamentCommand(QObject *parent)
    : BaseCommand(parent)
{

}

Tournament GetTournamentCommand::tournament()
{
    return m_tournament;
}

bool GetTournamentCommand::run(IDocument *const doc)
{
    m_tournament = doc->tournament();
    return true;
}
