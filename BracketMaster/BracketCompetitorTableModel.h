#pragma once

#include "CompetitorTableModel.h"

class BracketCompetitorTableModel : public CompetitorTableModel
{
    Q_OBJECT

public:
    BracketCompetitorTableModel(BaseController* controller, QObject *parent = 0);
    ~BracketCompetitorTableModel();

    // QAbstractItemModel interface
public:
    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

signals:
    void numCompetitorsChanged();

public Q_SLOTS:
    void removeCompetitor(int index);
};

