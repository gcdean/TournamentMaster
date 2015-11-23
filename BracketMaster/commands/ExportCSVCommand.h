#pragma once

#include "commands/BaseCommand.h"

class ExportCSVCommand : public BaseCommand
{
public:
    ExportCSVCommand(QObject *parent = 0);
    ~ExportCSVCommand();

    // BaseCommand interface
public slots:
    bool run(IEditor* const editor);
};

