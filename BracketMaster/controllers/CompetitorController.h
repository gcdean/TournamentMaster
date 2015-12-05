#pragma once

#include "BaseController.h"
#include "JMUtil.h"
#include <QObject>

class Competitor;

/**
 * @brief Manages Competitors
 *
 */
class CompetitorController : public BaseController
{
    Q_OBJECT
public:
    explicit CompetitorController(QObject *parent = 0);

    Competitor createCompetitor(QString firstName, QString lastName, JM::Gender gender, int age , double weight, JM::Rank rank, int clubId);
    void updateCompetitor(Competitor competitor);

    int size() const /*override*/;
    int size(int id) const /*override*/;

    Competitor findByName(QString firstName, QString lastName);

//    const QList<Competitor *> clubCompetitors(int clubId) const;
    const QList<Competitor> competitors(int parentId = -1) const override;
    Competitor find(int id) const;
    void add(int parentId) override;

signals:
    void competitorAdded(Competitor *competitor);

};

