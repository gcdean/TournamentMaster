#include "CompetitorTests.h"

#include <QDebug>

#include "data/CompetitorData.h"
#include "data/Competitor.h"

namespace
{
    Competitor tc;
    const int ID(200);
    const QString FNAME("Greg");
    const QString LNAME("Dean");
    const JM::Gender GENDER(JM::Male);
    const int AGE(21);
    const double WEIGHT(140.3);
    const JM::Rank RANK(JM::Green);
    const int NUMBRACKETS(2);
    const QString NOTES("Test Notes");
    const int CLUBID(3);
}

void CompetitorTests::initTestCase()
{
    tc.setId(ID);
    tc.setFirstName(FNAME);
    tc.setLastName(LNAME);
    tc.setGender(GENDER);
    tc.setAge(AGE);
    tc.setWeight(WEIGHT);
    tc.setRank(RANK);
    tc.setNumBrackets(NUMBRACKETS);
    tc.setNotes(NOTES);
    tc.setClubId(CLUBID);

}

void CompetitorTests::idTest()
{
    QCOMPARE(tc.id(), ID);
    tc.setId(ID + 3);
    QCOMPARE(tc.id() == ID, false);
}

void CompetitorTests::firstNameTest()
{
    QCOMPARE(tc.firstName(), FNAME);

    tc.setFirstName(LNAME);
    QCOMPARE(tc.firstName(), LNAME);
}

void CompetitorTests::lastNameTest()
{
    QCOMPARE(tc.lastName(), LNAME);

    tc.setLastName(FNAME);
    QCOMPARE(tc.lastName(), FNAME);
}

void CompetitorTests::genderTest()
{
    QCOMPARE(tc.gender(), GENDER);
}

void CompetitorTests::ageTest()
{
    QCOMPARE(tc.age(), AGE);
}

void CompetitorTests::weightTest()
{
    QCOMPARE(tc.weight(), WEIGHT);
}

void CompetitorTests::rankTest()
{
    QCOMPARE(tc.rank(), RANK);
}

void CompetitorTests::bracketsTest()
{
    QCOMPARE(tc.numBrackets(), NUMBRACKETS);
}

void CompetitorTests::notesTest()
{
    QCOMPARE(tc.notes(), NOTES);
}

void CompetitorTests::clubIdTest()
{
    QCOMPARE(tc.clubId(), CLUBID);
}

void CompetitorTests::cleanupTestCase()
{

}
