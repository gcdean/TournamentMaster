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



bool CreateTournamentCommand::run(IEditor* const editor)
{
    Q_UNUSED(editor)

    qDebug() << "Create a New Tournament";

    std::unique_ptr <Tournament> tournament(new Tournament());
    tournament->setName("Test");
    tournament->setDate(QDate::currentDate());

    JMApp()->setTournament(std::move(tournament));

    JMApp()->setModified(true);


    QSharedPointer<TournamentDoc> doc = QSharedPointer<TournamentDoc>(new TournamentDoc);
    QSharedPointer<TournamentEditor> teditor = QSharedPointer<TournamentEditor>(new TournamentEditor(doc));
//    std::unique_ptr<IEditor> teditor(new TournamentEditor(new TournamentDoc));

    JMApp()->setEditor(teditor);

    return done(true);
}
