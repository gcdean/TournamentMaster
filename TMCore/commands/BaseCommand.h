#pragma once

#include <QObject>

#include "IEditor.h"

class BaseCommand : public QObject
{
    Q_OBJECT

public:
    BaseCommand(QObject* parent = 0);
    ~BaseCommand();

    virtual bool isUndoable();

signals:
    void commandComplete(); // Emitted whenenver the command is done, regardless of the result
    void commandSuccessful();    // Emitted when the command is successful
    void commandFailed();       // Emitted when command fails.
public slots:
    virtual bool run(IEditor* const editor) = 0;

protected:
    bool done(bool success);

};

