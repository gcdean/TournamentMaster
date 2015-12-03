
#include "commands/ClubCommands.h"

GetClubsCommand::GetClubsCommand(QObject *parent)
    : BaseCommand(parent)
{

}

bool GetClubsCommand::run(IDocument *const doc)
{
    m_clubs = doc->clubs();
    return true;
}

const QList<Club> GetClubsCommand::clubs()
{
    return m_clubs;
}


GetClubCommand::GetClubCommand(int id, QObject *parent)
    : BaseCommand(parent)
    , m_byId(true)
{
    m_id = id;
}

GetClubCommand::GetClubCommand(QString name, QObject *parent)
    : BaseCommand(parent)
    , m_byId(false)
{
    m_name = name;
}

Club GetClubCommand::club()
{
    return m_club;
}

bool GetClubCommand::run(IDocument *const doc)
{
    bool found = false;
    foreach(Club club, doc->clubs())
    {
        if((m_byId && club.id() == m_id) || (!m_byId && club.clubName() == m_name))
        {
            m_club = club;
            found = true;
            break;
        }
    }

    return found;
}

CreateClubCommand::CreateClubCommand(QObject *parent)
    : BaseUndoCommand(parent)
{

}

Club CreateClubCommand::club()
{
    return m_club;
}

bool CreateClubCommand::run(IDocument *const doc)
{
    m_club = doc->addClub();
    return m_club.isValid();
}

bool CreateClubCommand::undo(IDocument *doc)
{
    return doc->removeClub(m_club.id());
}


UpdateClubCommand::UpdateClubCommand(Club club, QObject *parent)
    : BaseUndoCommand(parent)
    , m_updatedClub(club)
{

}

bool UpdateClubCommand::run(IDocument *const doc)
{
    m_origClub = doc->club(m_updatedClub.id());
    if(m_origClub.isValid())
    {
        return doc->updateClub(m_updatedClub);
    }

    return false;
}

bool UpdateClubCommand::undo(IDocument *doc)
{
    return doc->updateClub(m_origClub);
}

RemoveClubCommand::RemoveClubCommand(Club club, QObject *parent)
    : BaseUndoCommand(parent)
    , m_origClub(club)
{

}

bool RemoveClubCommand::run(IDocument *const doc)
{
    return doc->removeClub(m_origClub.id());
}

bool RemoveClubCommand::undo(IDocument *doc)
{
    return doc->addClub(m_origClub);
}
