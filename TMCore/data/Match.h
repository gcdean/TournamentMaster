#pragma once

#include "TMCore.h"
#include "MatchData.h"

#include <QList>
#include <QSharedData>

class Competitor;

void writeMatchHeader(QTextStream &stream);

class TMCORE_DLLSPEC Match
{
public:
    Match();
    Match(int id);
    Match(const Match& src);
    virtual ~Match();

    // NOTE Add specific Judo match scoring?
    int id() const;
    void setId(int id);
    int bracketId() const;
    void setBracketId(int id);
    int matchNum() const;
    void setMatchNum(int num);
    void setCompetitor1Id(int id);
    int competitor1Id() const;
    void setCompetitor2Id(int id);
    int competitor2Id() const;
    void setWinnerId(int id);
    int winnerId() const;
    int score() const;
    void setScore(int score);
    const QString notes() const;
    void setNotes(QString notes);

    bool isValid() const;

    virtual bool operator == (const Match& src);

private:
    QSharedDataPointer<MatchData> m_data;
};

