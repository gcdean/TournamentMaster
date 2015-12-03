#pragma once

#include "TournamentDoc.h"

class TestDoc : public TournamentDoc
{
public:
    TestDoc();
    virtual ~TestDoc();

    // IDocument interface
public:
//    const Tournament &tournament() const override;
//    void updateTournament(const Tournament &tournament) override;

//    const QList<Club> clubs() override;
//    const Club club(int id) const override;
//    bool addClub(Club club) override;
//    Club addClub() override;
//    bool removeClub(int id) override;
//    bool updateClub(const Club &src) override;

//    const QList<Competitor> competitors() const override;
//    const Competitor competitor(id) const override;
//    bool addCompetitor(Competitor competitor) override;
//    bool removeCompetitor(int id) override;
//    bool updateCompetitor(const Competitor &src) override;

//    const QList<Bracket> brackets() const override;
//    const Bracket &bracket(int id) override;
//    const QList<Competitor> bracketCompetitors(int bracketId) override;
//    bool addBracket(Bracket bracket) override;
//    bool removeBracket(int id) override;
//    bool updateBracket(const Bracket &src) override;

//    const QList<Match> matches(int bracketid) const override;
//    const Match &match(int id) override;
//    bool addMatch(int bracketId, Match match) override;
//    bool removeMatch(int id) override;
//    bool updateMatch(const Match &src) override;

//    bool load(QString filename) override;
//    bool save() override;
//    bool save(QString filename) override;

    Competitor createCompetitor(int competitorId, QString fname, QString lname, JM::Gender gender, int age, double weight, JM::Rank rank, int clubid, int numBrackets);
    Bracket createBracket(int id, QString name, JM::Gender gender, JM::WeightType wtype, int minAge, int maxAge, int time, double maxWeight, bool chokes, bool armbars, int matnum);

};

