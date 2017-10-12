#include "ClubsEditor.h"
#include "ui_ClubsEditor.h"

#include "ClubListModel.h"
#include "CompetitorItemDelegate.h"
#include "CompetitorTableModel.h"
#include "JudoMasterApplication.h"
#include "commands/ClubInfoUpdateCommand.h"
#include "commands/PrintRegistrationCommand.h"

#include <QAbstractListModel>

#include <QDebug>
#include <QMenu>
#include <QSortFilterProxyModel>
#include <QTableView>

ClubsEditor::ClubsEditor(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::ClubsEditor)
    , m_printClubRegAction(0)
{
    ui->setupUi(this);

    m_printClubRegAction = new QAction("Print Registration...", this);

    ui->clubList->setModel(new ClubListModel(ui->clubList));

    ui->clubList->setContextMenuPolicy(Qt::CustomContextMenu);


    CompetitorTableModel *sourceModel = new CompetitorTableModel(JMApp()->competitorController(), this);
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(sourceModel);

    ui->competitorsList->tableView()->setSortingEnabled(true);
    ui->competitorsList->tableView()->setModel(proxyModel);
    ui->competitorsList->setTableItemDelegate(new CompetitorItemDelegate);
    ui->competitorsList->setController(JMApp()->competitorController());
    ui->competitorsList->tableView()->verticalHeader()->setVisible(true);

    connect(ui->addClubBtn, &QPushButton::clicked, this, &ClubsEditor::addClub);
    connect(ui->removeClubBtn, &QPushButton::clicked, this, &ClubsEditor::removeClub);
    // TODO - Fix
    //connect(this, &ClubsEditor::clubAdded, ui->clubEditor, &ClubEditor::editClub);
    connect(this, &ClubsEditor::clubSelect, ui->clubEditor, &ClubEditor::editClub);

    connect(ui->clubList->selectionModel(), &QItemSelectionModel::currentChanged, this, &ClubsEditor::clubSelected);
    connect(JMApp(), &JudoMasterApplication::tournamentChanged, this, &ClubsEditor::tournamentChanged);

    connect(ui->clubList, &QWidget::customContextMenuRequested, this, &ClubsEditor::clubContextMenu);
    connect(m_printClubRegAction, &QAction::triggered, this, &ClubsEditor::printClubRegistration);

    connect(JMApp(), &JudoMasterApplication::editClub, this, &ClubsEditor::editSelectedClub);

}

ClubsEditor::~ClubsEditor()
{
    delete ui;
}

void ClubsEditor::addClub()
{
    ClubListModel* model = dynamic_cast<ClubListModel *>(ui->clubList->model());
    if(!model)
        return; // Handle null value

    JMApp()->clubController()->createClub();
    QModelIndex addedIndex = model->index(JMApp()->clubController()->clubs().size() - 1, 0);
    ui->clubList->selectionModel()->select(addedIndex, QItemSelectionModel::ClearAndSelect);
    clubSelected(addedIndex);
}

void ClubsEditor::removeClub()
{
    QModelIndexList selected = ui->clubList->selectionModel()->selectedIndexes();
    for(int x = 0; x < selected.size(); x++)
    {
        QModelIndex index = selected[x];
        qDebug() << "Removing Row: " << index.row();
        JMApp()->clubController()->removeIndex(index.row());
    }
}

void ClubsEditor::clubSelected(const QModelIndex &index)
{
    ClubListModel* model = dynamic_cast<ClubListModel *>(ui->clubList->model());
    if(!model)
        return; // Handle null value

    ui->competitorsList->setClubId(model->club(index).id());
    emit clubSelect(model->club(index));
}

void ClubsEditor::tournamentChanged()
{
    ui->clubList->reset();
}

void ClubsEditor::clubContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->clubList->viewport()->mapToGlobal(pos);

    QMenu contextMenu;
    contextMenu.addAction(m_printClubRegAction);

    contextMenu.exec(globalPos);

}

void ClubsEditor::printClubRegistration()
{
    Q_ASSERT(true);
//    QModelIndexList indexes = ui->clubList->selectionModel()->selectedRows();
//    QList<Club *> selectedClubs;
//    foreach(QModelIndex index, indexes)
//    {
//        Club *club = dynamic_cast<Club *>(JMApp()->clubController()->find(ui->clubList->model()->data(index, Qt::UserRole).toInt()));
//        if(club)
//        {
//            selectedClubs.append(club);
//        }
//    }

//    PrintRegistrationCommand cmd(this, selectedClubs);
    //    cmd.run(nullptr);
}

void ClubsEditor::editSelectedClub()
{
    QModelIndexList selectedClubs = ui->clubList->selectionModel()->selectedRows();
    if(selectedClubs.size() == 1)   // Only if there is one item selected.
    {
        int clubId = ui->clubList->model()->data(selectedClubs[0], Qt::UserRole).toInt();
        qDebug() << "ClubsEditor::editSelectedClub() - Selected Club is: " << selectedClubs[0].row() << ", Club Id: " << clubId;

        ClubInfoUpdateCommandPtr cmd = ClubInfoUpdateCommandPtr(new ClubInfoUpdateCommand(this, clubId));

        JMApp()->commandController()->doCommand(cmd);
    }
}
