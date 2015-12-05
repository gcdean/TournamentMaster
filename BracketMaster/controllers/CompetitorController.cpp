#include "CompetitorController.h"

#include "commands/CompetitorCommands.h"
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

Competitor CompetitorController::createCompetitor(QString firstName, QString lastName, JM::Gender gender, int age, double weight, JM::Rank rank, int clubId)
{

    Competitor competitor;
    competitor.setFirstName(firstName);
    competitor.setLastName(lastName);
    competitor.setGender(gender);
    competitor.setAge(age);
    competitor.setWeight(weight);
    competitor.setRank(rank);
    competitor.setClubId(clubId);

    AddCompetitorCmdPtr addCmd = AddCompetitorCmdPtr(new AddCompetitorCommand(competitor));
    JMApp()->commandController()->doCommand(addCmd);

    // TODO - Change signal
//    emit addedDataObj(competitor);

//    return competitor;
    return 0;
}

void CompetitorController::updateCompetitor(Competitor competitor)
{
    UpdateCompetitorCmdPtr cmd = UpdateCompetitorCmdPtr(new UpdateCompetitorCommand(competitor));
    if(JMApp()->commandController()->doCommand(cmd))
    {
        // TODO - emit signal?
    }
}

Competitor CompetitorController::find(int id) const
{
    FindCompetitorCmdPtr cmd = FindCompetitorCmdPtr(new FindCompetitorCommand(id));

    JMApp()->commandController()->doCommand(cmd);

    return cmd->competitor();
}

void CompetitorController::add(int parentId)
{
    // TODO - CHange to use commands
    createCompetitor(QString("Competitor"), QString("Last Name"), JM::Female, 0, 0, JM::White, parentId);
//    Competitor *competitor = new Competitor(compId, QString("Competitor"), QString("%1").arg(compId), JM::Female, 0, 0, JM::White, parentId);
//    tournament()->competitors().append(competitor);

    // TODO change signal
//    emit addedDataObj(competitor);
}

int CompetitorController::size() const
{
    return competitors().size();
}

int CompetitorController::size(int id) const
{
    return competitors(id).size();
}

/**
 * @brief CompetitorController::findByName - Search for a match on both fist and last name.
 * A case insensitive search will be done
 * @param firstName
 * @param lastName
 * @return The found competitor, or null if not found.
 */
Competitor CompetitorController::findByName(QString firstName, QString lastName)
{
    // TODO - use command
    foreach(Competitor competitor, competitors())
    {
        if(competitor.firstName().compare(firstName, Qt::CaseInsensitive) == 0 && competitor.lastName().compare(lastName, Qt::CaseInsensitive) == 0)
        {
            // Found it.
            return competitor;
        }
    }

    return Competitor();
}

///**
// * @brief Returns the list of competitors for a specified club
// * @param clubId
// * @return
// */
//const QList<Competitor *> CompetitorController::clubCompetitors(int clubId) const
//{
//    // CAN DELETE THIS
//    QList<Competitor *> competitors;

//    if(tournament())
//    {
//        // TODO - use command
////        foreach(Competitor *competitor, tournament()->competitors())
////        {
////            if(competitor->clubId() == clubId)
////            {
////                competitors.append(competitor);
////            }
////        }
//    }

//    return competitors;
//}

const QList<Competitor> CompetitorController::competitors(int clubId) const
{

    // TODO - Make both commands derive from base so can reduce duplicated code.
    if(clubId == -1)
    {
        GetCompetitorsCmdPtr cmd = GetCompetitorsCmdPtr(new GetCompetitorsCommand);
        JMApp()->commandController()->doCommand(cmd);
        return cmd->competitors();
    }

    GetClubCompetitorsCmdPtr cmd = GetClubCompetitorsCmdPtr(new GetClubCompetitorsCommand(clubId));
    JMApp()->commandController()->doCommand(cmd);
    return cmd->competitors();
}
