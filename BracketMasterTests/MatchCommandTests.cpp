#include "MatchCommandTests.h"

#include "CommandController.h"
#include "commands/MatchCommands.h"
#include "data/Match.h"
#include "TestDoc.h"

namespace
{
    QSharedPointer<TestDoc> doc = QSharedPointer<TestDoc> (new TestDoc());
    CommandController cmdController(doc);

    const int MAXBRACKETS(3);
    const int MAXMATCHES(3);
}

void MatchCommandTests::initTestCase()
{
    for(int x = 0; x < MAXBRACKETS; x++)
    {
        JM::Gender gender = x % 2 == 0 ? JM::Male : JM::Female;
        Bracket b = doc->createBracket(x, QString("Bracket: %1").arg(x), gender, JM::Medium, 10, 11, 3, 75.0, true, false, 1);
        doc->addBracket(b);

        for(int y = 0; y < MAXMATCHES; y++)
        {
            Match m = doc->addMatch(b.id());
        }
    }
}

void MatchCommandTests::findMatchTest()
{
    FindMatchCmdPtr cmd = FindMatchCmdPtr(new FindMatchCommand(1));
    QCOMPARE(cmdController.doCommand(cmd), true);
    QCOMPARE(cmd->match().bracketId(), 0);
}

void MatchCommandTests::getBracketMatchesTest()
{
    GetAllMatchesCmdPtr cmd = GetAllMatchesCmdPtr(new GetAllMatchesCommand(1));
    QCOMPARE(cmdController.doCommand(cmd), true);
    QCOMPARE(cmd->matches().size(), MAXMATCHES);
}

void MatchCommandTests::addMatchTest()
{
    Match match;
    match.setNotes(QString("Added Match"));
    AddMatchCmdPtr cmd = AddMatchCmdPtr(new AddMatchCommand(1, match));
    QCOMPARE(cmdController.doCommand(cmd), true);
    Match addedMatch = cmd->match();
    QCOMPARE(addedMatch.notes(), QString("Added Match"));
    QCOMPARE(addedMatch.isValid(), true);

}

void MatchCommandTests::updateMatchTest()
{
    // First, get a match.
    FindMatchCmdPtr findCmd = FindMatchCmdPtr(new FindMatchCommand(1));
    QCOMPARE(cmdController.doCommand(findCmd), true);

    Match m = findCmd->match();
    m.setCompetitor1Id(222);
    m.setCompetitor2Id(333);
    m.setWinnerId(222);
    m.setMatchNum(77);
    m.setScore(7);

    UpdateMatchCmdPtr updateCmd = UpdateMatchCmdPtr(new UpdateMatchCommand(m));
    QCOMPARE(cmdController.doCommand(updateCmd), true);

    // Now, find the match again and confirm the updates.
    QCOMPARE(cmdController.doCommand(findCmd), true);
    Match updatedMatch = findCmd->match();
    QCOMPARE(updatedMatch.competitor1Id(), 222);
    QCOMPARE(updatedMatch.competitor2Id(), 333);
    QCOMPARE(updatedMatch.winnerId(), 222);
    QCOMPARE(updatedMatch.matchNum(), 77);
    QCOMPARE(updatedMatch.score(), 7);

}

void MatchCommandTests::removeMatchTest()
{
    FindMatchCmdPtr findCmd = FindMatchCmdPtr(new FindMatchCommand(1));
    QCOMPARE(cmdController.doCommand(findCmd), true);

    Match foundMatch = findCmd->match();

    RemoveMatchCmdPtr cmd = RemoveMatchCmdPtr(new RemoveMatchCommand(foundMatch));
    QCOMPARE(cmdController.doCommand(cmd), true);

    // Now, make sure we can't find it.
    QCOMPARE(cmdController.doCommand(findCmd), false);

    // Undo the remove.
    QCOMPARE(cmdController.undoCommand(), true);

    // Make sure we can find it again.
    QCOMPARE(cmdController.doCommand(findCmd), true);
}

void MatchCommandTests::cleanupTestCase()
{

}
