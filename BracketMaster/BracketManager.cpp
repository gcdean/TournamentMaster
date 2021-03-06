#include "BracketManager.h"
#include "ui_BracketManager.h"

#include "data/Bracket.h"
#include "BracketCompetitorTableModel.h"
#include "BracketEditor.h"
#include "BracketTableModel.h"
#include "BracketTypeItemDelegate.h"
#include "data/Competitor.h"
#include "CompetitorEditor.h"
#include "CompetitorFilter.h"
#include "CompetitorTableModel.h"
#include "JMUtil.h"
#include "JudoMasterApplication.h"
#include "data/Tournament.h"
#include "actions/PrintBracketsAction.h"
#include "commands/PrintBrancketsCommand.h"
#include "commands/TournamentCommands.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QLCDNumber>
#include <QList>
#include <QMenu>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QStyledItemDelegate>
#include <QTableView>



BracketManager::BracketManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BracketManager)
{
    ui->setupUi(this);

    m_printAction = new PrintBracketsAction(this);
    m_editBracketAction = new QAction("Edit..", this);

    m_bracketItemDelegate = new BracketTypeItemDelegate();
    ui->bracketList->setTableItemDelegate(m_bracketItemDelegate);
    m_bracketModel = new BracketTableModel(this);
    ui->bracketList->setModel(m_bracketModel);
    ui->bracketList->setController(JMApp()->bracketController());
    ui->bracketList->tableView()->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->bracketList->tableView()->verticalHeader()->setVisible(true);
    ui->bracketList->tableView()->setSortingEnabled(false);
    ui->bracketList->tableView()->verticalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->bracketList->tableView()->setContextMenuPolicy(Qt::CustomContextMenu);


    ui->allCompetitors->tableView()->setSortingEnabled(true);
    ui->allCompetitors->setDisplayEditButtons(false);
    ui->allCompetitors->tableView()->setDragEnabled(true);
    ui->allCompetitors->tableView()->setDragDropMode(QAbstractItemView::DragOnly);
    ui->allCompetitors->tableView()->setDropIndicatorShown(true);
    ui->allCompetitors->tableView()->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->allCompetitors->tableView()->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->allCompetitors->tableView()->verticalHeader()->setVisible(true);
    connect(ui->allCompetitors->tableView()->verticalHeader(), &QHeaderView::sectionDoubleClicked, this, &BracketManager::editCompetitor);

    ui->bracketCompetitors->setDisplayEditButtons(false);
    m_bracketCompetitorModel = new BracketCompetitorTableModel(JMApp()->bracketController());
    ui->bracketCompetitors->setModel(m_bracketCompetitorModel);
    ui->bracketCompetitors->tableView()->setDragDropMode(QAbstractItemView::DragDrop);
    ui->bracketCompetitors->tableView()->setAcceptDrops(true);
    ui->bracketCompetitors->tableView()->viewport()->setAcceptDrops(true);
    ui->bracketCompetitors->tableView()->setDropIndicatorShown(true);
    ui->bracketCompetitors->tableView()->setSortingEnabled(false);
    ui->bracketCompetitors->tableView()->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->notBracketedNum->setPalette(Qt::red);
    ui->notBracketedFrame->setVisible(false);
    setMatNumbers();

    connect(ui->bracketList->tableView()->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &BracketManager::rowChanged);
    connect(ui->allCompetitorsFilter, &CompetitorFilterWidget::applyFilter, this, &BracketManager::competitorFilterChanged);
    connect(JMApp(), &JudoMasterApplication::tournamentChanged, this, &BracketManager::tournamentChanged);
    connect(ui->removeBtn, &QPushButton::clicked, this, &BracketManager::removeCompetitorFromBracket);
    connect(ui->allCompetitors->tableView()->verticalHeader(), &QHeaderView::sectionDoubleClicked, this, &BracketManager::viewCompetitor);
    connect(ui->bracketList->tableView()->verticalHeader(), &QHeaderView::sectionDoubleClicked, this, &BracketManager::editBracket);
    connect(m_bracketCompetitorModel, &BracketCompetitorTableModel::numCompetitorsChanged, this, &BracketManager::resetMatCompetitors);
    connect(m_bracketItemDelegate, &BracketTypeItemDelegate::matNumberChanged, this, &BracketManager::resetMatCompetitors);
    connect(ui->bracketList->tableView()->verticalHeader(), &QWidget::customContextMenuRequested, this, &BracketManager::bracketContextMenu);
    connect(m_printAction, &QAction::triggered, this, &BracketManager::printSelectedBrackets);
    connect(m_editBracketAction, &QAction::triggered, this, &BracketManager::editBracket);

}

BracketManager::~BracketManager()
{
    delete ui;
    delete m_bracketModel;
}

void BracketManager::resetMatCompetitors()
{
    // Adding 1 because brackets with a mat 0 have not been set.
    int numMats = getNumberOfMatsInTournament() + 1;

    int matArray[numMats];

    for(int x = 0; x < numMats; x++)
    {
        matArray[x] = 0;
    }

    const QList<Bracket > brackets = JMApp()->bracketController()->brackets();
    foreach(Bracket bracket, brackets)
    {
        matArray[bracket.matNumber()]+= bracket.competitorIds().size();
    }

    for(int x = 1; x < numMats; x++)
    {
        QLCDNumber *cntr = this->findChild<QLCDNumber *>(QString("mat_%1").arg(x));
        if(cntr)
        {
            cntr->display(matArray[x]);
        }
    }

    if(matArray[0] > 0)
    {
        ui->notBracketedFrame->setVisible(true);
        ui->notBracketedNum->display(matArray[0]);
    }
    else
    {
        ui->notBracketedFrame->setVisible(false);
    }
}

void BracketManager::bracketContextMenu(const QPoint &pos)
{
    // Get the selected indexes.
    QModelIndexList selectedIndexes = ui->bracketList->tableView()->selectionModel()->selectedRows();
    int logicalIndex = ui->bracketList->tableView()->verticalHeader()->logicalIndexAt(pos);
    QModelIndex index = ui->bracketList->tableModel()->index(logicalIndex, 0);

    // If the index we clicked on is not part of the selected indexes, then unselect current ones
    // and select the current index.
    bool found = false;
    for(int x = 0; x < selectedIndexes.size(); x++)
    {
        QModelIndex i = selectedIndexes[x];
        if(i.row() == index.row())
        {
            // the row under the cursor is selected.
            found = true;
            break;
        }
    }

    if(!found)
    {
        ui->bracketList->tableView()->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
        selectedIndexes = ui->bracketList->tableView()->selectionModel()->selectedRows();
    }

    qDebug() << "There are " << selectedIndexes.size() << " selected Indexes";

   QPoint globalPos = ui->bracketList->tableView()->viewport()->mapToGlobal(pos);

   QMenu myMenu;
   m_editBracketAction->setEnabled(selectedIndexes.size() == 1);
   myMenu.addAction(m_editBracketAction);
   myMenu.addAction(m_printAction);
   myMenu.exec(globalPos);
}

void BracketManager::printSelectedBrackets()
{
    QModelIndexList selectedIndexes = ui->bracketList->tableView()->selectionModel()->selectedRows();
    QList<int> bracketIds;
    foreach(QModelIndex index, selectedIndexes)
    {
        bracketIds.append(m_bracketModel->data(index, Qt::UserRole).toInt());
    }

    // TODO - Can command params be changed?
    PrintBracketsCmdPtr cmd = PrintBracketsCmdPtr(new PrintBracketsCommand);
    JMApp()->commandController()->doCommand(cmd);

}


void BracketManager::addBracket()
{
    qDebug() << "ADD A BRACKET";
}

void BracketManager::tournamentChanged()
{
    setMatNumbers();

    ui->bracketList->setModel(new BracketTableModel());
    connect(ui->bracketList->tableView()->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &BracketManager::rowChanged);
    ui->bracketList->tableView()->resizeColumnsToContents();

    m_allCompModel = new CompetitorTableModel(JMApp()->competitorController(), this);
    m_allCompModel->setParentId(-1);
    m_allCompModel->setEditable(false);

    m_allCompSortModel = new QSortFilterProxyModel(this);
    m_allCompSortModel->setSourceModel(m_allCompModel);
    m_allCompSortModel->setSortCaseSensitivity(Qt::CaseInsensitive);

    ui->allCompetitors->tableView()->setModel(m_allCompSortModel);
    ui->allCompetitors->tableView()->resizeColumnsToContents();

    resetMatCompetitors();
}

void BracketManager::rowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if(current.row() == previous.row())
    {
        return;
    }

    BracketTableModel* model = dynamic_cast<BracketTableModel *>(ui->bracketList->tableModel());
    if(model)
    {
        // Get the index of the selected item.
        // Get the bracket id of the selected item.
        QVariant qv = model->data(current, Qt::UserRole);

        // Set the id in the competitor list.
        if(qv.isValid())
        {
            m_currentBracket = JMApp()->bracketController()->find(qv.toInt());
            CompetitorTableModel* cmodel = dynamic_cast<CompetitorTableModel *>(ui->bracketCompetitors->tableModel());
            cmodel->setParentId(qv.toInt());
        }
    }

}

void BracketManager::competitorFilterChanged(const CompetitorFilter &filter)
{
    qDebug() << "BracketManager::competitorFilterChanged() minAge: " << filter.minAge() << ", maxAge: " << filter.maxAge() << ", minWeight: " << filter.minWeight() << ", maxWeight: " << filter.maxWeight();

//    QSortFilterProxyModel* proxyModel = dynamic_cast<QSortFilterProxyModel *>(ui->allCompetitors->tableView()->model());
//    CompetitorTableModel* cmodel = dynamic_cast<CompetitorTableModel *>(proxyModel->sourceModel());
    CompetitorTableModel* cmodel = allCompetitorModel();
    cmodel->setFilter(filter);

}

void BracketManager::removeCompetitorFromBracket()
{
    if(!m_currentBracket.isValid())
        return;

    QModelIndexList lst = ui->bracketCompetitors->tableView()->selectionModel()->selectedRows();
    foreach(const QModelIndex& index, lst)
    {
        // TODO - Fix with command(s). Looks like need to get a competitor at a index of the list of compeitors in the bracket.
//        Competitor *competitor = m_currentBracket->competitors().at(index.row());
//        JMApp()->bracketController()->removeCompetitorFromBracket(m_currentBracket->id(), competitor->id());
    }

    resetMatCompetitors();

}

void BracketManager::viewCompetitor(int logicalIndex)
{
    qDebug() << "BracketManager::viewCompetitor() - index: " << logicalIndex;
    QAbstractItemModel *model = ui->allCompetitors->tableView()->model();
    QModelIndex index = model->index(logicalIndex, 0);
    QVariant qv = model->data(index);
    if(qv.isValid())
    {
        qDebug() << "    Text is: " << qv.toString();
    }
    else
    {
        qDebug() << "    UNKNOWN";
    }
}

void BracketManager::editBracket()
{
    QModelIndexList selected = ui->bracketList->tableView()->selectionModel()->selectedRows();
    if(selected.size() > 1)
    {
        return;
    }

    QModelIndex modelIndex = selected[0];
    QVariant qv = m_bracketModel->data(modelIndex, Qt::UserRole);
    Bracket bracket = JMApp()->bracketController()->find(qv.toInt());

    BracketEditor be(bracket, this);
    be.exec();
}

void BracketManager::editCompetitor()
{
    QModelIndexList selected = ui->allCompetitors->tableView()->selectionModel()->selectedRows();
    if(selected.size() > 1)
    {
        return;
    }

    QModelIndex modelIndex = selected[0];

    QModelIndex rootIndex = m_allCompSortModel->mapToSource(modelIndex);

    CompetitorTableModel *cmodel = allCompetitorModel();
    QVariant qv = cmodel->data(rootIndex, Qt::UserRole);
    Competitor competitor = JMApp()->competitorController()->find(qv.toInt());

    CompetitorEditor editor(competitor, this);
    editor.exec();
}

CompetitorTableModel *BracketManager::allCompetitorModel()
{
    QSortFilterProxyModel* proxyModel = dynamic_cast<QSortFilterProxyModel *>(ui->allCompetitors->tableView()->model());
    CompetitorTableModel* cmodel = dynamic_cast<CompetitorTableModel *>(proxyModel->sourceModel());

    return cmodel;
}

void BracketManager::setMatNumbers()
{
    // Clear out the old controls
    QList<QWidget *> widgets = this->findChildren<QWidget *>(QRegExp("mat_.*"));
    foreach (QWidget *widget, widgets) {
        ui->matNumberLayout->removeWidget(widget);
        delete widget;
    }

    int numMats = getNumberOfMatsInTournament();

    for (int x = numMats; x > 0; x--)
    {
        auto value = new QLCDNumber(this);
        value->setSegmentStyle(QLCDNumber::Flat);
        QString objName = QString("mat_%1").arg(x);
        value->setObjectName(objName);
        ui->matNumberLayout->insertWidget(0, value);


        auto label = new QLabel(QString("Mat %1").arg((x)), this);
        label->setObjectName(QString("mat_%1_label").arg(x));
        ui->matNumberLayout->insertWidget(0, label );
    }
}

int BracketManager::getNumberOfMatsInTournament()
{
    int numMats = 0;
    // Get the tournament info
    GetTournamentCmdPtr getTrnCmd = GetTournamentCmdPtr(new GetTournamentCommand);
    if(JMApp()->commandController()->doCommand(getTrnCmd))
    {
        Tournament tournament = getTrnCmd->tournament();

        numMats = tournament.numMats();
    }

    return numMats;
}
