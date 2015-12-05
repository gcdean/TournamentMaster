#include "MatchTableModel.h"

#include "commands/MatchCommands.h"
#include "data/Competitor.h"
#include "JudoMasterApplication.h"
#include "data/Match.h"

#include "data/JMDataObj.h" // TODO - Delete this.

#include <QDebug>

MatchTableModel::MatchTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    connect(JMApp()->matchController(), &MatchController::matchAdded, this, &MatchTableModel::matchAdded);
}

void MatchTableModel::setBracketId(int id)
{
    m_bracketId = id;
}

int MatchTableModel::bracketId()
{
    return m_bracketId;
}


int MatchTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    const MatchController* controller = JMApp()->matchController();
    return controller->size(m_bracketId);
}

int MatchTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return MatchTableModel::MAX_COLUMNS;
}

QVariant MatchTableModel::data(const QModelIndex &index, int role) const
{
    const QList<Match> matches = JMApp()->matchController()->matches(m_bracketId);

    if(index.row() >= matches.size())
    {
        return QVariant();
    }

    Match match = matches[index.row()];

//    qDebug() << "MatchTableModel::data(). Match is: " << match;
    switch(role)
    {
        case Qt::DisplayRole:
        case Qt::EditRole:
        {
            switch(index.column())
            {
                case MatchTableModel::firstCompetitor:
                {
                    Competitor c1 = JMApp()->competitorController()->find(match.competitor1Id());
                    return QVariant(c1.isValid() ? QString("%1 %2").arg(c1.firstName()).arg(c1.lastName()) : "<Not Set>");
                }

                case MatchTableModel::secondCompetitor:
                {
//                    qDebug() << "Match Competitor 2 is: " << match->competitor2();
                    Competitor c2 = JMApp()->competitorController()->find(match.competitor2Id());
                    return QVariant(c2.isValid() ? QString("%1 %2").arg(c2.firstName()).arg(c2.lastName()) : "<Not Set>");
                }

                case MatchTableModel::winner:
                {
//                    qDebug() << "Match winner is: " << match->winner();
                    Competitor winner = JMApp()->competitorController()->find(match.winnerId());
                    return QVariant(winner.isValid() ? QString("%1 %2").arg(winner.firstName()).arg(winner.lastName()) : "<Not Set>");
                }

                case MatchTableModel::score:
                    return QVariant(match.score());

                case MatchTableModel::notes:
                    return QVariant(match.notes());
            }
        }
        break;
    }

    return QVariant();
}


bool MatchTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "MatchTableModel::setData(). role is: " << role;

    const QList<Match> matches = JMApp()->matchController()->matches(m_bracketId);

    if(index.row() >= matches.size())
    {
        return false;
    }

    Match match = matches[index.row()];

    bool updated = true;
    switch(index.column())
    {
        case firstCompetitor:
        {
            match.setCompetitor1Id(value.toInt());
        }
            break;

        case secondCompetitor:
        {
            match.setCompetitor2Id(value.toInt());
        }
            break;

        case winner:
        {
            match.setWinnerId(value.toInt());
        }
            break;

        case score:
            match.setScore(value.toInt());
            break;

        case notes:
            match.setNotes(value.toString());
        break;

        default:
            updated = false;
    }

    if(updated)
    {
        JMApp()->matchController()->update(match);
    }

    return updated;
}

QVariant MatchTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal)
    {
        if(role == Qt::DisplayRole)
        {
            switch(section)
            {
                case firstCompetitor:
                    return QVariant("White");

                case secondCompetitor:
                    return QVariant("Blue");

                case winner:
                    return QVariant("Winner");

                case score:
                    return QVariant("Score");

                case notes:
                    return QVariant("Notes");
            }
        }
    }

    return QVariant();
}

void MatchTableModel::matchAdded(int id)
{
    // TODO - Fix
    qDebug() << "MatchTableMOdel::matchAdded(" << id << ")";
//    int index = JMApp()->matchController()->indexOf(data->id());
    // TODO - Change below to actual index.
    int index = rowCount(QModelIndex());
    beginInsertRows(QModelIndex(), index, index);
    endInsertRows();
}


Qt::ItemFlags MatchTableModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);

    Qt::ItemFlags flags = QAbstractTableModel::flags(index);

    flags |= Qt::ItemIsEditable;

    return flags;
}


