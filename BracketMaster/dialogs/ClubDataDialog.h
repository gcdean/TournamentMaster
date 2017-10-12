#pragma once
#include "data/Club.h"
#include <QDialog>

namespace Ui {
class ClubDataDialog;
}

class ClubDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClubDataDialog(Club club, QWidget *parent = 0);
    ~ClubDataDialog();

    Club getClub();

private:
    void updateControls();
    void updateStateList();
    void updateClub();

private:
    Ui::ClubDataDialog *ui;

    Club m_club;
};

