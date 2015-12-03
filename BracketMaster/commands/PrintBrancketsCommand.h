#pragma once

#include "commands/BaseCommand.h"
#include <QList>
#include <QString>

class Tournament;

class PrintBracketsCommand : public BaseCommand
{
    Q_OBJECT

public:
    PrintBracketsCommand(QObject *parent = 0);
    PrintBracketsCommand(QString tournament, QList<int> brackets);
    ~PrintBracketsCommand();

    // BaseCommand interface
    bool run(IDocument* const doc) override;

private:
    QString m_tournament;
    QList<int> m_bracketIds;
};

