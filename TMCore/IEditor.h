#pragma once

#include "TMCore.h"

#include <QString>

#include "data/Bracket.h"
#include "data/Club.h"
#include "data/Competitor.h"

class BaseCommand;
class BaseUndoCommand;

class TMCORE_DLLSPEC IEditor
{
public:
    virtual ~IEditor() {}

    virtual bool doCommand(QSharedPointer<BaseCommand> command) = 0;
    virtual bool undoCommand() = 0;

    // Add ability to undo multiple commands?

    virtual const QList<QSharedPointer<BaseUndoCommand>> undoCommandList() const = 0;
    virtual const QList<QSharedPointer<BaseUndoCommand>> redoCommandList() const = 0;



    //  Below are the methods that are to be used by commands to update the document.

    virtual bool load(QString name) = 0;
    virtual bool save() = 0;
    virtual bool saveAs(QString name) = 0;

    // Club methods.
    virtual const QList<Club> clubs() = 0;
    virtual bool addClub(Club club) = 0;
    virtual Club createClub() = 0;
    virtual Club findClub(int id) = 0;
    virtual bool updateClub(Club club) = 0;
    virtual bool removeClub(int id) = 0;

    // Bracket methods.
    virtual const QList<Bracket> brackets() = 0;
    virtual const Bracket bracket(int id) = 0;
    virtual const QList<Competitor> bracketCompetitors(int bracketId) = 0;
    virtual bool addBracket(Bracket bracket) = 0;
    virtual bool updateBracket(Bracket bracket) = 0;
    virtual bool removeBracket(int id) = 0;

    // Competitor methods.

};


