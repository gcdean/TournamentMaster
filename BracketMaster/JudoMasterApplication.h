#pragma once

#include "controllers/BracketController.h"
#include "controllers/ClubController.h"
#include "controllers/CompetitorController.h"
#include "controllers/MatchController.h"

#include <QApplication>

class Tournament;

class JudoMasterApplication : public QApplication
{
public:
    explicit JudoMasterApplication(int& argc, char** argv);

    ClubController* clubController()  {return &m_clubController;}
    CompetitorController *competitorController() {return &m_competitorController;}
    BracketController *bracketController() {return &m_bracketController;}
    MatchController *matchController() {return &m_matchController;}
    void setTournament(Tournament *tournament);
    const Tournament *tournament() const;

private:
    ClubController m_clubController;
    CompetitorController m_competitorController;
    BracketController m_bracketController;
    MatchController m_matchController;
    Tournament *m_tournament;
};

JudoMasterApplication *JMApp(); //{return dynamic_cast<JudoMasterApplication *>(qApp);}
