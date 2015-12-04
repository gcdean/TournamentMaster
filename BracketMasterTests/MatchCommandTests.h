#pragma once

#include "AutoTest.h"

class MatchCommandTests : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void findMatchTest();
    void getBracketMatchesTest();
    void addMatchTest();
    void updateMatchTest();
    void removeMatchTest();
    void cleanupTestCase();
};

DECLARE_TEST(MatchCommandTests)
