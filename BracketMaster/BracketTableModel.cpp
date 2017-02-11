#include "BracketTableModel.h"

#include "data/Bracket.h"
#include "controllers/BracketController.h"
#include "JudoMasterApplication.h"

#include <QDebug>

BracketTableModel::BracketTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int BracketTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return JMApp()->bracketController()->size();
}

int BracketTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
   return bracket::MAX_BRACKET_ITEMS;
}

QVariant BracketTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Vertical)
    {
        if(role == Qt::DisplayRole)
        {
            return QVariant(section+1);
        }
        return QVariant();
    }

    if(role == Qt::DisplayRole)
    {

        switch(section)
        {
            case bracket::Name:
                return QVariant("Name");

            case bracket::Gender:
                return QVariant("Gender");

            case bracket::Type://1:
                return QVariant("Type");

            case bracket::MinAge://2:
                return QVariant("Min Age");

            case bracket::MaxAge://3:
                return QVariant("Max Age");

           case bracket::MaxWeight://4:
                return QVariant("Max Weight");

            case bracket::Time:
                return QVariant("Match Len");

           case bracket::AllowChokes:
                return QVariant("Chokes");

            case bracket::AllowArmBars:
                return QVariant("Armbars");

            case bracket::MatNum:
                return QVariant("Mat");
            case bracket::Competitors:
                return QVariant("# Comp");
           default:
            return QVariant();
        }
    }
    return QVariant();
}

QVariant BracketTableModel::data(const QModelIndex &index, int role) const
{
    const QList<Bracket> brackets = JMApp()->bracketController()->brackets();
    const Bracket selectedBracket = brackets.at(index.row());
    switch(role)
    {
        case Qt::DisplayRole:
        case Qt::EditRole:
        {

            int col = index.column();
            switch(col)
            {
                case bracket::Name: // Name
                    return QVariant(selectedBracket.name());
                break;

                case bracket::Gender:
                    return QVariant(genderToString(selectedBracket.gender()));
                    break;

                case bracket::Type: // Type
                    return QVariant(Bracket::weightTypeToStr(selectedBracket.weightType()));

                break;

                case bracket::MinAge: // Min Age
                    return QVariant(selectedBracket.minAge());
                break;

                case bracket::MaxAge: // Max Age
                    return QVariant(selectedBracket.maxAge());
                break;

                case bracket::MaxWeight: // Max Weight
                    return QVariant(selectedBracket.maxWeight());
                break;

                case bracket::Time:
                    return QVariant(selectedBracket.time());

                case bracket::AllowChokes:
                    return QVariant(selectedBracket.chokesAllowed());

                case bracket::AllowArmBars:
                    return QVariant(selectedBracket.armbarsAllowed());

                case bracket::MatNum:
                    return QVariant(selectedBracket.matNumber());
                case bracket::Competitors:
                        // TODO - Fix with command?
                    return QVariant(JMApp()->bracketController()->competitors(selectedBracket.id()).size());
                default:
                    return QVariant("Unknown");
            }
        }
            break;

        case Qt::CheckStateRole:
            switch(index.column())
            {
                case bracket::AllowChokes:
                {
                    if(selectedBracket.chokesAllowed())
                        return Qt::Checked;
                    else
                        return Qt::Unchecked;

                }
                case bracket::AllowArmBars:
                {
                    if(selectedBracket.armbarsAllowed())
                        return Qt::Checked;
                    else
                        return Qt::Unchecked;
                }
            }

            break;

        case Qt::UserRole:
            return QVariant(selectedBracket.id());
            break;

    }
    return QVariant();
}

Qt::ItemFlags BracketTableModel::flags(const QModelIndex &index) const
{

    Qt::ItemFlags flags = QAbstractTableModel::flags(index);

//    flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    switch (index.column())
    {
        case bracket::AllowChokes:
        case bracket::AllowArmBars:
            flags |= Qt::ItemIsUserCheckable;
        break;
        case bracket::Competitors:
            break;
        default:
            flags |= Qt::ItemIsEditable;
    }


    return flags;
}

bool BracketTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);

    bool updated = true;
    const QList<Bracket> brackets = JMApp()->bracketController()->brackets();
    Bracket bracket = brackets.at(index.row());

    switch(index.column())
    {
        case bracket::Name: // First Name
            bracket.setName(value.toString());
        break;

        case bracket::Gender:
            bracket.setGender(genderFromString(value.toString()));
            break;

        case bracket::Type: // Weight Type
        {
            int t = value.toInt();
            bracket.setWeightType((JM::WeightType)t);
            break;
        }

        case bracket::MinAge: // Min Age
            bracket.setMinAge(value.toInt());
            break;

        case bracket::MaxAge: // Max Age
            bracket.setMaxAge(value.toInt());
            break;

        case bracket::MaxWeight: // Max Weight
            bracket.setMaxWeight(value.toDouble());
            break;

        case bracket::Time:
            bracket.setTime(value.toInt());
            break;

        case bracket::AllowChokes:
            bracket.setChokesAllowed(value.toBool());
            break;

        case bracket::AllowArmBars:
            bracket.setArmbarsAllowed(value.toBool());
            break;

        case bracket::MatNum:
            bracket.setMatNumber(value.toInt());
            break;

        default:
            updated = false;
    }

    if(updated)
    {
        // Now we need to update the bracket.
        JMApp()->bracketController()->updateBracket(bracket);
        emit dataChanged(index, index);
    }
    return updated;

}

bool BracketTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + (count - 1));
    for(int x = 0; x < count; x++)
    {
//        QModelIndex index = createIndex(row + x, 0);
        JMApp()->bracketController()->add(-1);
    }
    endInsertRows();

    return true;
}

bool BracketTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + (count - 1));
    for(int x = 0; x < count; x++)
    {
        QModelIndex index = createIndex(row + x, 0);
        QVariant var = data(index, Qt::UserRole);
        JMApp()->bracketController()->remove(var.toInt());
    }
    endRemoveRows();
    return true;
}
