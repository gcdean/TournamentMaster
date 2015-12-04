#pragma once

#include "AutoTest.h"

class CompetitorCommandTests : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void allCompetitorsTest();
    void clubCompetitorsTest();
    void findCompetitorTest();
    void addCompetitorTest();
    void updateCompetitorTest();
    void removeCompetitorTest();
    void cleanupTestCase();

};

DECLARE_TEST(CompetitorCommandTests)
