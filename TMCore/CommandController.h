#pragma once

#include "IEditor.h"

#include "data/Club.h"
#include <QSharedPointer>
#include <QStack>

class BaseUndoCommand;
class IDocument;
class Club;

class TMCORE_DLLSPEC CommandController// : public IEditor
{
public:
    CommandController(QSharedPointer<IDocument> doc);
    ~CommandController();

    // IEditor interface
public:
    bool doCommand(QSharedPointer<BaseCommand> command);
    bool undoCommand();
    const QList<QSharedPointer<BaseUndoCommand>> undoCommandList() const;
    const QList<QSharedPointer<BaseUndoCommand>> redoCommandList() const;
//    bool load(QString name) override;
//    bool save() override;
//    bool saveAs(QString name) override;

//    // Club methods.
//    const QList<Club> clubs() override;
//    bool addClub(Club club) override;
//    Club createClub() override;
//    Club findClub(int id) override;
//    bool updateClub(Club club) override;
//    bool removeClub(int id) override;

//    // Bracket methods
//    const QList<Bracket> brackets() override;
//    const Bracket bracket(int id) override;
//    const QList<Competitor> bracketCompetitors(int bracketId) override;
//    bool addBracket(Bracket bracket) override;
//    bool updateBracket(Bracket bracket) override;
//    bool removeBracket(int id) override;



private:
    QSharedPointer<IDocument> m_document;
    QStack<QSharedPointer<BaseUndoCommand>> m_undoStack;
    QStack<QSharedPointer<BaseUndoCommand>> m_redoStack;


};


