#pragma once

#include <QObject>

class BaseUndoCommand : public BaseCommand
{
public:
    BaseUndoCommand();
    ~BaseUndoCommand();
};


