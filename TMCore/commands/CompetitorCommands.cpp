#include "CompetitorCommands.h"

#include "data/Bracket.h"


GetCompetitorsCommand::GetCompetitorsCommand(QObject *parent)
    : BaseCommand(parent)
{

}

QList<Competitor> GetCompetitorsCommand::competitors()
{
    return m_competitors;
}

bool GetCompetitorsCommand::run(IDocument *const doc)
{
    m_competitors =  doc->competitors();

    return m_competitors.size() > 0;
}

GetClubCompetitorsCommand::GetClubCompetitorsCommand(int clubId, QObject *parent)
    : GetCompetitorsCommand(parent)
    , m_clubId(clubId)
{

}

bool GetClubCompetitorsCommand::run(IDocument *const doc)
{
    QList<Competitor> allComp = doc->competitors();

    foreach(Competitor competitor, allComp)
    {
        if(competitor.clubId() == m_clubId)
        {
            m_competitors.append(competitor);
        }
    }

    return m_competitors.size() > 0;
}

//GetBracketCompetitorsCommand::GetBracketCompetitorsCommand(int bracketId, QObject *parent)
//    : GetCompetitorsCommand(parent)
//    , m_bracketId(bracketId)
//{

//}

//bool GetBracketCompetitorsCommand::run(IDocument *const doc)
//{
//    Bracket bracket = doc->bracket(m_bracketId);

//    foreach(int id, bracket.competitorIds())
//    {
//        Competitor c = doc->competitor(id);
//        m_competitors.append(c);
//    }

//    return m_competitors.size() > 0;
//}


BaseSingleCompetitorCommand::BaseSingleCompetitorCommand(QObject *parent)
    : BaseUndoCommand(parent)
{

}

BaseSingleCompetitorCommand::BaseSingleCompetitorCommand(Competitor competitor, QObject *parent)
    : BaseUndoCommand(parent)
    , m_competitor(competitor)
{

}

Competitor BaseSingleCompetitorCommand::competitor()
{
    return m_competitor;
}

AddCompetitorCommand::AddCompetitorCommand(QObject *parent)
    : BaseSingleCompetitorCommand(parent)
    , m_addEmptyCompetitor(true)
{

}

AddCompetitorCommand::AddCompetitorCommand(Competitor competitor, QObject *parent)
    : BaseSingleCompetitorCommand(competitor, parent)
    , m_addEmptyCompetitor(false)
{
}

bool AddCompetitorCommand::run(IDocument *const doc)
{
    bool success = false;
    if(m_addEmptyCompetitor)
    {
        m_competitor = doc->addCompetitor();
        success = m_competitor.isValid();
    }
    else
    {
        success = doc->addCompetitor(m_competitor);
    }

    return success;
}

bool AddCompetitorCommand::undo(IDocument *doc)
{
    bool success = false;
    if(m_competitor.isValid())
    {
        success = doc->removeCompetitor(m_competitor.id());
    }

    return success;
}

UpdateCompetitorCommand::UpdateCompetitorCommand(Competitor competitor, QObject *parent)
    : BaseSingleCompetitorCommand(competitor, parent)
{

}

bool UpdateCompetitorCommand::run(IDocument *const doc)
{
    bool success = false;
    // Find the original one.
    Competitor orig = doc->competitor(m_competitor.id());
    if(orig.isValid())
    {
        if(doc->updateCompetitor(m_competitor))
        {
            m_competitor = orig;
            success = true;
        }
    }

    return success;
}

bool UpdateCompetitorCommand::undo(IDocument *doc)
{
    // The current competitor should be the original so we should be able
    // to simply re-run the command.
    return run(doc);
}


RemoveCompetitorCommand::RemoveCompetitorCommand(Competitor competitor, QObject *parent)
    : BaseSingleCompetitorCommand(competitor, parent)
{

}

bool RemoveCompetitorCommand::run(IDocument *const doc)
{
    return doc->removeCompetitor(m_competitor.id());
}

bool RemoveCompetitorCommand::undo(IDocument *doc)
{
    return doc->addCompetitor(m_competitor);
}


FindCompetitorCommand::FindCompetitorCommand(int id, QObject *parent)
    : BaseSingleCompetitorCommand(parent)
    , m_id(id)
{

}

bool FindCompetitorCommand::isUndoable()
{
    // We are overriding this command because we don't want the find
    // to be undoable but do want it to be derived from the BaseSingleCompetitor
    // command in order ot use the competitor() method.
    return false;
}

bool FindCompetitorCommand::run(IDocument *const doc)
{
    m_competitor = doc->competitor(m_id);

    return m_competitor.isValid();
}

bool FindCompetitorCommand::undo(IDocument *doc)
{
    Q_UNUSED(doc);
    Q_ASSERT(false);

    return false;
}
