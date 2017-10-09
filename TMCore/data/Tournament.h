#pragma once

#include "TMCore.h"
#include "TournamentData.h"

class Tournament
{
public:
    explicit Tournament(int id = -1);
    Tournament(const Tournament& src);

    int id() const;
    void setId(int id);
    QString name() const;
    void setName(QString name);
    QDate date() const;
    void setDate(QDate date);
    QTime startTime() const;
    void setStartTime(QTime startTime);
    bool useTexasMatchCards() const;
    void setTexasMatchCards(bool use);
    int numMats() const;
    void setNumMats(int numMats);

    bool operator ==(const Tournament& src);

private:
    QSharedDataPointer<TournamentData> m_data;

};

