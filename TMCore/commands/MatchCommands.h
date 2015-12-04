#pragma once

#include "commands/BaseUndoCommand.h"

class GetAllMatchesCommand : public BaseCommand
{
    Q_OBJECT

public:
    GetAllMatchesCommand(int bracketId, QObject* parent = 0);

    const QList<Match> matches();

    // BaseCommand interface
public slots:
    bool run(IDocument *const doc) override;

private:
    int m_bracketId;
    QList<Match> m_matches;
};

typedef QSharedPointer<GetAllMatchesCommand> GetAllMatchesCmdPtr;


class BaseMatchCommand : public BaseUndoCommand
{
    Q_OBJECT

public:
    BaseMatchCommand(QObject* parent = 0);
    BaseMatchCommand(Match match, QObject* parent = 0);

    Match match() const;

protected:
    Match m_match;

};

class FindMatchCommand : public BaseMatchCommand
{
    Q_OBJECT

public:
    FindMatchCommand(int id, QObject* parent = 0);

    // BaseCommand interface
    bool isUndoable() override;

    // BaseCommand interface
public slots:
    bool run(IDocument *const doc) override;
    // BaseUndoCommand interface
    bool undo(IDocument *doc) override;

private:
    int m_matchId;
};

typedef QSharedPointer<FindMatchCommand> FindMatchCmdPtr;

class AddMatchCommand : public BaseMatchCommand
{
    Q_OBJECT

public:
    AddMatchCommand(int bracketId, QObject* parent = 0);
    AddMatchCommand(int bracketId, Match match, QObject* parent = 0);


    // BaseCommand interface
public slots:
    bool run(IDocument *const doc) override;

    // BaseUndoCommand interface
    bool undo(IDocument *doc) override;

private:
    int m_bracketId;
    bool m_useMatchObj;
};

typedef QSharedPointer<AddMatchCommand> AddMatchCmdPtr;

class RemoveMatchCommand : public BaseMatchCommand
{
    Q_OBJECT

public:
    RemoveMatchCommand(Match match, QObject* parent = 0);

public slots:
    // BaseCommand interface
    bool run(IDocument *const doc) override;

    // BaseUndoCommand interface
    bool undo(IDocument *doc) override;
};

typedef QSharedPointer<RemoveMatchCommand> RemoveMatchCmdPtr;

class UpdateMatchCommand : public BaseMatchCommand
{
    Q_OBJECT

public:
    UpdateMatchCommand(Match match, QObject* parent = 0);


public slots:
    // BaseCommand interface
    bool run(IDocument *const doc) override;

    // BaseUndoCommand interface
    bool undo(IDocument *doc) override;

};

typedef QSharedPointer<UpdateMatchCommand> UpdateMatchCmdPtr;
