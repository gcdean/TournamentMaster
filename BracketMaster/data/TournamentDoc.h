#pragma once

#include "Tournament.h"

#include <QJsonObject>
#include <QList>
#include <QMap>
#include <QString>

class Bracket;
class Club;
class Competitor;
class Match;

class TournamentDoc
{
public:
    TournamentDoc();
    ~TournamentDoc();

    void load(QString filename);
    void save(QString filename) const;

private:
    void readTournament(const QJsonObject &jobj );
    void readBrackets(const QJsonObject &root );
    void readClubs(const QJsonObject &root );
    void readCompetitors(const QJsonObject &root );
    void readMatches(const QJsonObject &root );

    void writeTournament(QJsonObject &root) const;
    void writeBrackets(QJsonObject &root) const;
    void writeClubs(QJsonObject &root) const;
    void writeCompetitors(QJsonObject &root) const;
    void writeMatches(QJsonObject &root) const;

    Tournament m_tournament;
    QList <Bracket> m_brackets;
    QList <Club> m_clubs;

    QList <Competitor> m_competitors;

    QMap <int, Match> m_matches;


};

