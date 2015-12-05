#pragma once

#include "commands/BaseCommand.h"

class CloseCommand : public BaseCommand
{
public:
    CloseCommand();
    ~CloseCommand();

    // BaseCommand interface
public slots:
    bool run(IDocument* const doc);
};

typedef QSharedPointer<CloseCommand> CloseCmdPtr;

