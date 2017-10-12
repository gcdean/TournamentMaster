#pragma once
#include "commands/BaseCommand.h"
#include "data/Club.h"
#include <QObject>

class ClubInfoUpdateCommand : public BaseCommand
{
public:
    ClubInfoUpdateCommand(QObject* parent, int clubId = 0);
    ~ClubInfoUpdateCommand();


    // BaseUndoCommand interface
public slots:
    bool run(IDocument *const doc) override;

private:
    int m_clubId;
    Club m_club;

};

typedef QSharedPointer<ClubInfoUpdateCommand> ClubInfoUpdateCommandPtr;
