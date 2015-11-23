#pragma once

#include "commands/BaseCommand.h"

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
    virtual bool run(IEditor* const editor);

private:
    QList<Competitor *> m_importedCompetitors;
    QList<Competitor *> m_skippedCompetitors;
};

