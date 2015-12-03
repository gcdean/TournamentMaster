#pragma once

#include <QSharedData>

class ClubData : public QSharedData
{
public:
    ClubData() : m_id(-1) {}
    ClubData(int id) : m_id (id) {}
    ClubData(const ClubData& other)
        : QSharedData(other)
        , m_id(other.m_id)
        , m_clubName(other.m_clubName)
        , m_coachName(other.m_coachName)
        , m_address1(other.m_address1)
        , m_address2(other.m_address2)
        , m_country(other.m_country)
        , m_city(other.m_city)
        , m_state(other.m_state)
        , m_zip(other.m_zip)
    {
    }

    int m_id;
    QString m_clubName;
    QString m_coachName;
    QString m_address1;
    QString m_address2;
    QString m_country;
    QString m_city;
    QString m_state;
    QString m_zip;

};


