#include "BracketTests.h"

#include <QDebug>

#include "data/Bracket.h"
#include "data/Competitor.h"

namespace
{
    Bracket testBracket;
}

void BracketTests::initTestCase()
{
}

void BracketTests::bracketNameTest()
{
    Bracket b1;
    b1.setName("Bracket Name");
    QCOMPARE(QString("Bracket Name"), b1.name());
}

void BracketTests::numMatchesTest_data()
{
    QTest::addColumn<int>("numCompetitors");
    QTest::addColumn<int>("maxMatches");

    QTest::newRow("0 competitors") << 0 << 0;
    QTest::newRow("1 competitors") << 1 << 0;
    QTest::newRow("2 competitors") << 2 << 3;
    QTest::newRow("3 competitors") << 3 << 3;
    QTest::newRow("4 competitors") << 4 << 6;
    QTest::newRow("5 competitors") << 5 << 8;
    QTest::newRow("6 competitors") << 6 << 9;
    QTest::newRow("7 competitors") << 7 << 11;
    QTest::newRow("8 competitors") << 8 << 13;
    QTest::newRow("9 competitors") << 9 << -1;
    QTest::newRow("10 competitors") << 10 << -1;
}

void BracketTests::numMatchesTest()
{
    QFETCH(int, numCompetitors);
    QFETCH(int, maxMatches);

    for(int x = testBracket.competitors().size() - 1; x >= 0; x--)
    {
        testBracket.removeCompetitor(x);
    }
    QCOMPARE(testBracket.competitors().size(), 0);
    for(int x = 0; x < numCompetitors; x++)
    {
        testBracket.addCompetitor(new Competitor);
    }

    QCOMPARE(testBracket.numberOfMatches(), maxMatches);

}

void BracketTests::cleanupTestCase()
{
}
