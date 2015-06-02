#include "JudoMasterApplication.h"

#include "Tournament.h"

JudoMasterApplication *JMApp()
{
    return dynamic_cast<JudoMasterApplication *>(qApp);
}


JudoMasterApplication::JudoMasterApplication(int &argc, char **argv) :
    QApplication(argc, argv)
    , m_tournament(0)
{
}

void JudoMasterApplication::setTournament(Tournament *tournament)
{
    m_tournament = tournament;
    m_matchController.setTournament(m_tournament);
}

const Tournament *JudoMasterApplication::tournament() const
{
    return m_tournament;
}
