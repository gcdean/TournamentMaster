#include "JudoMasterApplication.h"

#include "CommandController.h"
#include "data/Tournament.h"
#include "TournamentDoc.h"

JudoMasterApplication *JMApp()
{
    return dynamic_cast<JudoMasterApplication *>(qApp);
}


JudoMasterApplication::JudoMasterApplication(int &argc, char **argv) :
    QApplication(argc, argv)
    , m_tournament(nullptr)
    , m_lastSaveDir(QDir::home())
{

    QSharedPointer<TournamentDoc> doc = QSharedPointer<TournamentDoc>(new TournamentDoc);
    QSharedPointer<CommandController> teditor = QSharedPointer<CommandController>(new CommandController(doc));

    setCommandController(teditor);

}

void JudoMasterApplication::setTournament(std::unique_ptr<Tournament> tournament)
{
    m_tournament = std::move(tournament);
    m_matchController.setTournament(m_tournament);
    m_clubController.setTournament(m_tournament);
    m_competitorController.setTournament(m_tournament);
    m_bracketController.setTournament(m_tournament);
}

void JudoMasterApplication::setCommandController(QSharedPointer<CommandController> editor)
{
    m_commandController = editor;

    // TODO - Set controllers?
}

const std::unique_ptr<Tournament> &JudoMasterApplication::tournament() const
{
    return m_tournament;
}

CommandController* JudoMasterApplication::commandController()
{

    return m_commandController.data();
}

bool JudoMasterApplication::isModified() const
{
    return m_modified;
}

void JudoMasterApplication::setModified(bool modified)
{
    m_modified = modified;
}

const QDir JudoMasterApplication::lastSaveDir() const
{
    return m_lastSaveDir;
}

void JudoMasterApplication::setLastSaveDir(QDir dirname)
{
    m_lastSaveDir = dirname;
}
