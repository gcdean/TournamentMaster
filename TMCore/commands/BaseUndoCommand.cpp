#include "BaseUndoCommand.h"

BaseUndoCommand::BaseUndoCommand(QObject *parent)
    : BaseCommand(parent)
{

}

BaseUndoCommand::~BaseUndoCommand()
{

}



bool BaseUndoCommand::isUndoable()
{
    return true;
}
