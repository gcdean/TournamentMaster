#include "CreateTournamentCommand.h"


#include <memory>

#include "JudoMasterApplication.h"
#include "data/Tournament.h"
#include <QDate>
#include <QDebug>

CreateTournamentCommand::CreateTournamentCommand(QObject *parent)
    : BaseCommand(parent)
{

}

CreateTournamentCommand::~CreateTournamentCommand()
{

}



bool CreateTournamentCommand::run()
{
    qDebug() << "Create a New Tournament";

    std::unique_ptr <Tournament> tournament(new Tournament());
    tournament->setName("Test");
    tournament->setDate(QDate::currentDate());

    JMApp()->setTournament(std::move(tournament));

    JMApp()->setModified(true);

    return done(true);
}
