#ifndef TOURNAMENTINFODIALOG_H
#define TOURNAMENTINFODIALOG_H

#include <QDialog>

namespace Ui {
class TournamentInfoDialog;
}

class TournamentInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TournamentInfoDialog(QWidget *parent = 0);
    ~TournamentInfoDialog();

private:
    Ui::TournamentInfoDialog *ui;
};

#endif // TOURNAMENTINFODIALOG_H
