#include "MatchTests.h"

#include "data/Match.h"

namespace
{
    Match match;

    const int ID(33);
    const int BRACKETID(45);
    const int MATCHNUM(52);
    const int COMP1_ID(3);
    const int COMP2_ID(15);
    const int WINNER_ID(COMP1_ID);
    const int SCORE(10);
    const QString NOTES("Match Notes");

}
void MatchTests::initTestCase()
{
    match.setId(ID);
    match.setBracketId(BRACKETID);
    match.setMatchNum(MATCHNUM);
    match.setCompetitor1Id(COMP1_ID);
    match.setCompetitor2Id(COMP2_ID);
    match.setWinnerId(WINNER_ID);
    match.setScore(SCORE);
    match.setNotes(NOTES);
}

void MatchTests::idTest()
{
    QCOMPARE(match.id(), ID);
}

void MatchTests::bracketIdTest()
{
    QCOMPARE(match.bracketId(), BRACKETID);
}

void MatchTests::matchNumTest()
{
    QCOMPARE(match.matchNum(), MATCHNUM);
}

void MatchTests::competitorId1Test()
{
    QCOMPARE(match.competitor1Id(), COMP1_ID);
}

void MatchTests::competitorId2Test()
{
    QCOMPARE(match.competitor2Id(), COMP2_ID);
}

void MatchTests::winnerIdTest()
{
    QCOMPARE(match.winnerId(), WINNER_ID);
}

void MatchTests::scoreTest()
{
    QCOMPARE(match.score(), SCORE);
}

void MatchTests::notesTest()
{
    QCOMPARE(match.notes(), NOTES);
}

void MatchTests::cleanupTestCase()
{

}
