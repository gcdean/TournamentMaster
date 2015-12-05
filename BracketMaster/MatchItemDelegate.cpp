#include "MatchItemDelegate.h"

#include "data/Bracket.h"
#include "data/Competitor.h"
#include "JudoMasterApplication.h"
#include "data/Match.h"
#include "MatchTableModel.h"

#include <QComboBox>

MatchItemDelegate::MatchItemDelegate(Bracket bracket, QObject *parent) :
    QStyledItemDelegate(parent)
    , m_bracket(bracket)
{
    Q_ASSERT(bracket.isValid());
}


QWidget *MatchItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QWidget *widget = 0;
    switch(index.column())
    {
        case MatchTableModel::firstCompetitor:
        case MatchTableModel::secondCompetitor:
        case MatchTableModel::winner:
            widget = new QComboBox(parent);
            break;

        default:
            widget = QStyledItemDelegate::createEditor(parent, option, index);
    }

    return widget;
}

void MatchItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

    switch(index.column())
    {
        case MatchTableModel::firstCompetitor:
        case MatchTableModel::secondCompetitor:
        case MatchTableModel::winner:
        {
            const QList<Match> matches = JMApp()->matchController()->matches(m_bracket.id());
            Q_ASSERT(matches.size() > index.row());

            Match match = matches[index.row()];

            QComboBox *combo = dynamic_cast<QComboBox *>(editor);
            if(combo)
            {
                combo->addItem("<None>", QVariant(-1));
                int currentIndex = 0;
                int x = 1;
                // TODO - Fix with Command
                QList<Competitor> competitors = JMApp()->bracketController()->competitors(m_bracket.id());
                foreach(Competitor competitor, competitors)
                {
                    combo->addItem(QString("%1 %2").arg(competitor.firstName()).arg(competitor.lastName()), QVariant(competitor.id()));
                    if(index.column() == MatchTableModel::firstCompetitor)
                    {

                        if(match.competitor1Id() == competitor.id())
                        {
                            currentIndex = x;
                        }
                    }
                    else if(index.column() == MatchTableModel::secondCompetitor)
                    {
                        if(match.competitor2Id() == competitor.id())
                        {
                            currentIndex = x;
                        }
                    }
                    else if(index.column() == MatchTableModel::winner)
                    {
                        if(match.winnerId() == competitor.id())
                        {
                            currentIndex = x;
                        }
                    }
                    x++;
                }

                combo->setCurrentIndex(currentIndex);

            }
        }
        break;

        default:
            QStyledItemDelegate::setEditorData(editor, index);
    }

}

void MatchItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    switch(index.column())
    {
        case MatchTableModel::firstCompetitor:
        case MatchTableModel::secondCompetitor:
        case MatchTableModel::winner:
        {
            QComboBox *combo = dynamic_cast<QComboBox *>(editor);
            Q_ASSERT(combo);
            int cid = combo->currentData().toInt();
            model->setData(index, QVariant(cid));
        }
            break;

        default:
            QStyledItemDelegate::setModelData(editor, model, index);

    }

}
