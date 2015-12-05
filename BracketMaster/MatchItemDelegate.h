#pragma once

#include "data/Bracket.h"

#include <QStyledItemDelegate>

class MatchItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MatchItemDelegate(Bracket bracket, QObject *parent = 0);

    // QAbstractItemDelegate interface
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

signals:

public slots:

private:
    Bracket m_bracket;
};

