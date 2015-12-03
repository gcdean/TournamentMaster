#pragma once

#include "commands/BaseUndoCommand.h"

#include "data/Competitor.h"
#include "data/Bracket.h"


class GetBracketCompetitorsCommand : public BaseCommand
{
    Q_OBJECT
public:
    GetBracketCompetitorsCommand(int bracketId, QObject* parent = 0);

    QList<Competitor> competitors() const;

public slots:
    // BaseCommand interface
    bool run(IDocument *const doc) override;

private:
    int m_bracketId;
    QList<Competitor> m_competitors;
};
typedef QSharedPointer<GetBracketCompetitorsCommand> GetBracketCompetitorsCommandPtr;


class GetBracketsCommand : public BaseCommand
{
    Q_OBJECT

public:
    GetBracketsCommand(QObject* parent = 0);

    QList<Bracket> brackets();

public slots:
    bool run(IDocument * const doc) override;

private:
    QList<Bracket> m_brackets;
};

typedef QSharedPointer<GetBracketsCommand> GetBracketsCommandPtr;

class GetBracketCommand : public BaseCommand
{
    Q_OBJECT

public:
    GetBracketCommand(int id, QObject *parent = 0);

    Bracket bracket();

public slots:
    bool run(IDocument * const doc) override;

private:
    int m_id;
    Bracket m_bracket;

};

typedef QSharedPointer<GetBracketCommand> GetBracketCommandPtr;

class AddBracketCommand : public BaseUndoCommand
{
    Q_OBJECT
public:
    AddBracketCommand(Bracket b, QObject* parent = 0);

public slots:
    // BaseCommand interface
    bool run(IDocument *const doc) override;
    // BaseUndoCommand interface
    bool undo(IDocument *doc) override;

private:
    Bracket m_bracket;
};

typedef QSharedPointer<AddBracketCommand> AddBracketCommandPtr;

class RemoveBracketCommand : public BaseUndoCommand
{
    Q_OBJECT

public:
    RemoveBracketCommand(Bracket bracket, QObject* parent = 0);

public slots:
    // BaseCommand interface
    bool run(IDocument *const doc) override;
    // BaseUndoCommand interface
    bool undo(IDocument *doc) override;

private:
    int m_id;
    Bracket m_bracket;
};

typedef QSharedPointer<RemoveBracketCommand> RemoveBracketCommandPtr;

class UpdateBracketCommand : public BaseUndoCommand
{
    Q_OBJECT
public:
    UpdateBracketCommand(Bracket bracket, QObject* parent = 0);

public slots:
    // BaseCommand interface
    bool run(IDocument *const doc) override;

    // BaseUndoCommand interface
    bool undo(IDocument *doc) override;

private:
    Bracket m_bracket;
};

typedef QSharedPointer<UpdateBracketCommand> UpdateBracketCmdPtr;

