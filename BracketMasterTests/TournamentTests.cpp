#include "TournamentTests.h"

#include "data/Tournament.h"

namespace
{
    Tournament trn;
    const int ID(300);
    const QString NAME("Tourn Name");
    const QDate DATE(1990, 7, 4);
    const QTime TIME(10, 30);
    const bool USE_TEXASMATCH(true);
}

void TournamentTests::initTestCase()
{
    trn.setId(ID);
    trn.setName(NAME);
    trn.setDate(DATE);
    trn.setStartTime(TIME);
    trn.setTexasMatchCards(USE_TEXASMATCH);

}

void TournamentTests::idTest()
{
    QCOMPARE(trn.id(), ID);
}

void TournamentTests::nameTest()
{
    QCOMPARE(trn.name(), NAME);
}

void TournamentTests::dateTest()
{
    QCOMPARE(trn.date(), DATE);
}

void TournamentTests::startTimeTest()
{
    QCOMPARE(trn.startTime(), TIME);
}

void TournamentTests::texasMatchCardTest()
{
    QCOMPARE(trn.useTexasMatchCards(), USE_TEXASMATCH);
}

void TournamentTests::cleanUpTestCase()
{

}
