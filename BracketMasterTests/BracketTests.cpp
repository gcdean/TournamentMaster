#include "BracketTests.h"

#include <QDebug>

#include "data/Bracket.h"
#include "data/Competitor.h"
#include "JMUtil.h"

namespace
{
    Bracket testBracket;

    const int ID(222);
    const QString NAME("BracketName");
    const JM::Gender MALE(JM::Male);
    const JM::WeightType MEDIUM_WEIGHT(JM::Medium);
    const int MINAGE(5);
    const int MAXAGE(6);
    const int TIME(3);
    const bool NOCHOKES(false);
    const bool NOARMBARS(false);
    const int MATNUM(2);
    const int FIRSTPL_ID(100);
    const int SECONDPL_ID(200);
    const int THIRDPL1_ID(300);
    const int THIRDPL2_ID(400);
    const double MAXWEIGHT(150.5);
}

void BracketTests::initTestCase()
{
    testBracket.setId(ID);
    testBracket.setName(NAME);
    testBracket.setGender(MALE);
    testBracket.setWeightType(MEDIUM_WEIGHT);
    testBracket.setMinAge(MINAGE);
    testBracket.setMaxAge(MAXAGE);
    testBracket.setTime(TIME);
    testBracket.setChokesAllowed(NOCHOKES);
    testBracket.setArmbarsAllowed(NOARMBARS);
    testBracket.setMatNumber(MATNUM);
    testBracket.setFirstPlace(FIRSTPL_ID);
    testBracket.setSecondPlace(SECONDPL_ID);
    testBracket.setThirdPlace1(THIRDPL1_ID);
    testBracket.setThirdPlace2(THIRDPL2_ID);
    testBracket.setMaxWeight(MAXWEIGHT);
}

void BracketTests::idTest()
{
    QCOMPARE(testBracket.id(), ID);
}

void BracketTests::nameTest()
{
    QCOMPARE(testBracket.name(), NAME);
}

void BracketTests::genderTest()
{
    QCOMPARE(testBracket.gender(), MALE);
}

void BracketTests::weightTypeTest()
{
    QCOMPARE(testBracket.weightType(), MEDIUM_WEIGHT);
}

void BracketTests::minAgeTest()
{
    QCOMPARE(testBracket.minAge(), MINAGE);
}

void BracketTests::maxAgeTest()
{
    QCOMPARE(testBracket.maxAge(), MAXAGE);
}

void BracketTests::timeTest()
{
    QCOMPARE(testBracket.time(), TIME);
}

void BracketTests::maxWeightTest()
{
   QCOMPARE(testBracket.maxWeight(), MAXWEIGHT);
}

void BracketTests::chokesTest()
{
    QCOMPARE(testBracket.chokesAllowed(), NOCHOKES);
    testBracket.setChokesAllowed(true);
    QCOMPARE(testBracket.chokesAllowed(), !NOCHOKES);
}

void BracketTests::armbarsTest()
{
    QCOMPARE(testBracket.armbarsAllowed(), NOARMBARS);
    testBracket.setArmbarsAllowed(true);
    QCOMPARE(testBracket.armbarsAllowed(), !NOARMBARS);
}

void BracketTests::matNumberTest()
{
    QCOMPARE(testBracket.matNumber(), MATNUM);
}

void BracketTests::firstPlaceTest()
{
    QCOMPARE(testBracket.firstPlace(), FIRSTPL_ID);
}

void BracketTests::secondPlaceTest()
{
    QCOMPARE(testBracket.secondPlace(), SECONDPL_ID);
}

void BracketTests::thirdPlace1Test()
{
    QCOMPARE(testBracket.thirdPlace1(), THIRDPL1_ID);
}

void BracketTests::thirdPlace2Test()
{
    QCOMPARE(testBracket.thirdPlace2(), THIRDPL2_ID);
}

void BracketTests::validTest()
{
    QCOMPARE(testBracket.isValid(), true);
    Bracket badBracket;
    QCOMPARE(badBracket.isValid(), false);
}

//void BracketTests::numMatchesTest_data()
//{
//    QTest::addColumn<int>("numCompetitors");
//    QTest::addColumn<int>("maxMatches");

//    QTest::newRow("0 competitors") << 0 << 0;
//    QTest::newRow("1 competitors") << 1 << 0;
//    QTest::newRow("2 competitors") << 2 << 3;
//    QTest::newRow("3 competitors") << 3 << 3;
//    QTest::newRow("4 competitors") << 4 << 6;
//    QTest::newRow("5 competitors") << 5 << 8;
//    QTest::newRow("6 competitors") << 6 << 9;
//    QTest::newRow("7 competitors") << 7 << 11;
//    QTest::newRow("8 competitors") << 8 << 13;
//    QTest::newRow("9 competitors") << 9 << -1;
//    QTest::newRow("10 competitors") << 10 << -1;
//}

//void BracketTests::numMatchesTest()
//{
//    QFETCH(int, numCompetitors);
//    QFETCH(int, maxMatches);

////    for(int x = testBracket.competitors().size() - 1; x >= 0; x--)
////    {
////        testBracket.removeCompetitor(x);
////    }
////    QCOMPARE(testBracket.competitors().size(), 0);
////    for(int x = 0; x < numCompetitors; x++)
////    {
////        testBracket.addCompetitor(new Competitor);
////    }

////    QCOMPARE(testBracket.numberOfMatches(), maxMatches);

//}

void BracketTests::cleanupTestCase()
{
}
