#pragma once

#include <QSharedData>

class MatchData : public QSharedData
{
public:
    MatchData()
        : m_id(-1)
        , m_bracketId(-1)
        , m_matchNum(-1)
        , m_competitor1Id(-1)
        , m_competitor2Id(-1)
        , m_winnerId(-1)
        , m_score(-1)
    {}
    MatchData(int id) : m_id(id)
      , m_matchNum(-1)
      , m_competitor1Id(-1)
      , m_competitor2Id(-1)
      , m_winnerId(-1)
      , m_score(-1)
    {}

    MatchData(const MatchData& other)
        :QSharedData(other)
        , m_id(other.m_id)
        , m_bracketId(other.m_bracketId)
        , m_matchNum(other.m_matchNum)
        , m_competitor1Id(other.m_competitor1Id)
        , m_competitor2Id(other.m_competitor2Id)
        , m_winnerId(other.m_winnerId)
        , m_score(other.m_score)
        , m_notes(other.m_notes)
    {}

    int m_id;
    int m_bracketId;
    int m_matchNum;     // For when Texas Match Card system is used.
    int m_competitor1Id;
    int m_competitor2Id;
    int m_winnerId;
    int m_score;
    QString m_notes;

};

