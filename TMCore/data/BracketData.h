#pragma once

#include <QSharedData>

#include "JMUtil.h"

class BracketData : public QSharedData
{
public:
    BracketData() : m_id(-1) {}
    BracketData(int id) : m_id(id) {}
    BracketData(const BracketData& other)
        : QSharedData(other)
        , m_id(other.m_id)
        , m_name(other.m_name)
        , m_gender(other.m_gender)
        , m_weightType(other.m_weightType)
        , m_minAge(other.m_minAge)
        , m_maxAge(other.m_maxAge)
        , m_time(other.m_time)
        , m_chokesAllowed(other.m_chokesAllowed)
        , m_armbarsAllowed(other.m_armbarsAllowed)
        , m_matNumber(other.m_matNumber)
        , m_firstPlace(other.m_firstPlace)
        , m_secondPlace(other.m_secondPlace)
        , m_thirdPlace_1(other.m_thirdPlace_1)
        , m_thirdPlace_2(other.m_thirdPlace_2)
        , m_maxWeight(other.m_maxWeight)
        , m_competitorIds(other.m_competitorIds)
    {}
    ~BracketData() {}

    int m_id;

    QString m_name;
    JM::Gender m_gender;
    JM::WeightType m_weightType;

    int m_minAge;
    int m_maxAge;
    int m_time;
    bool m_chokesAllowed;
    bool m_armbarsAllowed;
    int m_matNumber;
    int m_firstPlace;
    int m_secondPlace;
    int m_thirdPlace_1;
    int m_thirdPlace_2;

    double m_maxWeight;
    QList<int> m_competitorIds;


};

