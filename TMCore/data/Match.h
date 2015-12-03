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
    const Competitor *competitor1() const;
    void setCompetitor1(Competitor *competitor);
    const Competitor *competitor2() const;
    void setCompetitor2(Competitor *competitor);
    const Competitor *winner() const;
    void setWinner(Competitor *competitor);
    int score() const;
    void setScore(int score);
    const QString notes() const;
    void setNotes(QString notes);

    bool isValid() const;

    virtual bool operator == (const Match& src);


//    void read(const QJsonObject& json, const QList<Competitor *> competitors);
    // JMDataObj interface
//    void read(const QJsonObject &json) override;
//    void write(QJsonObject &json) const override;
//    void write(QTextStream &stream) const override;

private:
    QSharedDataPointer<MatchData> m_data;
//    int m_bracketId;
//    int m_matchNum;     // For when Texas Match Card system is used.
//    int m_competitor1Id;
//    int m_competitor2Id;
//    int m_winnerId;
//    Competitor *m_competitor1;  // White
//    Competitor *m_competitor2;  // Blue
//    Competitor *m_winner;
//    int m_score;
//    QString m_notes;
};

