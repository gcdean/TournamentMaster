#pragma once

#include "commands/BaseCommand.h"

class SaveCommand : public BaseCommand
{
public:
    SaveCommand(bool saveAs = false, QObject *parent = 0);
    ~SaveCommand();

    // BaseCommand interface
public slots:
    bool run(IEditor* const editor) override;

private:
    bool m_enableSaveAs;
};

