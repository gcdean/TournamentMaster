#include "MatchController.h"

#include "data/Match.h"
#include "JudoMasterApplication.h"
#include "data/Tournament.h"

MatchController::MatchController(QObject *parent)
    : BaseController(parent)
{
}


void MatchController::add(int parentId)
{

    Match *match = new Match(findNextId());
    match->setBracketId(parentId);

    // TODO - use command
//    tournament()->matches().append(match);

    JMApp()->setModified(true);
    // TODO - fix signal signature
//    emit addedDataObj(match);
}

JMDataObj *MatchController::find(int id) const
{
    // TODO - Change return value.
//    foreach(Match *match, tournament()->matches())
//    {
//        if(id == match->id())
//        {
//            return match;
//        }
//    }

    return nullptr;
}

int MatchController::findNextId()
{
    int nextId = 0;
    if(tournament())
    {
        // TODO - Remove this method
//        foreach (Match* match, tournament()->matches())
//        {

//            nextId = std::max(nextId, match->id());
//        }
    }

    // We now have the max match id.
    nextId++;

    return nextId;
}

void MatchController::remove(int id)
{
    Q_UNUSED(id);
}

int MatchController::size() const
{
    return size(-1);
}

int MatchController::size(int id) const
{
    return matches(id).size();
}

const QList<Match *> MatchController::matches(int bracketId) const
{
//    if(bracketId == -1)
//        return tournament()->matches();

    // TODO - use command
    QList<Match *> matches;
//    foreach(Match *match, tournament()->matches())
//    {
//        if(bracketId == match->bracketId())
//        {
//            matches.append(match);
//        }
//    }

    return matches;
}



int MatchController::indexOf(int id)
{
    int index = 0;
    // TODO - use command. Do we need this method?
//    foreach(Match *match, tournament()->matches())
//    {
//        if(id == match->id())
//        {
//            return index;
//        }
//        index++;
//    }

    return -1;
}
