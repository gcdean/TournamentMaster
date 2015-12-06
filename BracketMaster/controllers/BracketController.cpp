#include "BracketController.h"

#include "commands/BracketCommands.h"

#include "data/Bracket.h"
#include "data/Competitor.h"
#include "data/Tournament.h"
#include "data/JMDataObj.h" // TODO - delete this.

#include "JudoMasterApplication.h"  // DEBUG ONLY. DELETE
#include "data/Competitor.h"             // DEBUG ONLY. DELETE

#include <QDebug>
#include <QList>

namespace
{
    const QList<Bracket> NOBRACKETS;
}

BracketController::BracketController(QObject *parent)
    : BaseController(parent)
{
}

const QList<Bracket> BracketController::brackets() const
{

    GetBracketsCommandPtr cmd = GetBracketsCommandPtr(new GetBracketsCommand);
    JMApp()->commandController()->doCommand(cmd);

    return cmd->brackets();
}

int BracketController::size() const
{
    return brackets().size();
}

int BracketController::size(int id) const
{
    Q_UNUSED(id);

    return size();
}

void BracketController::add(int parentId)
{
    Q_UNUSED(parentId);

    Bracket bracket;
    AddBracketCommandPtr cmd = AddBracketCommandPtr(new AddBracketCommand(bracket));

    if(JMApp()->commandController()->doCommand(cmd))
    {
        emit bracketAdded(cmd->bracket().id());
    }

}

void BracketController::remove(int id)
{
    Bracket bracket = findById(id);
    if(bracket.isValid())
    {

        RemoveBracketCommandPtr cmd = RemoveBracketCommandPtr(new RemoveBracketCommand(bracket));
        if(JMApp()->commandController()->doCommand(cmd))
        {
            emit bracketRemoved(id);
        }
    }
}

void BracketController::removeIndex(int index)
{
    Q_ASSERT(false);
    // TODO - use command
//    if(!tournament() || index < 0 || index >= tournament()->brackets().size())
//    {
//        return;
//    }

    // TODO - Change signature
//    emit removedDataObj(tournament()->brackets().at(index));
    // TODO - use command
//    tournament()->brackets().removeAt(index);
}



Bracket BracketController::find(int id) const
{
    GetBracketCommandPtr cmd = GetBracketCommandPtr(new GetBracketCommand(id));
    JMApp()->commandController()->doCommand(cmd);

    return cmd->bracket();
}

Bracket BracketController::findById(int id) const
{
    GetBracketCommandPtr cmd = GetBracketCommandPtr(new GetBracketCommand(id));
    JMApp()->commandController()->doCommand(cmd);

    return cmd->bracket();
}

int BracketController::indexOf(int id)
{
    int index = 0;
    // TODO - use command
//    foreach (Bracket *bracket, tournament()->brackets())
//    {
//        if(bracket->id() == id)
//        {
//            return index;
//        }
//        index++;
//    }

    return -1;
}

void BracketController::updateBracket(Bracket bracket)
{
    UpdateBracketCmdPtr cmd = UpdateBracketCmdPtr(new UpdateBracketCommand(bracket));
    JMApp()->commandController()->doCommand(cmd);
    // TODO - emit signal?
}

void BracketController::removeCompetitorFromBracket(int bracketId, int competitorId)
{
    qDebug() << "BracketController - Remove competitor " << competitorId << " from Bracket " << bracketId;
    Bracket bracket = find(bracketId);
    if(bracket.isValid())
    {
        bracket.removeCompetitor(competitorId);

        UpdateBracketCmdPtr cmd = UpdateBracketCmdPtr(new UpdateBracketCommand(bracket));
        JMApp()->commandController()->doCommand(cmd);
    }
}

const QList<Competitor> BracketController::competitors(int parentId) const
{
    QList<Competitor> competitors;

    if(parentId != -1)
    {
        // First, find the bracket.
        GetBracketCompetitorsCommandPtr cmd = GetBracketCompetitorsCommandPtr(new GetBracketCompetitorsCommand(parentId));
        if(JMApp()->commandController()->doCommand(cmd))
        {
            competitors = cmd->competitors();
        }
    }

    // NOTE - Not returning all comopetitors if the bracket id is -1.
    return competitors;
}

const QList<Bracket> BracketController::competitorBrackets(int competitorId) const
{
    // Find the brackets that the specified competitor is in.
    QList <Bracket > brackets;
    GetBracketsCommandPtr cmd = GetBracketsCommandPtr(new GetBracketsCommand);
    if(JMApp()->commandController()->doCommand(cmd))
    {

        foreach(Bracket bracket, cmd->brackets())
        {
            foreach(int id, bracket.competitorIds())
            {
                if(competitorId == id)
                {
                    brackets.append(bracket);
                    break;
                }
            }
        }
    }

    return brackets;
}


