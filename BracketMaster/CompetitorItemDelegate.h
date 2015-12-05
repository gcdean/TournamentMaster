#pragma once

#include <QStyledItemDelegate>

class QComboBox;

class CompetitorItemDelegate : public QStyledItemDelegate
{
public:
    CompetitorItemDelegate();
    ~CompetitorItemDelegate();


    // QAbstractItemDelegate interface
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void destroyEditor(QWidget *editor, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

private:    // Methods
    QComboBox* genderCombo();

private:    // Data Members
    QComboBox* m_genderCombo;
    QComboBox* m_rankCombo;

    // QAbstractItemDelegate interface
public:
};

