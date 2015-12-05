#pragma once

#include "commands/BaseCommand.h"

class CreateTournamentCommand : public BaseCommand
{
    Q_OBJECT

public:
    CreateTournamentCommand(QObject *parent = 0);
    ~CreateTournamentCommand();

    // BaseCommand interface
public slots:
    bool run(IDocument* const doc);
};

typedef QSharedPointer<CreateTournamentCommand> CreateTournamentCmdPtr;


