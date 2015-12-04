#include "MatchCommands.h"



GetAllMatchesCommand::GetAllMatchesCommand(int bracketId, QObject *parent)
    : BaseCommand(parent)
    , m_bracketId(bracketId)
{

}

const QList<Match> GetAllMatchesCommand::matches()
{
    return m_matches;
}

bool GetAllMatchesCommand::run(IDocument *const doc)
{
    m_matches = doc->matches(m_bracketId);

    return m_matches.size() > 0;
}

BaseMatchCommand::BaseMatchCommand(QObject *parent)
    : BaseUndoCommand(parent)
{

}

BaseMatchCommand::BaseMatchCommand(Match match, QObject *parent)
    : BaseUndoCommand(parent)
    , m_match(match)
{

}

Match BaseMatchCommand::match() const
{
    return m_match;
}


FindMatchCommand::FindMatchCommand(int id, QObject *parent)
    : BaseMatchCommand(parent)
    , m_matchId(id)
{

}

bool FindMatchCommand::run(IDocument *const doc)
{
    m_match = doc->match(m_matchId);

    return m_match.isValid();
}


bool FindMatchCommand::isUndoable()
{
    return false;
}

bool FindMatchCommand::undo(IDocument *doc)
{
    Q_UNUSED(doc);
    return false;
}

AddMatchCommand::AddMatchCommand(int bracketId, QObject *parent)
    : BaseMatchCommand(parent)
    , m_bracketId(bracketId)
    , m_useMatchObj(false)
{

}

AddMatchCommand::AddMatchCommand(int bracketId, Match match, QObject *parent)
    : BaseMatchCommand(match, parent)
    , m_bracketId(bracketId)
    , m_useMatchObj(true)
{

}

bool AddMatchCommand::run(IDocument *const doc)
{
    // Are we adding a brand new one or an existing one?
    bool success = false;
    if(m_useMatchObj)
    {
        success = doc->addMatch(m_bracketId, m_match);
    }
    else
    {
        m_match = doc->addMatch(m_bracketId);
        success = m_match.isValid();
    }

    return success;
}

bool AddMatchCommand::undo(IDocument *doc)
{
    return doc->removeMatch(m_match.id());
}

RemoveMatchCommand::RemoveMatchCommand(Match match, QObject *parent)
    : BaseMatchCommand(match, parent)
{

}


bool RemoveMatchCommand::run(IDocument *const doc)
{
    return doc->removeMatch(m_match.id());
}

bool RemoveMatchCommand::undo(IDocument *doc)
{
    return doc->addMatch(m_match.bracketId(), m_match);
}

UpdateMatchCommand::UpdateMatchCommand(Match match, QObject *parent)
    : BaseMatchCommand(match, parent)
{

}


bool UpdateMatchCommand::run(IDocument *const doc)
{
    Match origMatch = doc->match(m_match.id());
    if(doc->updateMatch(m_match))
    {
        m_match = origMatch;
        return true;
    }

    return false;
}

bool UpdateMatchCommand::undo(IDocument *doc)
{
    return run(doc);
}
