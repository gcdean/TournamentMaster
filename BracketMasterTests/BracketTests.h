#pragma once

#include "AutoTest.h"

class BracketTests : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void bracketNameTest();
    void numMatchesTest_data();
    void numMatchesTest();
    void cleanupTestCase();
};

DECLARE_TEST(BracketTests)
