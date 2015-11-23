#include "PrintRegistrationCommand.h"

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

namespace
{
    bool compareClubs(Club* club1, Club* club2)
    {
        return club1->clubName().compare(club2->clubName()) < 0;
    }

}

PrintRegistrationCommand::PrintRegistrationCommand(QWidget *parent, QList<Club > clubs)
    : BaseCommand(parent)

{
    m_clubs.append(clubs);
}

PrintRegistrationCommand::~PrintRegistrationCommand()
{

}

bool PrintRegistrationCommand::run(IEditor* const editor)
{

    QList<Club >sortedClubs = getClubs();

    PrintController pc(JMApp()->tournament()->name(), QPrinter::Portrait);
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

//    if(m_clubs.size() == 0)
//    {
//        const QList<Club > clubs = JMApp()->clubController()->clubs();

//        sortedClubs.append(clubs);
//    }
//    else
//    {
//        sortedClubs.append(m_clubs);
//    }

//    std::sort(sortedClubs.begin(), sortedClubs.end(), compareClubs);

    return sortedClubs;
}

