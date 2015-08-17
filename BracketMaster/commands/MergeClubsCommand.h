#pragma once

#include "BaseCommand.h"

class Club;

class MergeClubsCommand : public BaseCommand
{
   Q_OBJECT
public:
    MergeClubsCommand(Club *srcClub, Club *destClub);

    // BaseCommand interface
    virtual bool run();

private:
    Club *m_srcClub;
    Club *m_destClub;
};

