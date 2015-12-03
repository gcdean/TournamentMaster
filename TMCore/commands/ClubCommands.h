#pragma once


#include "commands/BaseUndoCommand.h"
#include "data/Club.h"

class GetClubsCommand : public BaseCommand
{
    Q_OBJECT
public:
    GetClubsCommand(QObject *parent = 0);

    const QList<Club> clubs();

public slots:
    // BaseCommand interface
    bool run(IDocument *const doc);

private:
    QList<Club> m_clubs;
};


class GetClubCommand : public BaseCommand
{
    Q_OBJECT

public:
    GetClubCommand(int id, QObject* parent = 0);
    GetClubCommand(QString name, QObject* parent = 0);

    Club club();

public slots:
    // BaseCommand interface
    bool run(IDocument *const doc);

private:
    bool m_byId;
    int m_id;
    QString m_name;
    Club m_club;

};


class CreateClubCommand : public BaseUndoCommand
{
    Q_OBJECT

public:
    CreateClubCommand(QObject* parent = 0);

    Club club();

    // BaseUndoCommand interface
public slots:
    bool run(IDocument* const doc) override;
    bool undo(IDocument *doc) override;

private:
    Club m_club;
};


class UpdateClubCommand : public BaseUndoCommand
{
    Q_OBJECT

public:
    UpdateClubCommand(Club club, QObject* parent = 0);

public slots:
    // BaseCommand interface
    bool run(IDocument *const doc) override;
    // BaseUndoCommand interface
    bool undo(IDocument *doc) override;

private:
    Club m_updatedClub;
    Club m_origClub;
};

class RemoveClubCommand : public BaseUndoCommand
{
    Q_OBJECT

public:
    RemoveClubCommand(Club club, QObject* parent = 0);

public slots:
    // BaseCommand interface
    bool run(IDocument *const doc) override;
    // BaseUndoCommand interface
    bool undo(IDocument *doc) override;

private:
    Club m_origClub;

};