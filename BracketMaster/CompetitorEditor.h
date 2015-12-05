#pragma once

#include <QDialog>

#include "data/Competitor.h"

namespace Ui {
class CompetitorEditor;
}


class CompetitorEditor : public QDialog
{
    Q_OBJECT

public:
    explicit CompetitorEditor(Competitor competitor, QWidget *parent = 0);
    ~CompetitorEditor();

    // QDialog interface
public slots:
    virtual void accept();

private:
    Ui::CompetitorEditor *ui;
    Competitor m_competitor;

};

