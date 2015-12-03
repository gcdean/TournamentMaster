#pragma once

#include "commands/BaseCommand.h"

class OpenCommand : public BaseCommand
{
public:
    OpenCommand(QObject* parent);
    ~OpenCommand();

    // BaseCommand interface
public slots:
    bool run(IDocument* const doc);
};

