#pragma once

#include "commands/BaseCommand.h"
#include <QObject>

class TournamentInfoCommand : public BaseCommand
{
public:
    TournamentInfoCommand(QObject* parent);
    ~TournamentInfoCommand();

    // BaseCommand interface
public slots:
    bool run(IDocument* const doc) override;
};

