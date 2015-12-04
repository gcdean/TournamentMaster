#include "CompetitorCommandTests.h"


#include "CommandController.h"
#include "commands/CompetitorCommands.h"
#include "TestDoc.h"

namespace
{
QSharedPointer<TestDoc> doc = QSharedPointer<TestDoc>(new TestDoc);
CommandController cmdController(doc);

const int CLUB1_ID(200);
const int CLUB2_ID(201);


const int MAX_COMPETITORS(131);
}

void CompetitorCommandTests::initTestCase()
{
    for(int x = 0; x < MAX_COMPETITORS; x++)
    {
        int clubid = 200 + (x % 2);
        Competitor c = doc->createCompetitor(x, QString("First - %1").arg(x), QString("Last - %1").arg(x), JM::Male, x+5, 50.0, JM::Orange, clubid, 1);
        doc->addCompetitor(c);
    }
}

void CompetitorCommandTests::allCompetitorsTest()
{
    GetCompetitorsCmdPtr cmd = GetCompetitorsCmdPtr(new GetCompetitorsCommand);
    QCOMPARE(cmdController.doCommand(cmd), true);
    QCOMPARE(cmd->competitors().size(), MAX_COMPETITORS);

}

void CompetitorCommandTests::clubCompetitorsTest()
{
    // CLUB2_ID is used because it will always have an even number of competitors based on how
    // they are added in the initTestCase method.
    GetClubCompetitorsCmdPtr cmd = GetClubCompetitorsCmdPtr(new GetClubCompetitorsCommand(CLUB2_ID));
    QCOMPARE(cmdController.doCommand(cmd), true);

    // Each club should have half the number of competitors.
    QCOMPARE(cmd->competitors().size(), MAX_COMPETITORS / 2);
}

void CompetitorCommandTests::findCompetitorTest()
{
    // Find a valid competitor
    FindCompetitorCmdPtr cmd = FindCompetitorCmdPtr(new FindCompetitorCommand(MAX_COMPETITORS - 1));
    QCOMPARE(cmdController.doCommand(cmd), true);
    QCOMPARE(cmd->competitor().isValid(), true);

    // Now, find an invalid competitor.
    cmd = FindCompetitorCmdPtr(new FindCompetitorCommand(-999));
    QCOMPARE(cmdController.doCommand(cmd), false);
    QCOMPARE(cmd->competitor().isValid(), false);

}

void CompetitorCommandTests::addCompetitorTest()
{
    // Test creating a default competitor.
    AddCompetitorCmdPtr addCmd = AddCompetitorCmdPtr(new AddCompetitorCommand());
    QCOMPARE(cmdController.doCommand(addCmd), true);
    QCOMPARE(addCmd->competitor().isValid(), true);

    // Verify it's in the document.
    Competitor found = doc->competitor(addCmd->competitor().id());
    QCOMPARE(found == addCmd->competitor(), true);

    // Undo the add
    QCOMPARE(cmdController.undoCommand(), true);

    // Verify it is no longer in the document.
    found = doc->competitor(addCmd->competitor().id());
    QCOMPARE(found.isValid(), false);

    // Now, create a competitor object and add it.
    Competitor c = doc->createCompetitor(-1, QString("First Name Test"), QString("Last Name Test"), JM::Female, 99, 150.0, JM::Brown, CLUB1_ID, 1);
    addCmd = AddCompetitorCmdPtr(new AddCompetitorCommand(c));

    // Add the competitor.
    QCOMPARE(cmdController.doCommand(addCmd), true);

    // Verify it's in the document.
    found = doc->competitor(addCmd->competitor().id());
    QCOMPARE(found == addCmd->competitor(), true);

}

void CompetitorCommandTests::updateCompetitorTest()
{

    // First, find a competitor. We're going to find the middle competitor
    GetCompetitorsCmdPtr allCmd = GetCompetitorsCmdPtr(new GetCompetitorsCommand);
    QCOMPARE(cmdController.doCommand(allCmd), true);

    QList<Competitor> allCompetitors = allCmd->competitors();

    Competitor srcC = allCompetitors.at(allCompetitors.size() / 2);

    FindCompetitorCmdPtr findCmd = FindCompetitorCmdPtr(new FindCompetitorCommand(srcC.id()));
    QCOMPARE(cmdController.doCommand(findCmd), true);

    Competitor c = findCmd->competitor();
    QString fname = c.firstName();

    c.setFirstName(QString("UPDATE TEST"));
    UpdateCompetitorCmdPtr updateCmd = UpdateCompetitorCmdPtr(new UpdateCompetitorCommand(c));
    QCOMPARE(cmdController.doCommand(updateCmd), true);

    // Now, find the cmopetitor and see if it has the updated data.
    QCOMPARE(cmdController.doCommand(findCmd), true);
    QCOMPARE(findCmd->competitor().firstName(), QString("UPDATE TEST"));

    // Undo the change.
    QCOMPARE(cmdController.undoCommand(), true);
    QCOMPARE(cmdController.doCommand(findCmd), true);
    QCOMPARE(findCmd->competitor().firstName(), fname);

}

void CompetitorCommandTests::removeCompetitorTest()
{
    // First, find a competitor. We're going to find the middle competitor
    GetCompetitorsCmdPtr allCmd = GetCompetitorsCmdPtr(new GetCompetitorsCommand);
    QCOMPARE(cmdController.doCommand(allCmd), true);

    QList<Competitor> allCompetitors = allCmd->competitors();

    Competitor srcC = allCompetitors.at(allCompetitors.size() / 2);

    // Remove the competitor
    RemoveCompetitorCmdPtr removeCmd = RemoveCompetitorCmdPtr(new RemoveCompetitorCommand(srcC));
    QCOMPARE(cmdController.doCommand(removeCmd), true);

    // Make sure we can't find it again.
    FindCompetitorCmdPtr findCmd = FindCompetitorCmdPtr(new FindCompetitorCommand(srcC.id()));
    QCOMPARE(cmdController.doCommand(findCmd), false);

    // Undo the command
    QCOMPARE(cmdController.undoCommand(), true);

    // Make sure we can find it again.
    QCOMPARE(cmdController.doCommand(findCmd), true);
}

void CompetitorCommandTests::cleanupTestCase()
{

}
