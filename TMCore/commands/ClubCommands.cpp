
#include "commands/ClubCommands.h"

GetClubsCommand::GetClubsCommand(QObject *parent)
    : BaseCommand(parent)
{

}

bool GetClubsCommand::run(IEditor *const editor)
{
    m_clubs = editor->clubs();
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

bool GetClubCommand::run(IEditor *const editor)
{
    bool found = false;
    foreach(Club club, editor->clubs())
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

bool CreateClubCommand::run(IEditor *const editor)
{
    m_club = editor->createClub();
    return m_club.isValid();
}

bool CreateClubCommand::undo(IEditor *editor)
{
    return editor->removeClub(m_club.id());
}


UpdateClubCommand::UpdateClubCommand(Club club, QObject *parent)
    : BaseUndoCommand(parent)
    , m_updatedClub(club)
{

}

bool UpdateClubCommand::run(IEditor *const editor)
{
    m_origClub = editor->findClub(m_updatedClub.id());
    if(m_origClub.isValid())
    {
        return editor->updateClub(m_updatedClub);
    }

    return false;
}

bool UpdateClubCommand::undo(IEditor *editor)
{
    return editor->updateClub(m_origClub);
}

RemoveClubCommand::RemoveClubCommand(Club club, QObject *parent)
    : BaseUndoCommand(parent)
    , m_origClub(club)
{

}

bool RemoveClubCommand::run(IEditor *const editor)
{
    return editor->removeClub(m_origClub.id());
}

bool RemoveClubCommand::undo(IEditor *editor)
{
    return editor->addClub(m_origClub);
}
