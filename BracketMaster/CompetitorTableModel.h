#pragma once

#include "CompetitorFilter.h"

#include <QAbstractTableModel>

class BaseController;
class Competitor;

class CompetitorTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CompetitorTableModel(BaseController* controller, QObject *parent = 0);

    void setParentId(int id);
    void setFilter(const CompetitorFilter& filter);
    void setEditable(bool editable);
    bool editable();

    // Overrides
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;

    // Drag Drop methods
    Qt::DropActions supportedDragActions() const override;
    Qt::DropActions supportedDropActions() const override;
    QStringList mimeTypes() const override;
    QMimeData* mimeData(const QModelIndexList &indexes) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;
signals:

public slots:

protected:
    BaseController* controller();
    int parentId() const;

private:    // Methods
    QVariant columnBackground(const Competitor judoka, int col) const;

private:    // Data Members
    int m_parentId;   // This is the id of the parent, club or bracket.
    BaseController *m_controller;
    bool m_editable;
    CompetitorFilter m_filter;

};

