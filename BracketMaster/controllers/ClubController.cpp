#include "ClubController.h"

#include "JudoMasterApplication.h"
#include "commands/ClubCommands.h"
#include "commands/CompetitorCommands.h"
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

    JMApp()->commandController()->doCommand(cmd);

    Club club = cmd->club();

    // TODO - Fix signal
//    emit addedDataObj(&club);

    return club;
}


void ClubController::updateClub(Club& club)
{

    QSharedPointer<UpdateClubCommand> cmd = QSharedPointer<UpdateClubCommand>(new UpdateClubCommand(club));

    if(JMApp()->commandController()->doCommand(cmd))
    {
        emit clubUpdated(&club);
    }

}

void ClubController::removeClub(int clubId)
{
    // Let's find the club.
    QSharedPointer<GetClubCommand> findCmd = QSharedPointer<GetClubCommand>(new GetClubCommand(clubId));
    if(JMApp()->commandController()->doCommand(findCmd))
    {
        Club club = findCmd->club();
        QSharedPointer<RemoveClubCommand> cmd = QSharedPointer<RemoveClubCommand>(new RemoveClubCommand(club));

        if(JMApp()->commandController()->doCommand(cmd))
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
    if(JMApp()->commandController())
    {
        QSharedPointer<GetClubsCommand> cmd = QSharedPointer<GetClubsCommand> (new GetClubsCommand);
        if(JMApp()->commandController()->doCommand(cmd))
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
    JMApp()->commandController()->doCommand(cmd);
    return cmd->club();
}

void ClubController::add(int parentId)
{
    Q_UNUSED(parentId);

    createClub();
}

int ClubController::size() const
{

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
    // TODO - use command
//    if(index < 0 || index >= tournament()->clubs().size())
//        return;

//    JMApp()->setModified(true);

//    // TODO - Fixe signal
////    emit removedDataObj(tournament()->clubs().at(index));
//    tournament()->clubs().removeAt(index);
}

int ClubController::indexOf(int id)
{
    int index = 0;
    // TODO - use command. Do we need this method?
//    foreach(const Club* club, tournament()->clubs())
//    {
//        if(id == club->id())
//            return index;
//        index++;
//    }

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


Club ClubController::find(int id) const
{
    // TODO - Fix return
//    foreach(Club *club, tournament()->clubs())
//    {
//        if(id == club->id())
//            return club;
//    }

    return 0;
}

const QList<Competitor> ClubController::competitors(int parentId) const
{
    // TODO - Fix this.
    GetClubCompetitorsCmdPtr cmd = GetClubCompetitorsCmdPtr(new GetClubCompetitorsCommand(parentId));
    JMApp()->commandController()->doCommand(cmd);

    return cmd->competitors();

}
