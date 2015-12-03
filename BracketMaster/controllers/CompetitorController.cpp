#include "CompetitorController.h"

#include "data/Club.h"
#include "data/Competitor.h"
#include "JudoMasterApplication.h"
#include "JMUtil.h"
#include "data/Tournament.h"
#include "data/JMDataObj.h" // TODO - delete this.

#include <QString>

CompetitorController::CompetitorController(QObject *parent) :
    BaseController(parent)
{
}

Competitor *CompetitorController::createCompetitor(QString firstName, QString lastName, JM::Gender gender, int age, double weight, JM::Rank rank, int clubId)
{
    int compId = findNextId();

    // TODO - Use Editor/Doc to create competitor
//    Competitor *competitor = new Competitor(compId, firstName, lastName, gender, age, weight, rank, clubId);

//    tournament()->competitors().append(competitor);

    Club *club = dynamic_cast<Club *>(JMApp()->clubController()->find(clubId));
    // TODO - Fix below
//    if(club)
//    {
//        club->addCompetitor(competitor);
//    }

    JMApp()->setModified(true);
    // TODO - Change signal
//    emit addedDataObj(competitor);

//    return competitor;
    return 0;
}

JMDataObj* CompetitorController::find(int id) const
{
    // Real simple linear search for now.
      // TODO - Fix Below or change method signature.
//    foreach(Competitor* competitor, tournament()->competitors())
//    {
//        if(competitor->id() == id)
//        {
//            // Found it!
//            return competitor;
//        }
//    }

    return 0;
}

void CompetitorController::add(int parentId)
{
    int compId = findNextId();
    // TODO - CHange to use commands
//    Competitor *competitor = new Competitor(compId, QString("Competitor"), QString("%1").arg(compId), JM::Female, 0, 0, JM::White, parentId);
//    tournament()->competitors().append(competitor);

    JMApp()->setModified(true);

    // TODO change signal
//    emit addedDataObj(competitor);
}

int CompetitorController::size() const
{
    if(!tournament())
        return 0;

    // TODO - use command
//    return tournament()->competitors().size();
    return 0;
}

int CompetitorController::size(int id) const
{
    int numCompetitors = 0;
    if(!tournament())
        return numCompetitors;

    // TODO - use command
//    if(id == -1)
//    {
//        numCompetitors = tournament()->competitors().size();
//    }
//    else
//    {
//        foreach(Competitor *competitor, tournament()->competitors())
//        {
//            if(competitor->clubId() == id)
//            {
//                numCompetitors++;
//            }
//        }
//    }

    return numCompetitors;
}

/**
 * @brief CompetitorController::findByName - Search for a match on both fist and last name.
 * A case insensitive search will be done
 * @param firstName
 * @param lastName
 * @return The found competitor, or null if not found.
 */
Competitor *CompetitorController::findByName(QString firstName, QString lastName)
{
    // TODO - use command
//    foreach(Competitor *competitor, tournament()->competitors())
//    {
//        if(competitor->firstName().compare(firstName, Qt::CaseInsensitive) == 0 && competitor->lastName().compare(lastName, Qt::CaseInsensitive) == 0)
//        {
//            // Found it.
//            return competitor;
//        }
//    }

    return 0;
}

/**
 * @brief Returns the list of competitors for a specified club
 * @param clubId
 * @return
 */
const QList<Competitor *> CompetitorController::clubCompetitors(int clubId) const
{
    // CAN DELETE THIS
    QList<Competitor *> competitors;

    if(tournament())
    {
        // TODO - use command
//        foreach(Competitor *competitor, tournament()->competitors())
//        {
//            if(competitor->clubId() == clubId)
//            {
//                competitors.append(competitor);
//            }
//        }
    }

    return competitors;
}

const QList<Competitor *> CompetitorController::competitors(int clubId) const
{
    if(!tournament())
    {
        return QList<Competitor *>();
    }
    // TODO - use command
//    if(clubId == -1)
//        return tournament()->competitors();
//    else
//    {
//        // TODO: I think this should be moved to the Club Controller and this controller
//        // should only return all competitors.
//        QList<Competitor *> competitors;

//        foreach(Competitor *competitor, tournament()->competitors())
//        {
//            if(competitor->clubId() == clubId)
//            {
//                competitors.append(competitor);
//            }
//        }

//        return competitors;

//    }
    return QList<Competitor *>();

}

int CompetitorController::findNextId()
{
    int id = 0;
    // TODO - remove this method
//    if(tournament())
//    {
//        foreach(Competitor* competitor, tournament()->competitors())
//        {
//            id = std::max(id, competitor->id());
//        }
//    }

    return id + 1;
}
