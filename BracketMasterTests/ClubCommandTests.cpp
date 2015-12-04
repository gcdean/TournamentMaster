#include "ClubCommandTests.h"

#include "commands/ClubCommands.h"
#include "TournamentDoc.h"
#include "CommandController.h"

#include <QDebug>
#include <QSharedPointer>

void ClubCommandTests::initTestCase()
{
    QSharedPointer<TournamentDoc> doc = QSharedPointer<TournamentDoc>(new TournamentDoc);
    m_editor = QSharedPointer<CommandController>(new CommandController(doc));
}

void ClubCommandTests::createClubTest()
{
    QSharedPointer<CreateClubCommand> cmd = QSharedPointer<CreateClubCommand>(new CreateClubCommand(0));

    bool success = m_editor->doCommand(cmd);
    m_testClub = cmd->club();
    QCOMPARE(success, true);
    QCOMPARE(m_testClub.isValid(), true);
}

void ClubCommandTests::findClubTest()
{
    QSharedPointer<GetClubCommand> cmd = QSharedPointer<GetClubCommand>(new GetClubCommand(m_testClub.id()));
    QCOMPARE(m_editor->doCommand(cmd), true);
    Club club = cmd->club();
    QCOMPARE(club.id(), m_testClub.id());
}

void ClubCommandTests::findAllClubsTest()
{
    QSharedPointer<GetClubsCommand>cmd = QSharedPointer<GetClubsCommand>(new GetClubsCommand);
    QCOMPARE(m_editor->doCommand(cmd), true);
    const QList<Club> clubs = cmd->clubs();
    QCOMPARE(clubs.size(), 1);
}

void ClubCommandTests::updateClubTest()
{
    QSharedPointer<GetClubCommand> findcmd = QSharedPointer<GetClubCommand>(new GetClubCommand(m_testClub.id()));
    QCOMPARE(m_editor->doCommand(findcmd), true);

    Club club = findcmd->club();
    club.setClubName("TestName");

    QSharedPointer<UpdateClubCommand> cmd = QSharedPointer<UpdateClubCommand>(new UpdateClubCommand(club));
    QCOMPARE(m_editor->doCommand(cmd), true);

    QCOMPARE(m_editor->doCommand(findcmd), true);
    Club updatedClub = findcmd->club();
    QCOMPARE(updatedClub.clubName(), QString("TestName"));
}

void ClubCommandTests::removeClubTest()
{
    // Find the club,
    // Remove the club,
    // Don't find the club.
    QSharedPointer<GetClubCommand> findcmd = QSharedPointer<GetClubCommand>(new GetClubCommand(m_testClub.id()));
    QCOMPARE(m_editor->doCommand(findcmd), true);

    QSharedPointer<RemoveClubCommand> cmd = QSharedPointer<RemoveClubCommand>(new RemoveClubCommand(m_testClub));
    QCOMPARE(m_editor->doCommand(cmd), true);

    QCOMPARE(m_editor->doCommand(findcmd), false);

}

void ClubCommandTests::cleanupTestCase()
{

}

