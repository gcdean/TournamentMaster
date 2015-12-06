#include "MergeClubsCommand.h"

#include "data/Club.h"
#include "JudoMasterApplication.h"

#include <QDebug>
#include <QMessageBox>

MergeClubsCommand::MergeClubsCommand(Club src, Club dest)
    :BaseCommand()
    , m_srcClub(src)
    , m_destClub(dest)
{
}


bool MergeClubsCommand::run(IDocument *const doc)
{
    if(!m_srcClub.isValid() || !m_destClub.isValid())
        return done(false);

    // Confirm the Merge
    if(QMessageBox::No == QMessageBox::question(0, "Merge Clubs", QString("Are you sure you want to merge %1 with %2").arg(m_srcClub.clubName()).arg(m_destClub.clubName())))
    {
        return done(false);
    }

//    // Copy Competitors from src to dest.
//    // TODO - Get list of competitors for a club
//    foreach(Competitor *cmp, m_srcClub->competitors())
//    {
//        m_destClub->addCompetitor(cmp);
//    }

    // Delete the src club.
//    JMApp()->clubController()->remove(m_srcClub->id());
    return done(true);
}
