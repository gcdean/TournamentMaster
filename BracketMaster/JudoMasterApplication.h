#pragma once

#include "controllers/BracketController.h"
#include "controllers/ClubController.h"
#include "controllers/CompetitorController.h"
#include "controllers/MatchController.h"
#include "data/Tournament.h"
#include "CommandController.h"

#include <memory.h>
#include <QApplication>
#include <QDir>


class JudoMasterApplication : public QApplication
{
    Q_OBJECT

public:
    JudoMasterApplication(int& argc, char** argv);

    ClubController* clubController()  {return &m_clubController;}
    CompetitorController *competitorController() {return &m_competitorController;}
    BracketController *bracketController() {return &m_bracketController;}
    MatchController *matchController() {return &m_matchController;}
    void setCommandController(QSharedPointer<CommandController> editor);
    CommandController* commandController();

    bool isModified() const;
    void setModified(bool setModified);
    const QDir lastSaveDir() const;
    void setLastSaveDir(QDir dirname);

signals:

    void tournamentChanged();
    void editClub();

private slots:
    void saveState();

private:
    ClubController m_clubController;
    CompetitorController m_competitorController;
    BracketController m_bracketController;
    MatchController m_matchController;

    QSharedPointer<CommandController> m_commandController;


    bool m_modified;
    QDir m_lastSaveDir;
};

JudoMasterApplication *JMApp();
