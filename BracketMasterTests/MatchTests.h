#pragma once

#include "AutoTest.h"

class MatchTests : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void idTest();
    void bracketIdTest();
    void matchNumTest();
    void competitorId1Test();
    void competitorId2Test();
    void winnerIdTest();
    void scoreTest();
    void notesTest();

    void cleanupTestCase();
};

DECLARE_TEST(MatchTests)

