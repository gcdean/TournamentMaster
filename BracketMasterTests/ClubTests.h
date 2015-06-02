#pragma once

#include "AutoTest.h"

class ClubTests : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void clubNameTest();
    void clubCityTest();
    void clubCoachTest();
    void clubCountryTest();
    void clubIdTest();
    void clubStateTest();
    void clubZipTest();
    void cleanupTestCase();
};

DECLARE_TEST(ClubTests)
