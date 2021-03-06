#include "CompetitorTableModel.h"

#include "commands/BracketCommands.h"
#include "controllers/CompetitorController.h"
#include "data/Bracket.h"
#include "data/Competitor.h"
#include "JudoMasterApplication.h"
#include "JMUtil.h"

#include <QColor>
#include <QDebug>
#include <QHash>
#include <QIcon>
#include <QMimeData>

CompetitorTableModel::CompetitorTableModel(BaseController *controller, QObject *parent) :
    QAbstractTableModel(parent)
    , m_parentId(-1)
    , m_controller(controller)
    , m_editable(true)
    , m_filter()
{
}

void CompetitorTableModel::setParentId(int id)
{
    beginResetModel();
    m_parentId = id;
    endResetModel();
}

void CompetitorTableModel::setFilter(const CompetitorFilter &filter)
{
    beginResetModel();
    m_filter = filter;
    endResetModel();
}

void CompetitorTableModel::setEditable(bool editable)
{
    m_editable = editable;
}

bool CompetitorTableModel::editable()
{
    return m_editable;
}

int CompetitorTableModel::rowCount(const QModelIndex &) const
{
    int rows = m_controller->competitors(m_filter, m_parentId).size();
    return rows;
}

int CompetitorTableModel::columnCount(const QModelIndex &) const
{
    return competitor::MAX_COMPETITOR_ITEM;
}

QVariant CompetitorTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Vertical)
    {

        switch(role)
        {
            case Qt::TextColorRole:
            {
                QModelIndex idx = index(section, 0);
                if(idx.isValid())
                {
                    QVariant qv = data(idx, Qt::UserRole);
                    CompetitorController *controller = dynamic_cast<CompetitorController *>(m_controller);
                    Competitor competitor = controller->find(qv.toInt());

                    const QList<Bracket> brackets = JMApp()->bracketController()->competitorBrackets(qv.toInt());
                    if(competitor.isValid() && competitor.numBrackets() != brackets.size())
                    {
                        return QVariant(QColor(Qt::red));
                    }
                }
                else
                {
                    qDebug() << "INVALID Index. Section " << section << ", Orientation: " << orientation << ", # Rows is: " << m_controller->competitors(m_filter, m_parentId).size();
                }
            }
            break;
            case Qt::DisplayRole:
            {
                return QVariant(section+1);
            }
            break;

            default:
                return QVariant();
        }

        return QVariant();

    }


    if(role == Qt::DisplayRole)
    {
        switch(section)
        {
            case competitor::FirstName:
                return QVariant("First");
                break;

            case competitor::LastName:
                return QVariant("Last");
                break;

            case competitor::Gender:
                return QVariant("Gender");
                break;

            case competitor::Age:
                return QVariant("Age");
                break;

            case competitor::Weight:
                return QVariant("Wt.");
                break;

            case competitor::Rank:
                return QVariant("Rank");
                break;

            case competitor::NumDivs:
                return QVariant("Divs");

            case competitor::Notes:
                return QVariant("Notes");
            default:
                return QVariant();
        }
    }
    return QVariant();
}

QVariant CompetitorTableModel::data(const QModelIndex &index, int role) const
{
    // Get the competitor.
    const QList<Competitor> competitors = m_controller->competitors(m_filter, m_parentId);
    if(index.row() >= competitors.size())
    {
        qDebug() << "ERROR!!! CompetitorTableModel::data() attempting to access row: " << index.row() << " with only " << competitors.size() << " Competitors with filter?";
        return QVariant("ERROR");
    }

    const Competitor judoka = competitors.at(index.row());
    switch(role)
    {
        case Qt::BackgroundRole:
            return QVariant(this->columnBackground(judoka, index.column()));

            break;

        case Qt::DecorationRole:
        {
            switch(index.column())
            {
                case competitor::Rank:
                {

                    switch(judoka.rank())
                    {
                        case JM::White:
                            return QIcon(":/images/white.png");
                            break;
                        case JM::Yellow:
                            return QIcon(":/images/yellow.png");
                            break;
                        case JM::Orange:
                            return QIcon(":/images/orange.png");
                            break;
                        case JM::Green:
                            return QIcon(":/images/green.png");
                            break;

                        case JM::Blue:
                            return QIcon(":/images/blue.png");
                            break;
                        case JM::Purple:
                            return QIcon(":/images/purple.png");
                            break;
                        case JM::Brown:
                            return QIcon(":/images/brown.png");
                            break;
                        case JM::Black:
                            return QIcon(":/images/black.png");
                            break;

                        case JM::Unknown:
                        default:
                            return QVariant();
                    }
                }
            }

            break;
        }
        case Qt::DisplayRole:
        case Qt::EditRole:
            switch(index.column())
            {
                case competitor::FirstName:
                    return QVariant(judoka.firstName());
                    break;

                case competitor::LastName:
                    return QVariant(judoka.lastName());
                    break;

                case competitor::Gender:
                    return QVariant(genderToString(judoka.gender()));
                    break;

                case competitor::Age:
                    return QVariant(judoka.age());
                    break;

                case competitor::Weight:
                    return QVariant(judoka.weight());
                    break;

                case competitor::Rank:
                    return QVariant(rankToString(judoka.rank()));

                    break;

                case competitor::NumDivs:
                    return QVariant(judoka.numBrackets());

                case competitor::Notes:
                    return QVariant(judoka.notes());

            }

            break;
        case Qt::UserRole:
            return QVariant(judoka.id());
            break;
    }

    return QVariant();
}

Qt::ItemFlags CompetitorTableModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if(m_editable)
    {
        flags |= Qt::ItemIsEditable;
    }

    // TODO: Refine when these flags are set (i.e. based on set data members)
    flags |= Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;

    return flags;
}

bool CompetitorTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);

    bool updated = true;

    const QList<Competitor > competitors = m_controller->competitors(m_filter, m_parentId);
    Competitor judoka = competitors.at(index.row());

    switch(index.column())
    {
        case competitor::FirstName: // First Name
            judoka.setFirstName(value.toString());
            break;

        case competitor::LastName: // Last Name
            judoka.setLastName(value.toString());
            break;

        case competitor::Gender:
            judoka.setGender(genderFromString(value.toString()));
            break;

        case competitor::Age:
            judoka.setAge(value.toInt());
            break;

        case competitor::Weight:
            judoka.setWeight(value.toDouble());
            break;

        case competitor::Rank:
            judoka.setRank(rankFromString(value.toString()));
            break;

        case competitor::NumDivs:
            judoka.setNumBrackets(value.toInt());
            break;

        case competitor::Notes:
            judoka.setNotes(value.toString());
            break;

        default:
            updated = false;
    }

    if(updated)
    {
        // Update the competitor.
        JMApp()->competitorController()->updateCompetitor(judoka);
        emit dataChanged(index, index);
    }
    return updated;

}

Qt::DropActions CompetitorTableModel::supportedDragActions() const
{
    return Qt::CopyAction;
}

Qt::DropActions CompetitorTableModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction | Qt::LinkAction;
}

QStringList CompetitorTableModel::mimeTypes() const
{
    QStringList types;// = QAbstractTableModel::mimeTypes();
    types << "application/jm.comp.list";

    return types;
}

QMimeData *CompetitorTableModel::mimeData(const QModelIndexList &indexes) const
{
    const QList<Competitor > competitors = m_controller->competitors(m_filter, m_parentId);
//    QMimeData *mimeData = new QMimeData();
    QMimeData *mimeData = QAbstractTableModel::mimeData(indexes);

    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    QHash<int, int> competitorIds;

    foreach(const QModelIndex& index, indexes)
    {
        Competitor competitor = competitors.at(index.row());
        if(competitor.isValid() && !competitorIds.contains(competitor.id()))
        {
            competitorIds[competitor.id()] = 1;
            stream << competitor.id();
        }

    }

    mimeData->setData("application/jm.comp.list", encodedData);

    return mimeData;
}

bool CompetitorTableModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    Q_UNUSED(row);
    Q_UNUSED(column);
    Q_UNUSED(parent);

    if(action == Qt::IgnoreAction)
        return true;

    bool success = false;

    if(data->hasFormat("application/jm.comp.list"))
    {
        QByteArray encoded = data->data("application/jm.comp.list");
        QDataStream stream(&encoded, QIODevice::ReadOnly);

        BracketController* controller = dynamic_cast<BracketController *>(m_controller);
        if(controller)
        {
            // This is only for adding competitors to a bracket.
            Bracket bracket = controller->find(m_parentId);
            if(!bracket.isValid())
            {
                return success;
            }

            int addedCompetitors = 0;
            while (!stream.atEnd())
            {
                int compId;
                stream >> compId;

                // Find the Competitor
                // TODO - Needs to be reworked
                Competitor competitor = JMApp()->competitorController()->find(compId);

                if(competitor.isValid() && (0 != dynamic_cast<BracketController *>(m_controller)))
                {
                    // Now add the competitor to the bracket.
                    if(bracket.addCompetitor(competitor.id()))
                    {
                        addedCompetitors++;
                    }
                }
            }

            if(addedCompetitors > 0)
            {
                UpdateBracketCmdPtr updaCmd = UpdateBracketCmdPtr(new UpdateBracketCommand(bracket));
                beginInsertRows(QModelIndex(), bracket.competitorIds().size(), bracket.competitorIds().size() + addedCompetitors - 1);
                if(JMApp()->commandController()->doCommand(updaCmd))
                {
                    success = true;
                }
                endInsertRows();

            }

        }

    }
    return success;
}

BaseController *CompetitorTableModel::controller()
{
    return m_controller;
}

int CompetitorTableModel::parentId() const
{
    return m_parentId;
}

QVariant CompetitorTableModel::columnBackground(const Competitor judoka, int col) const
{
    switch(col)
    {
        case competitor::FirstName:
            if(judoka.firstName().isEmpty())
                return QVariant(QColor(Qt::red));
            break;
        case competitor::LastName:
            if(judoka.lastName().isEmpty())
                return QVariant(QColor(Qt::red));
            break;

        case competitor::Age: // Age
            if(judoka.age() <= 0)
                return QVariant(QColor(Qt::red));
            break;

        case competitor::Weight: // Weight
            if(judoka.weight() <= 0.0)
                return QVariant(QColor(Qt::red));
            break;

        case competitor::NumDivs:
        {
            const QList<Bracket> brackets = JMApp()->bracketController()->competitorBrackets(judoka.id());
            if(brackets.size() == 0 && judoka.numBrackets() > 0)
                return QVariant(QColor(Qt::red));
            else if(brackets.size() < judoka.numBrackets())
                return QVariant(QColor(Qt::yellow));
            else if(brackets.size() > judoka.numBrackets())
                return QVariant(QColor(Qt::cyan));

        }
        break;

    }

    return QVariant();
}


bool CompetitorTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + (count - 1));
    for(int x = 0; x < count; x++)
    {
        QModelIndex index = createIndex(row + x, 0);
        QVariant var = data(index, Qt::UserRole);
        JMApp()->competitorController()->remove(var.toInt());
    }
    endRemoveRows();

    return true;
}


bool CompetitorTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    row = std::max(0, row);
    beginInsertRows(parent, row, row + (count - 1));
    for(int x = 0; x < count; x++)
    {
        QModelIndex index = createIndex(row + x, 0);
        QVariant var = data(index, Qt::UserRole);
        JMApp()->competitorController()->add(parentId());
    }
    endInsertRows();
    return true;
}
