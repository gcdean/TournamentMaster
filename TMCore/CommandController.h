#pragma once

#include "commands/BaseUndoCommand.h"
#include <QSharedPointer>
#include <QStack>

class IDocument;

class TMCORE_DLLSPEC CommandController
{
public:
    CommandController(QSharedPointer<IDocument> doc);
    ~CommandController();

public:
    bool doCommand(QSharedPointer<BaseCommand> command);
    bool undoCommand();
    // TODO - Add redo Method.
    const QList<QSharedPointer<BaseUndoCommand>> undoCommandList() const;
    const QList<QSharedPointer<BaseUndoCommand>> redoCommandList() const;

private:
    QSharedPointer<IDocument> m_document;
    QStack<QSharedPointer<BaseUndoCommand>> m_undoStack;
    QStack<QSharedPointer<BaseUndoCommand>> m_redoStack;


};


