#pragma once

#include "BaseCommand.h"

#include <QList>
#include <QString>

class Competitor;

class ImportDataCommand : public BaseCommand
{
    Q_OBJECT
public:
    ImportDataCommand(QString filename);
    ~ImportDataCommand();

    const QList<Competitor *> importedCompetitors() const;
    const QList<Competitor *> skippedCompetitors() const;

    // BaseCommand interface
    virtual bool run();

private:
    QString m_sourceFile;
    QList<Competitor *> m_importedCompetitors;
    QList<Competitor *> m_skippedCompetitors;
};

