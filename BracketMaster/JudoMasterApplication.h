#pragma once

#include "controllers/BracketController.h"
#include "controllers/ClubController.h"
#include "controllers/CompetitorController.h"
#include "controllers/MatchController.h"
#include "data/Tournament.h"
#include "TournamentEditor.h"

#include <memory.h>
#include <QApplication>
#include <QDir>


class JudoMasterApplication : public QApplication
{
public:
    explicit JudoMasterApplication(int& argc, char** argv);

    ClubController* clubController()  {return &m_clubController;}
    CompetitorController *competitorController() {return &m_competitorController;}
    BracketController *bracketController() {return &m_bracketController;}
    MatchController *matchController() {return &m_matchController;}
    void setTournament(std::unique_ptr<Tournament> tournament);
    void setEditor(QSharedPointer<IEditor> editor);
    const std::unique_ptr<Tournament> &tournament() const;
    IEditor* const tournamentEditor();

    bool isModified() const;
    void setModified(bool setModified);
    const QDir lastSaveDir() const;
    void setLastSaveDir(QDir dirname);

private:
    ClubController m_clubController;
    CompetitorController m_competitorController;
    BracketController m_bracketController;
    MatchController m_matchController;
//    Tournament *m_tournament;
    std::unique_ptr<Tournament> m_tournament; // OLD

    QSharedPointer<IEditor> m_editor;


    bool m_modified;
    QDir m_lastSaveDir;
};

JudoMasterApplication *JMApp(); //{return dynamic_cast<JudoMasterApplication *>(qApp);}
