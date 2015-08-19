#pragma once

#include "BaseCommand.h"

#include <QList>
#include <QString>

class Competitor;

class ImportDataCommand : public BaseCommand
{
    Q_OBJECT
public:
    ImportDataCommand(QObject *parent = 0);
    ~ImportDataCommand();

    const QList<Competitor *> importedCompetitors() const;
    const QList<Competitor *> skippedCompetitors() const;

    // BaseCommand interface
    virtual bool run();

private:
    QList<Competitor *> m_importedCompetitors;
    QList<Competitor *> m_skippedCompetitors;
};

