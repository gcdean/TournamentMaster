#include "ClubListModel.h"



#include "commands/MergeClubsCommand.h"
#include "commands/ClubCommands.h"
#include "controllers/ClubController.h"
#include "JudoMasterApplication.h"

#include <QDebug>
#include <QDataStream>
#include <QMimeData>

ClubListModel::ClubListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    // TODO - Add Add/remove clubs or notifation of them.
}

Club ClubListModel::club(const QModelIndex &index)
{
    return JMApp()->clubController()->clubs().at(index.row());
}

int ClubListModel::rowCount(const QModelIndex &) const
{
    int rows = JMApp()->clubController()->clubs().size();
//    qDebug() << "CLubListModel::rowCount() - " << rows << " rows.";
    return rows;
}

QVariant ClubListModel::data(const QModelIndex &index, int role) const
{
    Club club = JMApp()->clubController()->clubs().at(index.row());

    switch(role)
    {
        case Qt::DisplayRole:
            return QVariant(club.clubName());
        break;

        case Qt::UserRole:
            return QVariant(club.id());
        default:
            return QVariant();
    }
}

QVariant ClubListModel::headerData(int , Qt::Orientation , int role) const
{
    switch(role)
    {
        case Qt::DisplayRole:
            return QVariant(QString("Club Name"));
    }

    return QVariant();
}

Qt::ItemFlags ClubListModel::flags(const QModelIndex &) const
{
    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}


void ClubListModel::clubAdded(Club *)
{
    // The club has already been added.
    int numClubs = JMApp()->clubController()->clubs().size();
    beginInsertRows(QModelIndex(), numClubs - 1, numClubs);
    endInsertRows();
}

void ClubListModel::clubRemoved(Club *club)
{
    // Find the club that's being removed.
    // Find the index.
    int row = JMApp()->clubController()->indexOf(club->id());
    if(row >= 0)
    {
        beginRemoveRows(QModelIndex(), row, row);
        endRemoveRows();
    }

}

bool ClubListModel::dropMimeData(const QMimeData *mimeData, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if(mimeData->hasFormat("application/x-qabstractitemmodeldatalist"))
    {
        QByteArray encoded = mimeData->data("application/x-qabstractitemmodeldatalist");
        QDataStream stream(&encoded, QIODevice::ReadOnly);

        int destRow = parent.row();
        while (!stream.atEnd())
        {
            int srcRow, srcCol;
            QMap<int,  QVariant> roleDataMap;
            stream >> srcRow >> srcCol >> roleDataMap;
            qDebug() << "Dropping " << srcRow << " Onto " << parent.row();

            QModelIndex srcIndex = index(srcRow);
            QModelIndex destIndex = index(destRow);

            int srcClubId = data(srcIndex, Qt::UserRole).toInt();
            int destClubId = data(destIndex, Qt::UserRole).toInt();

            Club srcClub = JMApp()->clubController()->find(srcClubId);
            Club destClub = JMApp()->clubController()->find(destClubId);

            MergeClubsCommand mergeCmd(srcClub, destClub);
            mergeCmd.run(nullptr);
        }
    }

    return QAbstractListModel::dropMimeData(mimeData, action, row, column, parent);
}

Qt::DropActions ClubListModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

Qt::DropActions ClubListModel::supportedDragActions() const
{
    return Qt::MoveAction;
}


bool ClubListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row+count);
    CreatClubCmdPtr createCmd = CreatClubCmdPtr(new CreateClubCommand());
    for(int x = 0; x < count; x++)
    {
        JMApp()->commandController()->doCommand(createCmd);
    }
    endInsertRows();
    return true;
}

bool ClubListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count);

    for(int x = 0; x < count; x++)
    {
        Club club = JMApp()->clubController()->clubs().at(row + x);
        if(club.isValid())
        {
            RemoveClubCmdPtr removeCmd = RemoveClubCmdPtr(new RemoveClubCommand(club));
            JMApp()->commandController()->doCommand(removeCmd);
        }
    }
    endRemoveRows();
    return false;
}
