#pragma once

#include "commands/BaseCommand.h"

class Club;

class MergeClubsCommand : public BaseCommand
{
   Q_OBJECT
public:
    MergeClubsCommand(Club srcClub, Club destClub);

    // BaseCommand interface
    virtual bool run(IDocument* const doc);

private:
    Club m_srcClub;
    Club m_destClub;
};

