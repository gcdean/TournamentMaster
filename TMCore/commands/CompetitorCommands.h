#pragma once

#include "BaseUndoCommand.h"
#include "data/Competitor.h"


class GetCompetitorsCommand : public BaseCommand
{
    Q_OBJECT
public:
    GetCompetitorsCommand(QObject* parent = 0);

    QList<Competitor> competitors();

public slots:
    // BaseCommand interface
    bool run(IDocument *const doc) override;

protected:
    QList<Competitor> m_competitors;
};

typedef QSharedPointer<GetCompetitorsCommand> GetCompetitorsCmdPtr;

class GetClubCompetitorsCommand : public GetCompetitorsCommand
{
    Q_OBJECT

public:
    GetClubCompetitorsCommand(int clubId, QObject* parent = 0);


    // BaseCommand interface
public slots:
    bool run(IDocument *const doc) override;


private:
    int m_clubId;
};

typedef QSharedPointer<GetClubCompetitorsCommand> GetClubCompetitorsCmdPtr;


///
/// \brief Base abstract class for commands dealing with a single
/// competitor. Used to have a single method to publicly access
/// the Competitor data member.
///
class BaseSingleCompetitorCommand : public BaseUndoCommand
{
    Q_OBJECT
public:
    BaseSingleCompetitorCommand(QObject* parent = 0);
    BaseSingleCompetitorCommand(Competitor competitor, QObject* parent = 0);

    Competitor competitor();

protected:
    Competitor m_competitor;

};

class FindCompetitorCommand : public BaseSingleCompetitorCommand
{
    Q_OBJECT

public:
    FindCompetitorCommand(int id, QObject* parent = 0);

    // BaseCommand interface
public:
    bool isUndoable() override;

public slots:
    bool run(IDocument *const doc) override;

    // BaseUndoCommand interface
    bool undo(IDocument *doc) override;

private:
    int m_id;

};

typedef QSharedPointer<FindCompetitorCommand> FindCompetitorCmdPtr;

class AddCompetitorCommand : public BaseSingleCompetitorCommand
{
    Q_OBJECT

public:
    AddCompetitorCommand(QObject* parent = 0);
    AddCompetitorCommand(Competitor competitor, QObject* parent = 0);

public slots:
    // BaseCommand interface
    bool run(IDocument *const doc) override;

    // BaseUndoCommand interface
    bool undo(IDocument *doc) override;

private:
    bool m_addEmptyCompetitor;
};

typedef QSharedPointer<AddCompetitorCommand> AddCompetitorCmdPtr;

class UpdateCompetitorCommand : public BaseSingleCompetitorCommand
{
    Q_OBJECT

public:
    UpdateCompetitorCommand(Competitor competitor, QObject* parent = 0);

public slots:
    // BaseCommand interface
    bool run(IDocument *const doc) override;

    // BaseUndoCommand interface
    bool undo(IDocument *doc) override;

};

typedef QSharedPointer<UpdateCompetitorCommand> UpdateCompetitorCmdPtr;

class RemoveCompetitorCommand : public BaseSingleCompetitorCommand
{
    Q_OBJECT

public:
    RemoveCompetitorCommand(Competitor competitor, QObject* parent = 0);

public slots:
    // BaseCommand interface
    bool run(IDocument *const doc) override;

    // BaseUndoCommand interface
    bool undo(IDocument *doc) override;
};

typedef QSharedPointer<RemoveCompetitorCommand> RemoveCompetitorCmdPtr;
