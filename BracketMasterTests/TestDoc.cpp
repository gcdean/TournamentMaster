#include "TestDoc.h"


TestDoc::TestDoc()
    : TournamentDoc()
{
    // We want to initialize everything.

    Tournament t(1000);
    t.setId(1000);
    t.setName("Test Tournament");
    t.setDate(QDate(2015, 1, 1));
    t.setStartTime(QTime(10, 0));
    t.setTexasMatchCards(false);
    updateTournament(t);
}

TestDoc::~TestDoc()
{

}


Competitor TestDoc::createCompetitor(int competitorId, QString fname, QString lname, JM::Gender gender, int age, double weight, JM::Rank rank, int clubid, int numBrackets)
{
    Competitor comp(competitorId);
    comp.setFirstName(fname);
    comp.setLastName(lname);
    comp.setGender(gender);
    comp.setAge(age);
    comp.setWeight(weight);
    comp.setRank(rank);
    comp.setClubId(clubid);
    comp.setNumBrackets(numBrackets);

    return comp;

}

Bracket TestDoc::createBracket(int id, QString name, JM::Gender gender, JM::WeightType wtype, int minAge, int maxAge, int time, double maxWeight, bool chokes, bool armbars, int matnum)
{
    Bracket b(id);
    b.setName(name);
    b.setGender(gender);
    b.setWeightType(wtype);
    b.setMinAge(minAge);
    b.setMaxAge(maxAge);
    b.setTime(time);
    b.setMaxWeight(maxWeight);
    b.setChokesAllowed(chokes);
    b.setArmbarsAllowed(armbars);
    b.setMatNumber(matnum);

    return b;
}
