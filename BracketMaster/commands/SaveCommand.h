#pragma once

#include "BaseCommand.h"

class SaveCommand : public BaseCommand
{
public:
    SaveCommand(bool saveAs = false, QObject *parent = 0);
    ~SaveCommand();

    // BaseCommand interface
public slots:
    bool run();

private:
    bool m_enableSaveAs;
};

