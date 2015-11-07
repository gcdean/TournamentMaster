#pragma once

#include "data/Tournament.h"

#include <QHash>
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


    bool isModified();

    // Tournament methods
    const Tournament& tournament() const;
    void updateTournament(const Tournament& tournament);

    // Club methods
    const QList<Club> clubs();
    const Club *club(int id) const;
    bool addClub(Club club);
    bool removeClub(int id);
    bool updateClub(const Club& src);

    // Competitor methods
    const QList<Competitor> competitors() const;
    bool addCompetitor(Competitor competitor);
    bool removeCompetitor(int id);
    bool updateCompetitor(const Competitor& src);

    // Bracket methods
    const QList<Bracket> brackets() const;
    const Bracket& bracket(int id);
    bool addBracket(Bracket bracket);
    bool removeBracket(int id);
    bool updateBracket(const Bracket& src);


    // Match methods
    const QList<Match> matches(int bracketid) const;
    const Match& match(int id);
    bool addMatch(int bracketId, Match match);
    bool removeMatch(int id);
    bool updateMatch(const Match& src);

    void load(QString filename);
    void save(QString filename);


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

    Match& nonConstMatch(int id);

    Tournament m_tournament;
    bool m_modified;
    QList <Bracket> m_brackets;
    QList <Club> m_clubs;

    QList <Competitor> m_competitors;

    QMap <int, QList<Match>> m_matches;
    QHash <int, int> m_matchBrackets;   // indexs match id to bracket id for faster lookup


};

