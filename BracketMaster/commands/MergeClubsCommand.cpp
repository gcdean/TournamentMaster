#include "MergeClubsCommand.h"

#include "data/Club.h"
#include "JudoMasterApplication.h"

#include <QDebug>
#include <QMessageBox>

MergeClubsCommand::MergeClubsCommand(Club *src, Club *dest)
    :BaseCommand()
    , m_srcClub(src)
    , m_destClub(dest)
{
}


bool MergeClubsCommand::run()
{
    if(!m_srcClub || !m_destClub)
        return done(false);

    // Confirm the Merge
    if(QMessageBox::No == QMessageBox::question(0, "Merge Clubs", QString("Are you sure you want to merge %1 with %2").arg(m_srcClub->clubName()).arg(m_destClub->clubName())))
    {
        return done(false);
    }

    // Copy Competitors from src to dest.
    foreach(Competitor *cmp, m_srcClub->competitors())
    {
        m_destClub->addCompetitor(cmp);
    }

    // Delete the src club.
    JMApp()->clubController()->remove(m_srcClub->id());
    return done(true);
}
