#pragma once

#include "AutoTest.h"

class TournamentCommandTests : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void getTournamentTest();
    void updateTournamentTest();
    void cleanupTestCase();
};

DECLARE_TEST(TournamentCommandTests)
