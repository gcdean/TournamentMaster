#pragma once

#include "BaseController.h"
#include <QObject>

class Bracket;

class BracketController : public BaseController
{
    Q_OBJECT

public:
    BracketController(QObject *parent = 0);

    const QList<Bracket> brackets() const;

    // Overrides
    int size() const override;
    int size(int id) const override;

    // BaseController interface
    void add(int parentId) override;
    void remove(int id) override;
    void removeIndex(int index) override;
    Bracket find(int id) const;
    Bracket findById(int id) const;
    int indexOf(int id);

    void updateBracket(Bracket bracket);

    void moveCompetitor(Bracket bracket, int src, int dest);
    void removeCompetitorFromBracket(int bracketId, int competitorId);

    const QList<Competitor> competitors(int parentId = -1) const override;
    const QList<Bracket> competitorBrackets(int competitorId) const;

signals:
    void bracketAdded(int id);
    void bracketRemoved(int id);
    void competitorRemoved(int index);

};

