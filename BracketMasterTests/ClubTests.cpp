#include "ClubTests.h"

#include <QDebug>
#include <QJsonObject>

#include "../BracketMaster/Club.h"

namespace
{
    QJsonObject clubJsonObj;
    Club jsonClub;
}

void ClubTests::initTestCase()
{
    clubJsonObj["address1"] = QString();
    clubJsonObj["address2"] = QString("");
    clubJsonObj["city"] = QString("Redmond");
    clubJsonObj["clubname"] = QString("Emerald City Judo");
    clubJsonObj["coachname"] = QString("Greg Dean");
    clubJsonObj["country"] = QString("USA");
    clubJsonObj["id"] = 1;
    clubJsonObj["state"] = QString("WA");
    clubJsonObj["zip"] = QString("98052");

    jsonClub.read(clubJsonObj);

}

void ClubTests::clubNameTest()
{
    QCOMPARE(QString("Emerald City Judo"), jsonClub.clubName());
}

void ClubTests::clubCityTest()
{
    QCOMPARE(QString("Redmond"), jsonClub.city());
}

void ClubTests::clubCoachTest()
{
    QCOMPARE(QString("Greg Dean"), jsonClub.coachName());
}

void ClubTests::clubCountryTest()
{
    QCOMPARE(QString("USA"), jsonClub.country());
}

void ClubTests::clubIdTest()
{
    QCOMPARE(1, jsonClub.id());
}

void ClubTests::clubStateTest()
{

}

void ClubTests::clubZipTest()
{

}


void ClubTests::cleanupTestCase()
{
}
