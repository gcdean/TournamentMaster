#pragma once

#include "IEditor.h"

#include "data/Club.h"
#include <QSharedPointer>
#include <QStack>

class BaseUndoCommand;
class TournamentDoc;
class Club;

class TMCORE_DLLSPEC TournamentEditor : public IEditor
{
public:
    TournamentEditor(QSharedPointer<TournamentDoc> doc);
    ~TournamentEditor();

    // IEditor interface
public:
    bool doCommand(QSharedPointer<BaseCommand> command) override;
    bool undoCommand() override;
    const QList<QSharedPointer<BaseUndoCommand>> undoCommandList() const override;
    const QList<QSharedPointer<BaseUndoCommand>> redoCommandList() const override;
    bool load(QString name) override;
    bool save() override;
    bool saveAs(QString name) override;

    // Club methods.
    const QList<Club> clubs() override;
    bool addClub(Club club) override;
    Club createClub() override;
    Club findClub(int id) override;
    bool updateClub(Club club) override;
    bool removeClub(int id) override;




private:
    QSharedPointer<TournamentDoc> m_document;
    QStack<QSharedPointer<BaseUndoCommand>> m_undoStack;
    QStack<QSharedPointer<BaseUndoCommand>> m_redoStack;


};


