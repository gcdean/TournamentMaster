#include "BracketCommands.h"


GetBracketCompetitorsCommand::GetBracketCompetitorsCommand(int bracketId, QObject *parent)
    : BaseCommand(parent)
    , m_bracketId(bracketId)
{

}

QList<Competitor> GetBracketCompetitorsCommand::competitors() const
{
    return m_competitors;
}

bool GetBracketCompetitorsCommand::run(IDocument *const doc)
{
    m_competitors = doc->bracketCompetitors(m_bracketId);

    bool success = m_competitors.size() > 0;

    return success;
}

GetBracketsCommand::GetBracketsCommand(QObject *parent)
    : BaseCommand(parent)
{

}

QList<Bracket> GetBracketsCommand::brackets()
{
    return m_brackets;
}

bool GetBracketsCommand::run(IDocument *const doc)
{
    m_brackets = doc->brackets();

    return m_brackets.size() > 0;
}

GetBracketCommand::GetBracketCommand(int id, QObject *parent)
    : BaseCommand(parent)
    , m_id(id)
{

}

Bracket GetBracketCommand::bracket()
{
    return m_bracket;
}

bool GetBracketCommand::run(IDocument *const doc)
{
    m_bracket = doc->bracket(m_id);
    return m_bracket.isValid();
}


AddBracketCommand::AddBracketCommand(Bracket b, QObject *parent)
    : BaseUndoCommand(parent)
    , m_bracket(b)
{
}

Bracket AddBracketCommand::bracket()
{
    return m_bracket;
}

bool AddBracketCommand::run(IDocument *const doc)
{
    m_bracket = doc->addBracket(m_bracket);
    return m_bracket.isValid();
}

bool AddBracketCommand::undo(IDocument *doc)
{
    return doc->removeBracket(m_bracket.id());
}

RemoveBracketCommand::RemoveBracketCommand(Bracket bracket, QObject *parent)
    : BaseUndoCommand(parent)
    , m_bracket(bracket)
{

}

bool RemoveBracketCommand::run(IDocument *const doc)
{
    return doc->removeBracket(m_bracket.id());
}

bool RemoveBracketCommand::undo(IDocument *doc)
{
    m_bracket = doc->addBracket(m_bracket);
    return m_bracket.isValid();
}


UpdateBracketCommand::UpdateBracketCommand(Bracket bracket, QObject *parent)
    : BaseUndoCommand(parent)
    , m_bracket(bracket)
{

}

bool UpdateBracketCommand::run(IDocument *const doc)
{
    Bracket origBracket = doc->bracket(m_bracket.id());
    if(origBracket.isValid())
    {
        if(doc->updateBracket(m_bracket))
        {
            m_bracket = origBracket;
            return true;
        }
    }
    return false;
}

bool UpdateBracketCommand::undo(IDocument *doc)
{
    // Simply run the command again.
    return run(doc);
}
