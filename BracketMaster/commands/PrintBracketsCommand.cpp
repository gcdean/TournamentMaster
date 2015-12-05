#include "PrintBrancketsCommand.h"

#include "commands/BracketCommands.h"
#include "commands/TournamentCommands.h"
#include "data/Bracket.h"
#include "JudoMasterApplication.h"
#include "controllers/PrintController.h"
#include "data/Tournament.h"

#include <QDebug>
#include <QList>

PrintBracketsCommand::PrintBracketsCommand(QObject *parent)
    : BaseCommand(parent)
{

}

PrintBracketsCommand::PrintBracketsCommand(QString tournament, QList<int> brackets)
    : BaseCommand()
    , m_tournament(tournament)
{
       m_bracketIds.append(brackets);
}


PrintBracketsCommand::~PrintBracketsCommand()
{

}

bool PrintBracketsCommand::run(IDocument *const doc)
{
    // TODO
    // Open the print dialog
    // Set the print options.


    GetTournamentCmdPtr trnCmd = GetTournamentCmdPtr(new GetTournamentCommand);
    JMApp()->commandController()->doCommand(trnCmd);
    m_tournament = trnCmd->tournament().name();
    if(m_bracketIds.size() > 0)
    {
        PrintController pc(m_tournament);
        if (pc.prepare("Print Single Bracket"))
        {
            for(int x = 0; x < m_bracketIds.size(); x++)
            {
                int bracketId = m_bracketIds[x];
                // TODO - Change method signature

                GetBracketCommandPtr getBracketCmd = GetBracketCommandPtr(new GetBracketCommand(bracketId));
                JMApp()->commandController()->doCommand(getBracketCmd);

                Bracket bracket = getBracketCmd->bracket();
//                Bracket *bracket = dynamic_cast<Bracket *>(JMApp()->bracketController()->find(bracketId));
                if(bracket.isValid())
                {
                    qDebug() << "Print Bracket: " << bracket.name();
                    bool printed = pc.printBracket(&bracket);
                    if(printed && x < m_bracketIds.size() - 1)
                        pc.nextPage();
                }
            }
            pc.endPrint();
        }
        else
        {
            qDebug() << "Print failed";
        }
    }
    else if(JMApp()->bracketController()->brackets().size() > 0)
    {        
        PrintController pc(m_tournament);
        if (pc.prepare("Print Brackets"))
        {
            bool newPage = false;
            foreach(Bracket bracket, JMApp()->bracketController()->brackets())
            {
                // TODO - Fix with command to get competitors
                if (bracket.competitorIds().size() > 1)
                {
                    if (newPage)
                    {
                        pc.nextPage();
                    }

                    newPage = pc.printBracket(&bracket);
                    qDebug() << "Print Bracket: " << bracket.name();
                }
                else if (bracket.competitorIds().size() == 1)
                {
                    qDebug() << "WARNING: Bracket with only one competitor: " << bracket.name();
                }
            }
            pc.endPrint();
        }
        else
        {
            qDebug() << "Printing Failed";
        }
    }
    else
    {
        // print all brackets.
        qDebug() << "Nothing to Print";
    }

    return done(true);
}

