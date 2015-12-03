#pragma once

#include <QSharedData>

class TournamentData : public QSharedData
{
public:
    TournamentData() : m_id(-1) {}
    TournamentData(int id) : m_id(id) {}
    TournamentData(const TournamentData& other)
        : QSharedData(other)
        , m_id(other.m_id)
        , m_name(other.m_name)
        , m_date(other.m_date)
        , m_startTime(other.m_startTime)
        , m_useTexasMatchCards(other.m_useTexasMatchCards)
    {}

    int m_id;
    QString m_name;
    QDate m_date;
    QTime m_startTime;
    bool m_useTexasMatchCards;


};

