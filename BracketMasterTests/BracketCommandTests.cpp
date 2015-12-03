#include "BracketCommandTests.h"

#include "commands/BracketCommands.h"
#include "TestDoc.h"
#include "CommandController.h"

#include <QSharedPointer>

namespace
{
    QSharedPointer<TestDoc> doc = QSharedPointer<TestDoc>(new TestDoc);
    CommandController cmdController(doc);

    const int BRACKET1_ID(2000);
    const int BRACKET2_ID(2001);

}

void BracketCommandTests::initTestCase()
{
    // Create a bracket with 3 competitors.
    Bracket b1 = doc->createBracket(BRACKET1_ID, "Bracket 1 Name", JM::Male, JM::Light, 9, 10, 3, 68.0, false, false, 1);
    Bracket b2 = doc->createBracket(BRACKET2_ID, "Bracket 2", JM::Female, JM::IJF, 99, 99, 5, 0.0, true, true, 2);
    doc->addBracket(b1);
    doc->addBracket(b2);

    Competitor c1 = doc->createCompetitor(201, "Andie", "Dean", JM::Female, 19, 160.3, JM::Black, 2, 1);
    Competitor c2 = doc->createCompetitor(302, "Rhonda", "Rousey", JM::Female, 28, 154.0, JM::Black, 3, 1);
    doc->addCompetitor(c1);
    doc->addCompetitor(c2);

    b2.addCompetitor(c1.id());
    b2.addCompetitor(c2.id());

    doc->updateBracket(b2);
}

void BracketCommandTests::getBracketsTest()
{
    GetBracketsCommandPtr cmd = GetBracketsCommandPtr(new GetBracketsCommand);
    QCOMPARE(cmdController.doCommand(cmd), true);

    QCOMPARE(cmd->brackets().size(), 2);
}

void BracketCommandTests::getSingleBracetTest()
{
    // First, test a invalid bracket
    GetBracketCommandPtr cmd = GetBracketCommandPtr(new GetBracketCommand(-333));
    QCOMPARE(cmdController.doCommand(cmd), false);

    cmd = GetBracketCommandPtr(new GetBracketCommand(BRACKET2_ID));
    QCOMPARE(cmdController.doCommand(cmd), true);
    // Compare the bracket data.
    Bracket b = cmd->bracket();
    QCOMPARE(b.name(), QString("Bracket 2"));
    QCOMPARE(b.gender(), JM::Female);

}

void BracketCommandTests::getCompetitorsTest()
{    
    GetBracketCompetitorsCommandPtr cmd = GetBracketCompetitorsCommandPtr(new GetBracketCompetitorsCommand (BRACKET2_ID));
    bool success = cmdController.doCommand(cmd);
    QCOMPARE(success, true);
    QList<Competitor> competitors = cmd->competitors();
    QCOMPARE(competitors.size(), 2);

}

void BracketCommandTests::addBracketTest()
{
    Bracket b = doc->createBracket(2100, "New Bracket", JM::Female, JM::IJF, 99, 99, 5, 0.0, true, true, 2);
    AddBracketCommandPtr cmd = AddBracketCommandPtr(new AddBracketCommand(b));
    // First, do the add.
    QCOMPARE(cmdController.doCommand(cmd), true);

    // Let's see if we can find it.
    GetBracketCommandPtr findCmd = GetBracketCommandPtr(new GetBracketCommand(2100));
    QCOMPARE(cmdController.doCommand(findCmd), true);

    // Is it the right one?
    QCOMPARE(findCmd->bracket().name(), QString("New Bracket"));
}

void BracketCommandTests::removeBracketTest()
{
    GetBracketCommandPtr findCmd = GetBracketCommandPtr(new GetBracketCommand(BRACKET1_ID));
    QCOMPARE(cmdController.doCommand(findCmd), true);

    // Now, delete the bracket
    RemoveBracketCommandPtr removeCmd = RemoveBracketCommandPtr(new RemoveBracketCommand(findCmd->bracket()));
    QCOMPARE(cmdController.doCommand(removeCmd), true);

    // Test to make sure it's not htere.
    QCOMPARE(cmdController.doCommand(findCmd), false);

    // Undo and verify it's there.
    QCOMPARE(cmdController.undoCommand(), true);
    QCOMPARE(cmdController.doCommand(findCmd), true);
}

void BracketCommandTests::updateBracketTest()
{
    // First, find the bracket.
    GetBracketCommandPtr findCmd = GetBracketCommandPtr(new GetBracketCommand(BRACKET1_ID));
    QCOMPARE(cmdController.doCommand(findCmd), true);

    // We now have the bracket, make a change to it.
    Bracket bracket = findCmd->bracket();
    QString origName = bracket.name();
    bracket.setName("UPDATE TEST NAME");

    UpdateBracketCmdPtr updateCmd = UpdateBracketCmdPtr(new UpdateBracketCommand(bracket));
    QCOMPARE(cmdController.doCommand(updateCmd), true);

    // Now,find the bracket and compare the name again.
    QCOMPARE(cmdController.doCommand(findCmd), true);
    QCOMPARE(findCmd->bracket().name(), QString("UPDATE TEST NAME"));

    // Now, undo the change.
    QCOMPARE(cmdController.undoCommand(), true);

    // Find again and test against original name.
    QCOMPARE(cmdController.doCommand(findCmd), true);
    QCOMPARE(findCmd->bracket().name(), origName);

}

void BracketCommandTests::cleanupTestCase()
{
//    editor.clear();
}
