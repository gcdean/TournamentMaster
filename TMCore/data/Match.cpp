#include "Match.h"

#include "data/Competitor.h"
#include "JMUtil.h"

#include <QJsonObject>

Match::Match()
{
    m_data = new MatchData;
}

Match::Match(int id)
{
    m_data = new MatchData(id);
}

Match::Match(const Match &src)
    : m_data(src.m_data)
{

}

Match::~Match()
{

}

int Match::id() const
{
    return m_data->m_id;
}

void Match::setId(int id)
{
    m_data->m_id = id;
}

int Match::bracketId() const
{
    return m_data->m_bracketId;
}

void Match::setBracketId(int id)
{
    m_data->m_bracketId = id;
}

int Match::matchNum() const
{
    return m_data->m_matchNum;
}

void Match::setMatchNum(int num)
{
    m_data->m_matchNum = num;
}

void Match::setCompetitor1Id(int id)
{
    m_data->m_competitor1Id = id;
}

int Match::competitor1Id() const
{
    return m_data->m_competitor1Id;
}

void Match::setCompetitor2Id(int id)
{
    m_data->m_competitor2Id = id;
}

int Match::competitor2Id() const
{
    return m_data->m_competitor2Id;
}

void Match::setWinnerId(int id)
{
    m_data->m_winnerId = id;
}

int Match::winnerId() const
{
    return m_data->m_winnerId;
}


int Match::score() const
{
    return m_data->m_score;
}

void Match::setScore(int score)
{
    m_data->m_score = score;
}

const QString Match::notes() const
{
    return m_data->m_notes;
}

void Match::setNotes(QString notes)
{
    m_data->m_notes = notes;
}

bool Match::isValid() const
{
    return m_data->m_id != -1;
}

bool Match::operator ==(const Match &src)
{
    return id() == src.id();
}

//void Match::read(const QJsonObject &json, const QList<Competitor *> competitors)
//{
//    JMDataObj::read(json);
//    m_bracketId = json["bracketId"].toInt();
//    m_matchNum = json["matchNumber"].toInt();
//    int cid1 = json["competitor1"].toInt();
//    int cid2 = json["competitor2"].toInt();
//    int winnerId = json["winner"].toInt();

//    foreach(Competitor *competitor, competitors)
//    {
//        if(cid1 == competitor->id())
//        {
//            m_competitor1 = competitor;
//        }
//        if(cid2 == competitor->id())
//        {
//            m_competitor2 = competitor;
//        }
//        if(winnerId == competitor->id())
//        {
//            m_winner = competitor;
//        }

//        if(m_competitor1 && m_competitor2 && m_winner)
//        {
//            // Everything has been set, we can break out.
//            break;
//        }
//    }

//    m_score = json["score"].toInt();
//    m_notes = json["notes"].toString();

//}


//void Match::read(const QJsonObject &json)
//{
//    read(json, QList<Competitor *>());
//}

//void Match::write(QJsonObject &json) const
//{
//    JMDataObj::write(json);
//    json["bracketId"] = m_bracketId;
//    json["matchNumber"] = m_matchNum;
//    if(m_competitor1)
//        json["competitor1"] = m_competitor1->id();
//    if(m_competitor2)
//        json["competitor2"] = m_competitor2->id();
//    if(m_winner)
//        json["winner"] = m_winner->id();
//    json["score"] = m_score;
//    json["notes"] = m_notes;
//}

void writeMatchHeader(QTextStream &stream)
{
    stream << "MatchId,BracketId,CompetitorId,Type,Notes" << endl;
}

//void Match::write(QTextStream &stream) const
//{
//    QString notes = prepareStringForCSV(QString(m_notes));

//    // Want to write out 3 records, white, blue, winner
//    JMDataObj::write(stream);
//    stream << "," << m_bracketId;
//    stream << "," << (m_competitor1 ? m_competitor1->id() : -1);
//    stream << "," << "white";
//    stream << "," << notes;
//    stream << endl;

//    JMDataObj::write(stream);
//    stream << "," << m_bracketId;
//    stream << "," << (m_competitor2 ? m_competitor2->id() : -1);
//    stream << "," << "blue";
//    stream << "," << notes;
//    stream << endl;

//    JMDataObj::write(stream);
//    stream << "," << m_bracketId;
//    stream << "," << (m_winner ? m_winner->id() : -1);
//    stream << "," << "winner";
//    stream << "," << notes;
//    stream << endl;

////    stream << "," << (m_competitor2 ? m_competitor2->id() : -1);
////    stream << "," << (m_winner ? m_winner->id() : -1);
////    stream << "," << m_score;
////    stream << "," << prepareStringForCSV(QString(m_notes));
////    stream << endl;
//}
