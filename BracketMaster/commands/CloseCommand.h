#pragma once

#include "BaseCommand.h"
class CloseCommand : public BaseCommand
{
public:
    CloseCommand();
    ~CloseCommand();

    // BaseCommand interface
public slots:
    bool run();
};

