#pragma once

#include "AutoTest.h"

class CompetitorTests : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void idTest();
    void firstNameTest();
    void lastNameTest();
    void genderTest();
    void ageTest();
    void weightTest();
    void rankTest();
    void bracketsTest();
    void notesTest();
    void clubIdTest();

    void cleanupTestCase();

};

DECLARE_TEST(CompetitorTests)

