#include "PrintRegistrationCommand.h"

#include "commands/ClubCommands.h"
#include "commands/TournamentCommands.h"

#include "data/Club.h"
#include "data/Competitor.h"
#include "JudoMasterApplication.h"
#include "controllers/PrintController.h"
#include "data/Tournament.h"

#include <algorithm>
#include <QFontMetrics>
#include <QList>
#include <QPainter>
#include <QtPrintSupport>
#include <QPrintDialog>
#include <QPrinter>
#include <QRect>
#include <QString>
#include <QWidget>

PrintRegistrationCommand::PrintRegistrationCommand(QWidget *parent, QList<Club > clubs)
    : BaseCommand(parent)

{
    m_clubs.append(clubs);
}

PrintRegistrationCommand::~PrintRegistrationCommand()
{

}

bool PrintRegistrationCommand::run(IDocument *const doc)
{

    QList<Club >sortedClubs = getClubs();

    GetTournamentCmdPtr trncmd = GetTournamentCmdPtr(new GetTournamentCommand);
    JMApp()->commandController()->doCommand(trncmd);

    PrintController pc(trncmd->tournament().name(), QPrinter::Portrait);
    if(pc.prepare("Print Registration"))
    {
        bool newPage = false;
        foreach(const Club club, sortedClubs)
        {
            if(newPage)
                pc.nextPage();

            newPage = pc.printClubRegistration(club);
        }

        return done(true);
    }

    return done(false);
}

QList<Club > PrintRegistrationCommand::getClubs()
{
    Q_ASSERT(true);

    QList<Club >sortedClubs;

    if(m_clubs.size() == 0)
    {
        CommandController* cntrl = JMApp()->commandController();

        GetClubsCmdPtr cmd = GetClubsCmdPtr(new GetClubsCommand);
        cntrl->doCommand(cmd);

        const QList<Club> clubs = cmd->clubs();

        sortedClubs.append(clubs);
    }
    else
    {
        sortedClubs.append(m_clubs);
    }

    std::sort(sortedClubs.begin(), sortedClubs.end(), compareClubNames);

    return sortedClubs;
}

