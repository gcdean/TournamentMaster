#pragma once

#include "BaseCommand.h"

class ExportCSVCommand : public BaseCommand
{
public:
    ExportCSVCommand(QObject *parent = 0);
    ~ExportCSVCommand();

    // BaseCommand interface
public slots:
    bool run();
};

