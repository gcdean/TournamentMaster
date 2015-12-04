#pragma once
#include "AutoTest.h"

#include "data/Club.h"
#include "IEditor.h"
#include <QObject>

class CommandController;

class ClubCommandTests : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void createClubTest();
    void findClubTest();
    void findAllClubsTest();
    void updateClubTest();
    void removeClubTest();
    void cleanupTestCase();

private:
    QSharedPointer<CommandController> m_editor;
    Club m_testClub;
};

DECLARE_TEST(ClubCommandTests)
