#pragma once

#include "commands/BaseUndoCommand.h"

#include "data/Tournament.h"

class GetTournamentCommand : public BaseCommand
{
    Q_OBJECT

public:
    GetTournamentCommand(QObject* parent = 0);

    Tournament tournament();

    // BaseCommand interface
public slots:
    bool run(IDocument *const doc) override;

private:
    Tournament m_tournament;
};

typedef QSharedPointer<GetTournamentCommand> GetTournamentCmdPtr;

class UpdateTournamentCommand : public BaseUndoCommand
{
    Q_OBJECT

public:
    UpdateTournamentCommand(Tournament src, QObject* parent = 0);

    Tournament tournament();

public slots:
    // BaseCommand interface
    bool run(IDocument *const doc) override;

    // BaseUndoCommand interface
    bool undo(IDocument *doc) override;

private:
    Tournament m_tournament;

};

typedef QSharedPointer<UpdateTournamentCommand> UpdateTournamentCmdPtr;
