#include "CreateTournamentCommand.h"


#include <memory>

#include "JudoMasterApplication.h"
#include "data/Tournament.h"

#include "TournamentDoc.h"

#include <QDate>
#include <QDebug>

CreateTournamentCommand::CreateTournamentCommand(QObject *parent)
    : BaseCommand(parent)
{

}

CreateTournamentCommand::~CreateTournamentCommand()
{

}



bool CreateTournamentCommand::run(IDocument *const doc)
{
    Q_UNUSED(doc)

    qDebug() << "Create a New Tournament";

    Tournament tournament;
    tournament.setName("Test");
    tournament.setDate(QDate::currentDate());

    QSharedPointer<TournamentDoc> newdoc = QSharedPointer<TournamentDoc>(new TournamentDoc);
    QSharedPointer<CommandController> teditor = QSharedPointer<CommandController>(new CommandController(newdoc));

    JMApp()->setCommandController(teditor);

    newdoc->updateTournament(tournament);

    return done(true);
}
