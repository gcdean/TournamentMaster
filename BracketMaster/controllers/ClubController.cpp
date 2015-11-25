#include "ClubController.h"

#include "JudoMasterApplication.h"
#include "commands/ClubCommands.h"
#include "data/Club.h"
#include "data/Tournament.h"

#include <QDebug>

ClubController::ClubController(QObject *parent) :
    BaseController(parent)
{
}

Club ClubController::createClub()
{
    QSharedPointer<CreateClubCommand> cmd = QSharedPointer<CreateClubCommand>(new CreateClubCommand());

    JMApp()->tournamentEditor()->doCommand(cmd);

    Club club = cmd->club();

    emit addedDataObj(&club);

    return club;
}


void ClubController::updateClub(Club& club)
{

    QSharedPointer<UpdateClubCommand> cmd = QSharedPointer<UpdateClubCommand>(new UpdateClubCommand(club));

    if(JMApp()->tournamentEditor()->doCommand(cmd))
    {
        emit clubUpdated(&club);
    }

}

void ClubController::removeClub(int clubId)
{
    // Let's find the club.
    QSharedPointer<GetClubCommand> findCmd = QSharedPointer<GetClubCommand>(new GetClubCommand(clubId));
    if(JMApp()->tournamentEditor()->doCommand(findCmd))
    {
        Club club = findCmd->club();
        QSharedPointer<RemoveClubCommand> cmd = QSharedPointer<RemoveClubCommand>(new RemoveClubCommand(club));

        if(JMApp()->tournamentEditor()->doCommand(cmd))
        {
            emit clubRemoved(&club);
        }
    }
}

namespace
{
    const QList<Club> NOCLUBS;
    const QList<Competitor *> NOCOMPETITORS;
}

const QList<Club> ClubController::clubs() const
{
    if(JMApp()->tournamentEditor())
    {
        QSharedPointer<GetClubsCommand> cmd = QSharedPointer<GetClubsCommand> (new GetClubsCommand);
        if(JMApp()->tournamentEditor()->doCommand(cmd))
        {
            return cmd->clubs();
        }
    }

    return NOCLUBS;
}

Club ClubController::findClubByName(QString name)
{
    int firstSpace = name.indexOf(' ');
    if(firstSpace != -1)
    {
//        qDebug() << "Truncating (" << name << ")";
        name.truncate(firstSpace);
//        qDebug() << "Truncated Name is: (" << name << ")";
    }

    QSharedPointer<GetClubCommand> cmd = QSharedPointer<GetClubCommand>( new GetClubCommand(name));
    JMApp()->tournamentEditor()->doCommand(cmd);
    return cmd->club();
}

void ClubController::add(int parentId)
{
    Q_UNUSED(parentId);

    if(!tournament())
        return;

    createClub();
}

int ClubController::size() const
{
//    if(!tournament())
//    {
//        return 0;
//    }

//    return tournament()->clubs().size();

    return clubs().size();
}

int ClubController::size(int id) const
{
    Q_UNUSED(id);
    // For now, just return the size.
    return size();
}

void ClubController::remove(int id)
{
    removeClub(id);
}

void ClubController::removeIndex(int index)
{
    if(index < 0 || index >= tournament()->clubs().size())
        return;

    JMApp()->setModified(true);
    emit removedDataObj(tournament()->clubs().at(index));
    tournament()->clubs().removeAt(index);
}

int ClubController::indexOf(int id)
{
    int index = 0;
    foreach(const Club* club, tournament()->clubs())
    {
        if(id == club->id())
            return index;
        index++;
    }

    return -1;
}

//Club* ClubController::findClub(int id)
//{
//    Club* club = 0;

//    if(!tournament())
//        return club;

//    for(int x = 0; x < tournament()->clubs().size() && !club; x++)
//    {
//        Club* temp = tournament()->clubs()[x];
//        if(temp->id() == id)
//        {
//            club = temp;
//        }
//    }
//    return club;
//}

int ClubController::findNextId()
{
    int nextId = 0;
    if(tournament())
    {
        foreach (Club* club, tournament()->clubs())
        {

            nextId = std::max(nextId, club->id());
        }
    }

    // We now have the max club id.
    nextId++;

    return nextId;
}


JMDataObj *ClubController::find(int id) const
{
    foreach(Club *club, tournament()->clubs())
    {
        if(id == club->id())
            return club;
    }

    return 0;
}

const QList<Competitor *> ClubController::competitors(int parentId) const
{
    Club *club = dynamic_cast<Club *>(find(parentId));

    if(club)
    {
        return club->competitors();
    }

    return NOCOMPETITORS;
}
