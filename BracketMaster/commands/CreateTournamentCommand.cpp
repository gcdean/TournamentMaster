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

    std::unique_ptr <Tournament> tournament(new Tournament());
    tournament->setName("Test");
    tournament->setDate(QDate::currentDate());

    JMApp()->setTournament(std::move(tournament));

    JMApp()->setModified(true);


    QSharedPointer<TournamentDoc> newdoc = QSharedPointer<TournamentDoc>(new TournamentDoc);
    QSharedPointer<CommandController> teditor = QSharedPointer<CommandController>(new CommandController(newdoc));
//    std::unique_ptr<IEditor> teditor(new CommandController(new TournamentDoc));

    JMApp()->setCommandController(teditor);

    return done(true);
}
