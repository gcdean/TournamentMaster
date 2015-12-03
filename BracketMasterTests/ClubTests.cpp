#include "ClubTests.h"

#include <QDebug>

#include "data/Club.h"

namespace
{
    QJsonObject clubJsonObj;
    Club testClub;
}

void ClubTests::initTestCase()
{
    testClub.setAddress1("address1");
    testClub.setAddress2("address2");
    testClub.setCity("Redmond");
    testClub.setClubName("Emerald City Judo");
    testClub.setCoachName("Greg Dean");
    testClub.setCountry("USA");
//    testClub.setId(1);
    testClub.setState("WA");
    testClub.setZip("98052");

}

void ClubTests::clubNameTest()
{
    QCOMPARE(QString("Emerald City Judo"), testClub.clubName());
}

void ClubTests::clubCityTest()
{
    QCOMPARE(QString("Redmond"), testClub.city());
}

void ClubTests::clubCoachTest()
{
    QCOMPARE(QString("Greg Dean"), testClub.coachName());
}

void ClubTests::clubCountryTest()
{
    QCOMPARE(QString("USA"), testClub.country());
}

void ClubTests::clubIdTest()
{
    QCOMPARE(-1, testClub.id());
}

void ClubTests::clubStateTest()
{
    QCOMPARE(QString("WA"), testClub.state());

}

void ClubTests::clubZipTest()
{
    QCOMPARE(QString("98052"), testClub.zip());

}


void ClubTests::cleanupTestCase()
{
}
