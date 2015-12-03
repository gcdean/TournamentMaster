#include "BracketCompetitorTableModel.h"

#include "controllers/BaseController.h"
#include "data/Bracket.h"
#include "data/JMDataObj.h"
#include "JudoMasterApplication.h"

#include <QDebug>
#include <QDataStream>
#include <QMimeData>
#include <exception>

BracketCompetitorTableModel::BracketCompetitorTableModel(BaseController *controller, QObject *parent)
    : CompetitorTableModel(controller, parent)
{
    connect(JMApp()->bracketController(), &BracketController::competitorRemoved, this, &BracketCompetitorTableModel::removeCompetitor);
}

BracketCompetitorTableModel::~BracketCompetitorTableModel()
{

}

QStringList BracketCompetitorTableModel::mimeTypes() const
{
    QStringList types = QAbstractTableModel::mimeTypes();
//    types << "application/jm.comp.list";
    types << CompetitorTableModel::mimeTypes();
    return types;
}

QMimeData *BracketCompetitorTableModel::mimeData(const QModelIndexList &indexes) const
{
    return QAbstractTableModel::mimeData(indexes);
}

bool BracketCompetitorTableModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    qDebug() << "row: " << row << ", col: " << column << ", parent.row: " << parent.row() << ", parent.col: " << parent.column();
    if(data->hasFormat("application/x-qabstractitemmodeldatalist"))
    {
        // Internal move.
        BaseController* cntrl = controller();

        int pId = parentId();
        Bracket* bracket = dynamic_cast<Bracket *>(cntrl->find(pId));
        if(bracket)
        {
            qDebug() << "Bracket is: " << bracket->name();
            qDebug() << "HAVE MODLE DATA LIST INFO.";
            QByteArray encoded = data->data("application/x-qabstractitemmodeldatalist");
            QDataStream stream(&encoded, QIODevice::ReadOnly);

            int destRow = parent.row();
            while (!stream.atEnd())
            {
                int srcRow, srcCol;
                QMap<int,  QVariant> roleDataMap;
                stream >> srcRow >> srcCol >> roleDataMap;

                if(destRow == -1)
                {
                    // TODO - Fix with command.
//                    destRow = bracket->competitors().size() - 1;
                }
                /* do something with the data */

                // TODO Fix
                // This is not working correctly. I cannot move a row below/above
                // the next row.
                if(abs(srcRow - destRow) > 1)
                {
                    qDebug() << "Moving srcRow: " << srcRow << ", To row: " << destRow;
                    beginMoveRows(parent, srcRow, srcRow, parent, destRow);
                    // TODO - Fix with command.
//                    try
//                    {
//                        bracket->moveCompetitor(srcRow, destRow);
//                    }
//                    catch (std::exception& ex)
//                    {
//                        qDebug() << "EXCEPTION: " << ex.what();
//                    }

                    endMoveRows();

                    qDebug() << "BracketCompetitorTableModel::dropMimeData() - row: " << srcRow << ", col: " << srcCol << ", variant: " << roleDataMap;
                }
            }
            return true;
        }
        return false;
    }


    bool success = CompetitorTableModel::dropMimeData(data, action, row, column, parent);
    if(success)
        emit numCompetitorsChanged();

    return success;
}

void BracketCompetitorTableModel::removeCompetitor(int index)
{
    qDebug() << "BracketCompetitorTableModel::removeCompetitor(" << index << ")";
    beginRemoveRows(QModelIndex(), index, index);
    endRemoveRows();
}

