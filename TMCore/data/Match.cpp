#include "Match.h"

#include "data/Competitor.h"
#include "JMUtil.h"

#include <QJsonObject>

Match::Match()
    : JMDataObj(-1)
    , m_bracketId(-1)
    , m_matchNum(-1)
    , m_competitor1(0)
    , m_competitor2(0)
    , m_winner(0)
    , m_score(-1)
{

}

Match::Match(int id)
    : JMDataObj(id)
    , m_bracketId(-1)
    , m_matchNum(-1)
    , m_competitor1(0)
    , m_competitor2(0)
    , m_winner(0)
    , m_score(-1)
{
}

int Match::bracketId() const
{
    return m_bracketId;
}

void Match::setBracketId(int id)
{
    m_bracketId = id;
}

int Match::matchNum()
{
    return m_matchNum;
}

void Match::setMatchNum(int num)
{
    m_matchNum = num;
}

void Match::setCompetitor1Id(int id)
{
    m_competitor1Id = id;
}

int Match::competitor1Id()
{
    return m_competitor1Id;
}

void Match::setCompetitor2Id(int id)
{
    m_competitor2Id = id;
}

int Match::competitor2Id()
{
    return m_competitor2Id;
}

void Match::setWinnerId(int id)
{
    m_winnerId = id;
}

int Match::winnerId()
{
    return m_winnerId;
}

const Competitor *Match::competitor1() const
{
    return m_competitor1;
}

void Match::setCompetitor1(Competitor *competitor)
{
    m_competitor1 = competitor;
    setCompetitor1Id(competitor ? competitor->id() : -1);
}

const Competitor *Match::competitor2() const
{
    return m_competitor2;
}

void Match::setCompetitor2(Competitor *competitor)
{
    m_competitor2 = competitor;
    setCompetitor2Id(competitor ? competitor->id() : -1);
}

const Competitor *Match::winner() const
{
    return m_winner;
}

void Match::setWinner(Competitor *competitor)
{
    m_winner = competitor;

    setWinnerId(competitor ? competitor->id() : -1);
}

int Match::score() const
{
    return m_score;
}

void Match::setScore(int score)
{
    m_score = score;
}

const QString Match::notes() const
{
    return m_notes;
}

void Match::setNotes(QString notes)
{
    m_notes = notes;
}

void Match::read(const QJsonObject &json, const QList<Competitor *> competitors)
{
    JMDataObj::read(json);
    m_bracketId = json["bracketId"].toInt();
    m_matchNum = json["matchNumber"].toInt();
    int cid1 = json["competitor1"].toInt();
    int cid2 = json["competitor2"].toInt();
    int winnerId = json["winner"].toInt();

    foreach(Competitor *competitor, competitors)
    {
        if(cid1 == competitor->id())
        {
            m_competitor1 = competitor;
        }
        if(cid2 == competitor->id())
        {
            m_competitor2 = competitor;
        }
        if(winnerId == competitor->id())
        {
            m_winner = competitor;
        }

        if(m_competitor1 && m_competitor2 && m_winner)
        {
            // Everything has been set, we can break out.
            break;
        }
    }

    m_score = json["score"].toInt();
    m_notes = json["notes"].toString();

}


void Match::read(const QJsonObject &json)
{
    read(json, QList<Competitor *>());
}

void Match::write(QJsonObject &json) const
{
    JMDataObj::write(json);
    json["bracketId"] = m_bracketId;
    json["matchNumber"] = m_matchNum;
    if(m_competitor1)
        json["competitor1"] = m_competitor1->id();
    if(m_competitor2)
        json["competitor2"] = m_competitor2->id();
    if(m_winner)
        json["winner"] = m_winner->id();
    json["score"] = m_score;
    json["notes"] = m_notes;
}

void writeMatchHeader(QTextStream &stream)
{
    stream << "MatchId,BracketId,CompetitorId,Type,Notes" << endl;
}

void Match::write(QTextStream &stream) const
{
    QString notes = prepareStringForCSV(QString(m_notes));

    // Want to write out 3 records, white, blue, winner
    JMDataObj::write(stream);
    stream << "," << m_bracketId;
    stream << "," << (m_competitor1 ? m_competitor1->id() : -1);
    stream << "," << "white";
    stream << "," << notes;
    stream << endl;

    JMDataObj::write(stream);
    stream << "," << m_bracketId;
    stream << "," << (m_competitor2 ? m_competitor2->id() : -1);
    stream << "," << "blue";
    stream << "," << notes;
    stream << endl;

    JMDataObj::write(stream);
    stream << "," << m_bracketId;
    stream << "," << (m_winner ? m_winner->id() : -1);
    stream << "," << "winner";
    stream << "," << notes;
    stream << endl;

//    stream << "," << (m_competitor2 ? m_competitor2->id() : -1);
//    stream << "," << (m_winner ? m_winner->id() : -1);
//    stream << "," << m_score;
//    stream << "," << prepareStringForCSV(QString(m_notes));
//    stream << endl;
}
