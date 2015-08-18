#pragma once

#include "BaseCommand.h"

class CreateTournamentCommand : public BaseCommand
{
    Q_OBJECT

public:
    CreateTournamentCommand(QObject *parent);
    ~CreateTournamentCommand();

    // BaseCommand interface
public slots:
    bool run();
};

