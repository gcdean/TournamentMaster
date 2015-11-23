#include "TournamentEditor.h"

#include "commands/BaseCommand.h"
#include "commands/BaseUndoCommand.h"
#include "TournamentDoc.h"

#include <QDebug>

TournamentEditor::TournamentEditor(QSharedPointer<TournamentDoc> doc)
    : m_document(doc)
{

}

TournamentEditor::~TournamentEditor()
{
    qDebug() << "TournamentEditor being deleted";
}


bool TournamentEditor::doCommand(QSharedPointer<BaseCommand> command)
{
    bool success = command->run(this);
    if(success)
    {
        if(command->isUndoable())
        {
            m_undoStack.push(qSharedPointerCast<BaseUndoCommand>(command));
        }
    }

    return success;
}

bool TournamentEditor::undoCommand()
{
    bool success = false;
    QSharedPointer<BaseUndoCommand> command = m_undoStack.pop();
    if(command)
    {
        success = command->undo(this);
        m_redoStack.push(command);
    }

    return success;
}

const QList<QSharedPointer<BaseUndoCommand> > TournamentEditor::undoCommandList() const
{
    //return m_undoStack.toList();
    return QList<QSharedPointer<BaseUndoCommand>>();
}

const QList<QSharedPointer<BaseUndoCommand> > TournamentEditor::redoCommandList() const
{
    //return m_redoStack.toList();
    return QList<QSharedPointer<BaseUndoCommand>>();
}



bool TournamentEditor::load(QString name)
{
    // TODO - Need better error detection/handling
    this->m_document->load(name);

    return true;
}



bool TournamentEditor::save()
{
    return m_document->save();
}

bool TournamentEditor::saveAs(QString name)
{
    return m_document->save(name);
}

const QList<Club> TournamentEditor::clubs()
{
    return m_document->clubs();
}

bool TournamentEditor::addClub(Club club)
{
    return m_document->addClub(club);
}

Club TournamentEditor::createClub()
{
    Club club = m_document->addClub();
    return club;

}

Club TournamentEditor::findClub(int id)
{
    return m_document->club(id);
}

bool TournamentEditor::updateClub(Club club)
{
    return m_document->updateClub(club);
}

bool TournamentEditor::removeClub(int id)
{
    return m_document->removeClub(id);
}
