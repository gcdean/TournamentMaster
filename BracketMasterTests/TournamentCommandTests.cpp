#include "TournamentCommandTests.h"

#include "CommandController.h"
#include "commands/TournamentCommands.h"
#include "data/Tournament.h"
#include "TestDoc.h"

namespace
{
    QSharedPointer<TestDoc> doc = QSharedPointer<TestDoc>(new TestDoc);
    CommandController cmdController(doc);

    const QString TRN_NAME("TEST NAME");
    const QString UPDATED_NAME("Update Name");
}


void TournamentCommandTests::initTestCase()
{
    Tournament trn = doc->tournament();
    trn.setName(TRN_NAME);
    doc->updateTournament(trn);
}

void TournamentCommandTests::getTournamentTest()
{
    GetTournamentCmdPtr cmd = GetTournamentCmdPtr(new GetTournamentCommand);
    QCOMPARE(cmdController.doCommand(cmd), true);
    QCOMPARE(cmd->tournament().name(), TRN_NAME);
}

void TournamentCommandTests::updateTournamentTest()
{
    GetTournamentCmdPtr findCmd = GetTournamentCmdPtr(new GetTournamentCommand);
    QCOMPARE(cmdController.doCommand(findCmd), true);

    // Find and modify the tournament
    Tournament trn = findCmd->tournament();
    trn.setName(UPDATED_NAME);

    UpdateTournamentCmdPtr updateCmd = UpdateTournamentCmdPtr(new UpdateTournamentCommand(trn));
    QCOMPARE(cmdController.doCommand(updateCmd), true);

    // Now find it again and compare the updated name
    QCOMPARE(cmdController.doCommand(findCmd), true);
    QCOMPARE(findCmd->tournament().name(), UPDATED_NAME);

    // Now, undo and test.
    QCOMPARE(cmdController.undoCommand(), true);
    QCOMPARE(cmdController.doCommand(findCmd), true);
    QCOMPARE(findCmd->tournament().name(), TRN_NAME);

}

void TournamentCommandTests::cleanupTestCase()
{

}
