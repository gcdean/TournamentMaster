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

    void setName(QString name);
    QString name() const;
    void setDate(QDate date);
    QDate date() const;
    void setTime(QTime time);
    QTime time() const;
    void setUseMatchCards(bool matchCards);
    bool useMatchCards() const;

private:
    Ui::TournamentInfoDialog *ui;
};

#endif // TOURNAMENTINFODIALOG_H
