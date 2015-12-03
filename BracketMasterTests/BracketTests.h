#pragma once

#include "AutoTest.h"

class BracketTests : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void idTest();
    void nameTest();
    void genderTest();
    void weightTypeTest();
    void minAgeTest();
    void maxAgeTest();
    void timeTest();
    void maxWeightTest();
    void chokesTest();
    void armbarsTest();
    void matNumberTest();
    void firstPlaceTest();
    void secondPlaceTest();
    void thirdPlace1Test();
    void thirdPlace2Test();
    void validTest();
//    void numMatchesTest_data();
//    void numMatchesTest();
    void cleanupTestCase();
};

DECLARE_TEST(BracketTests)
