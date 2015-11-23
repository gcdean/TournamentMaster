#pragma once

#include "commands/BaseCommand.h"
#include <QList>

class QWidget;
class Club;

class PrintRegistrationCommand : public BaseCommand
{
    Q_OBJECT
public:
    PrintRegistrationCommand(QWidget *parent = 0, QList<Club >clubs=QList<Club >());
    ~PrintRegistrationCommand();

    // BaseCommand interface
public:
    bool run(IEditor* const editor) override;

private:
    QList<Club > getClubs();

private:
    QList<Club > m_clubs;
};

