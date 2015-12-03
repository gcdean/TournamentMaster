#include "BracketController.h"

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
    const QList<Bracket *> NOBRACKETS;
}

BracketController::BracketController(QObject *parent)
    : BaseController(parent)
{
}

const QList<Bracket *> *BracketController::brackets() const
{
    if(!tournament())
        return &NOBRACKETS;

    // TODO - Use command
//    return &tournament()->brackets();
    return &NOBRACKETS;

}

int BracketController::size() const
{
    if(!tournament())
        return 0;

    // TODO - Use command
//    return tournament()->brackets().size();
    return 0;
}

int BracketController::size(int id) const
{
    Q_UNUSED(id);

    return size();
}

void BracketController::add(int parentId)
{
    Q_UNUSED(parentId);

    if(!tournament())
    {
        return;
    }
    int id = findNextId();
    Bracket *bracket = new Bracket(id);

    // TODO - use command
//    tournament()->brackets().append(bracket);
//    JMApp()->setModified(true);
    // TODO - Change signature
//    emit addedDataObj(bracket);

}

void BracketController::remove(int id)
{
    if(!tournament())
    {
        return;
    }

    Bracket* bracket = dynamic_cast<Bracket *>(find(id));
    if(bracket)
    {
        // TODO - Change signature.
//        emit removedDataObj(bracket);

        // TODO - Use command
//        tournament()->brackets().removeOne(bracket);
        JMApp()->setModified(true);
    }
}

void BracketController::removeIndex(int index)
{
    // TODO - use command
//    if(!tournament() || index < 0 || index >= tournament()->brackets().size())
//    {
//        return;
//    }

    // TODO - Change signature
//    emit removedDataObj(tournament()->brackets().at(index));
    // TODO - use command
//    tournament()->brackets().removeAt(index);
    JMApp()->setModified(true);
}



JMDataObj* BracketController::find(int id) const
{
    // TODO - Change return type.
//    foreach (Bracket *bracket, tournament()->brackets())
//    {
//        if(bracket->id() == id)
//        {
//            return bracket;
//        }
//    }

    return 0;
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

void BracketController::removeCompetitorFromBracket(int bracketId, int competitorId)
{
    qDebug() << "BracketController - Remove competitor " << competitorId << " from Bracket " << bracketId;
    Bracket *bracket = dynamic_cast<Bracket *>(find(bracketId));
    if(bracket)
    {
        int index = 0;
        // TODO - Use command
//        foreach(Competitor *competitor, bracket->competitors())
//        {
//            if(competitor->id() == competitorId)
//            {
//                bracket->removeCompetitor(index);
//                emit competitorRemoved(index);
//                JMApp()->setModified(true);
//                break;
//            }
//            index++;
//        }
    }
}

const QList<Competitor *> BracketController::competitors(int parentId) const
{
    if(!tournament())
        return QList<Competitor *>();

    if(parentId != -1)
    {
        // First, find the bracket.
        // TODO - use command
//        foreach(Bracket *bracket, tournament()->brackets())
//        {
//            if(bracket->id() == parentId)
//            {
//                // TODO - Use command.
////                return bracket->competitors();
//            }
//        }
        return QList<Competitor *>();
    }

    const QList<Competitor *> allComps = JMApp()->competitorController()->competitors();

    return allComps;
}

const QList<Bracket *> BracketController::competitorBrackets(int competitorId) const
{
    // Find the brackets that the specified competitor is in.
    QList <Bracket *> brackets;
    // TODO - use command
//    foreach(Bracket *bracket, tournament()->brackets())
//    {
        // TODO - Use command
//        foreach(Competitor *competitor, bracket->competitors())
//        {
//            if(competitorId == competitor->id())
//            {
//                brackets.append(bracket);
//                break;
//            }
//        }
//    }

    return brackets;
}

int BracketController::findNextId()
{
    int nextId = 0;
    if(tournament())
    {
//        foreach (Bracket* bracket, tournament()->brackets())
//        {

//            nextId = std::max(nextId, bracket->id());
//        }
    }

    // We now have the max club id.
    nextId++;

    return nextId;
}

