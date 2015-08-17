#pragma once

#include "BaseCommand.h"
#include <QObject>

class TournamentInfoCommand : public BaseCommand
{
public:
    TournamentInfoCommand(QObject* parent);
    ~TournamentInfoCommand();

    // BaseCommand interface
public slots:
    bool run();
};

