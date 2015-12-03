#include "CommandController.h"

#include "commands/BaseCommand.h"
#include "commands/BaseUndoCommand.h"
#include "TournamentDoc.h"

#include <QDebug>

CommandController::CommandController(QSharedPointer<IDocument> doc)
    : m_document(doc)
{

}

CommandController::~CommandController()
{
    qDebug() << "CommandController being deleted";
}


bool CommandController::doCommand(QSharedPointer<BaseCommand> command)
{
    bool success = command->run(m_document.data());
    if(success)
    {
        if(command->isUndoable())
        {
            m_undoStack.push(qSharedPointerCast<BaseUndoCommand>(command));
        }
    }

    return success;
}

bool CommandController::undoCommand()
{
    bool success = false;
    QSharedPointer<BaseUndoCommand> command = m_undoStack.pop();
    if(command)
    {
        success = command->undo(m_document.data());
        m_redoStack.push(command);
    }

    return success;
}

const QList<QSharedPointer<BaseUndoCommand> > CommandController::undoCommandList() const
{
    //return m_undoStack.toList();
    return QList<QSharedPointer<BaseUndoCommand>>();
}

const QList<QSharedPointer<BaseUndoCommand> > CommandController::redoCommandList() const
{
    //return m_redoStack.toList();
    return QList<QSharedPointer<BaseUndoCommand>>();
}



//bool CommandController::load(QString name)
//{
//    // TODO - Need better error detection/handling
//    this->m_document->load(name);

//    return true;
//}



//bool CommandController::save()
//{
//    return m_document->save();
//}

//bool CommandController::saveAs(QString name)
//{
//    return m_document->save(name);
//}

//const QList<Club> CommandController::clubs()
//{
//    return m_document->clubs();
//}

//bool CommandController::addClub(Club club)
//{
//    return m_document->addClub(club);
//}

//Club CommandController::createClub()
//{
//    Club club = m_document->addClub();
//    return club;

//}

//Club CommandController::findClub(int id)
//{
//    return m_document->club(id);
//}

//bool CommandController::updateClub(Club club)
//{
//    return m_document->updateClub(club);
//}

//bool CommandController::removeClub(int id)
//{
//    return m_document->removeClub(id);
//}

//const QList<Bracket> CommandController::brackets()
//{
//    return m_document->brackets();
//}

//const Bracket CommandController::bracket(int id)
//{
//    return m_document->bracket(id);
//}

//const QList<Competitor> CommandController::bracketCompetitors(int bracketId)
//{
//    return m_document->bracketCompetitors(bracketId);
//}

//bool CommandController::addBracket(Bracket bracket)
//{
//    return m_document->addBracket(bracket);
//}

//bool CommandController::updateBracket(Bracket bracket)
//{
//    m_document->updateBracket(bracket);
//}

//bool CommandController::removeBracket(int id)
//{
//    return m_document->removeBracket(id);
//}
