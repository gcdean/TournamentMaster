#pragma once

#include "data/Bracket.h"
#include "data/Club.h"
#include "data/Competitor.h"
#include "data/Match.h"
#include "data/Tournament.h"

#include "IDocument.h"

#include <QHash>
#include <QJsonObject>
#include <QList>
#include <QMap>
#include <QString>

class Bracket;
class Club;
class Competitor;
class Match;

class TMCORE_DLLSPEC TournamentDoc : public IDocument
{
public:
    TournamentDoc();
    TournamentDoc(IDocument &doc);
    virtual ~TournamentDoc();

    // Tournament methods
    const Tournament& tournament() const override;
    void updateTournament(const Tournament& tournament) override;

    // Club methods
    const QList<Club> clubs() override;
    const Club club(int id) const override;
    bool addClub(Club club) override;
    Club addClub() override;
    bool removeClub(int id) override;
    bool updateClub(const Club& src) override;

    // Competitor methods
    const QList<Competitor> competitors() const override;
    const Competitor competitor(int id) const;
    bool addCompetitor(Competitor competitor) override;
    Competitor addCompetitor() override;
    bool removeCompetitor(int id) override;
    bool updateCompetitor(const Competitor& src) override;

    // Bracket methods
    const QList<Bracket> brackets() const override;
    const Bracket& bracket(int id) override;
    const QList<Competitor> bracketCompetitors(int bracketId) override;
    Bracket addBracket(Bracket bracket) override;
    bool removeBracket(int id) override;
    bool updateBracket(const Bracket& src) override;


    // Match methods
    const QList<Match> matches(int bracketid) const override;
    const Match match(int id) override;
    bool addMatch(int bracketId, Match& match) override;
    Match addMatch(int bracketId) override;
    bool removeMatch(int id) override;
    bool updateMatch(const Match& src) override;

    bool load(QString filename) override;
    QString name() override;
    bool save() override;
    bool save(QString filename) override;

    bool isModified() override;


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

    Match nonConstMatch(int matchId);

    Tournament m_tournament;
    bool m_modified;
    QString m_filename;

    QList <Bracket> m_brackets;
    int m_nextBracketId;

    QList <Club> m_clubs;
    int m_nextClubId;

    QList <Competitor> m_competitors;
    int m_nextCompetitorId;

    QMap <int, QList<Match>> m_matches; // bracket id to matches
    int m_nextMatchNum;

    QHash <int, int> m_matchBrackets;   // indexs match id to bracket id for faster lookup


};

