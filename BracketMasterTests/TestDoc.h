#pragma once

#include "TournamentDoc.h"

class TestDoc : public TournamentDoc
{
public:
    TestDoc();
    virtual ~TestDoc();

    // IDocument interface
public:

    Competitor createCompetitor(int competitorId, QString fname, QString lname, JM::Gender gender, int age, double weight, JM::Rank rank, int clubid, int numBrackets);
    Bracket createBracket(int id, QString name, JM::Gender gender, JM::WeightType wtype, int minAge, int maxAge, int time, double maxWeight, bool chokes, bool armbars, int matnum);

};

