#pragma once

#include "AutoTest.h"

class TournamentTests : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void idTest();
    void nameTest();
    void dateTest();
    void startTimeTest();
    void texasMatchCardTest();
    void cleanUpTestCase();
};

DECLARE_TEST(TournamentTests)
