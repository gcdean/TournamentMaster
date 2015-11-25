#include "JudoMasterApplication.h"

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
    QSharedPointer<IEditor> teditor = QSharedPointer<IEditor>(new TournamentEditor(doc));

    setEditor(teditor);

}

void JudoMasterApplication::setTournament(std::unique_ptr<Tournament> tournament)
{
    m_tournament = std::move(tournament);
    m_matchController.setTournament(m_tournament);
    m_clubController.setTournament(m_tournament);
    m_competitorController.setTournament(m_tournament);
    m_bracketController.setTournament(m_tournament);
}

void JudoMasterApplication::setEditor(QSharedPointer<IEditor> editor)
{
    m_editor = editor;

    // TODO - Set controllers?
}

const std::unique_ptr<Tournament> &JudoMasterApplication::tournament() const
{
    return m_tournament;
}

IEditor *const JudoMasterApplication::tournamentEditor()
{

    return m_editor.data();
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
