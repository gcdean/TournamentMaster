#pragma once

#include "BaseController.h"

class Match;

class MatchController : public BaseController
{
    Q_OBJECT
public:
    MatchController(QObject *parent = 0);

    // BaseController interface
public:
    void add(int parentId) override;
    void update(Match match);
    Match find(int id) const;
    int indexOf(int id) override;
    void remove(int id) override;
    int size() const override;
    int size(int id) const override;

    const QList<Match> matches(int bracketId) const;

};

