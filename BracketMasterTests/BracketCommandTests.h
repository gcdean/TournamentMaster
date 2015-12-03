#pragma once

#include "AutoTest.h"

#include "data/Bracket.h"

class BracketCommandTests : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void getBracketsTest();
    void getSingleBracetTest();
    void getCompetitorsTest();
    void addBracketTest();
    void removeBracketTest();
    void updateBracketTest();
    void cleanupTestCase();
};

DECLARE_TEST(BracketCommandTests)
