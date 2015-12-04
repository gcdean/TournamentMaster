#pragma once

#include "BaseCommand.h"

#include <QObject>

class IEditor;

class BaseUndoCommand : public BaseCommand
{
public:
    BaseUndoCommand(QObject* parent = 0);
    ~BaseUndoCommand();


    // BaseCommand interface
public:
    bool isUndoable() override;

public slots:
    virtual bool undo(IDocument *doc) = 0;

};


