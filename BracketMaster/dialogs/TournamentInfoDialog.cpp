#include "TournamentInfoDialog.h"
#include "ui_TournamentInfoDialog.h"

TournamentInfoDialog::TournamentInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TournamentInfoDialog)
{
    ui->setupUi(this);
}

TournamentInfoDialog::~TournamentInfoDialog()
{
    delete ui;
}

void TournamentInfoDialog::setName(QString name)
{
    ui->tournamentName->setText(name);
}

QString TournamentInfoDialog::name() const
{
    return ui->tournamentName->text();
}

void TournamentInfoDialog::setDate(QDate date)
{
    ui->tournamentDate->setDate(date);
}

QDate TournamentInfoDialog::date() const
{
    return ui->tournamentDate->date();
}

void TournamentInfoDialog::setTime(QTime time)
{
    ui->startTime->setTime(time);
}

QTime TournamentInfoDialog::time() const
{
    return ui->startTime->time();
}

void TournamentInfoDialog::setUseMatchCards(bool matchCards)
{
    ui->useTexasMatchCards->setChecked(matchCards);
}

bool TournamentInfoDialog::useMatchCards() const
{
    return ui->useTexasMatchCards->isChecked();
}
