#pragma once

#include <QSharedData>

#include "JMUtil.h"

class CompetitorData : public QSharedData
{
public:
    CompetitorData() : m_id(-1) {}
    CompetitorData(int id) : m_id(id) {}
    CompetitorData(const CompetitorData& other)
        : QSharedData(other)
        , m_id(other.m_id)
        , m_firstName(other.m_firstName)
        , m_lastName(other.m_lastName)
        , m_gender(other.m_gender)
        , m_age(other.m_age)
        , m_weight(other.m_weight)
        , m_rank(other.m_rank)
        , m_numBrackets(other.m_numBrackets)
        , m_notes(other.m_notes)
        , m_clubId(other.m_clubId)
    {}

    int m_id;
    QString m_firstName;
    QString m_lastName;
    JM::Gender m_gender;
    int m_age;
    double m_weight;
    JM::Rank m_rank;
    int m_numBrackets;
    QString m_notes;
    int m_clubId;

};

