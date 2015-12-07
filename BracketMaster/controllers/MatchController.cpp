#include "MatchController.h"

#include "commands/MatchCommands.h"
#include "data/Match.h"
#include "data/Tournament.h"
#include "JudoMasterApplication.h"

MatchController::MatchController(QObject *parent)
    : BaseController(parent)
{
}


void MatchController::add(int parentId)
{

    Match match;
    match.setBracketId(parentId);

    AddMatchCmdPtr cmd = AddMatchCmdPtr(new AddMatchCommand(parentId, match));
    if(JMApp()->commandController()->doCommand(cmd))
    {
        emit matchAdded(cmd->match().id());
    }

}

void MatchController::update(Match match)
{
    UpdateMatchCmdPtr cmd = UpdateMatchCmdPtr(new UpdateMatchCommand(match));

    JMApp()->commandController()->doCommand(cmd);
}

Match MatchController::find(int id) const
{
    FindMatchCmdPtr cmd = FindMatchCmdPtr(new FindMatchCommand(id));
    JMApp()->commandController()->doCommand(cmd);

    return cmd->match();
}

void MatchController::remove(int id)
{
    Match match = find(id);
    RemoveMatchCmdPtr cmd = RemoveMatchCmdPtr(new RemoveMatchCommand(match));

    if(JMApp()->commandController()->doCommand(cmd))
    {
        emit matchRemoved(id);
    }
}

int MatchController::size() const
{
    return size(-1);
}

int MatchController::size(int id) const
{
    return matches(id).size();
}

const QList<Match> MatchController::matches(int bracketId) const
{
    GetAllMatchesCmdPtr cmd = GetAllMatchesCmdPtr(new GetAllMatchesCommand(bracketId));
    JMApp()->commandController()->doCommand(cmd);

    return cmd->matches();
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
