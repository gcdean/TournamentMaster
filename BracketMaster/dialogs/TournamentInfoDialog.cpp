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
