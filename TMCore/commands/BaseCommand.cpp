#include "BaseCommand.h"

BaseCommand::BaseCommand(QObject *parent)
    : QObject(parent)
{

}

BaseCommand::~BaseCommand()
{

}

bool BaseCommand::isUndoable()
{
    return false;
}

bool BaseCommand::done(bool success)
{
    if(success)
        emit commandSuccessful();
    else
        emit commandFailed();

    emit commandComplete();

    return success;
}

