#include "Tournament.h"

#include "data/Bracket.h"
#include "data/Club.h"
#include "data/Competitor.h"
#include "data/Match.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>

Tournament::Tournament(int id)
{
    m_data = new TournamentData;
    setId(id);
}

Tournament::Tournament(const Tournament &src)
    : m_data(src.m_data)
{

}

int Tournament::id() const
{
    return m_data->m_id;
}

void Tournament::setId(int id)
{
    m_data->m_id = id;
}

//void Tournament::updateTournament(const Tournament &src)
//{
//    m_fileName = src.fileName();
//    m_name = src.name();
//    m_date = src.date();
//    m_startTime = src.startTime();
//    m_useTexasMatchCards = src.useTexasMatchCards();

//}


QString Tournament::name() const
{
    return m_data->m_name;
}

void Tournament::setName(QString name)
{
    m_data->m_name = name;
}

QDate Tournament::date() const
{
    return m_data->m_date;
}

void Tournament::setDate(QDate date)
{
    m_data->m_date = date;
}

QTime Tournament::startTime() const
{
    return m_data->m_startTime;
}

void Tournament::setStartTime(QTime startTime)
{
    m_data->m_startTime = startTime;
}


bool Tournament::useTexasMatchCards() const
{
    return m_data->m_useTexasMatchCards;
}

void Tournament::setTexasMatchCards(bool use)
{
    m_data->m_useTexasMatchCards = use;
}

int Tournament::numMats() const
{
    return m_data->m_numMats;
}

void Tournament::setNumMats(int numMats)
{
    m_data->m_numMats = numMats;
}

//void Tournament::read(QJsonObject &json)
//{
//    m_name = json["name"].toString();
//    m_date = QDate::fromString(json["date"].toString(), "dd.MM.yyyy");
//    m_startTime = QTime::fromString(json["starttime"].toString(), "HH.mm");
//    m_useTexasMatchCards = json["texasMatchCards"].toBool();

//    // Read the competitors
////    QJsonArray competitors = json["competitors"].toArray();
////    for(int x = 0; x < competitors.size(); x++)
////    {
////        QJsonObject jobj = competitors[x].toObject();
////        Competitor *competitor = new Competitor();
////        competitor->read(jobj);
////        m_competitors.append(competitor);

////    }
//    qDebug() << "Total Competitors Read In: " << m_competitors.size();

//    // Read the clubs
////    QJsonArray clubs = json["clubs"].toArray();
////    for(int x = 0; x < clubs.size(); x++)
////    {
////        QJsonObject jobj = clubs[x].toObject();
////        Club *club = new Club();
////        club->read(jobj, m_competitors);
////        m_clubs.append(club);
////    }

//    // Let's sort the clubs by name.
//    std::sort(m_clubs.begin(), m_clubs.end(), JM::compareClubNames);

//    // Read the brackets
//    QJsonArray brackets = json["brackets"].toArray();
////    for(int x = 0; x < brackets.size(); x++)
////    {
////        QJsonObject jobj = brackets[x].toObject();
////        Bracket *bracket = new Bracket();
////        bracket->read(jobj, m_competitors);
////        m_brackets.append(bracket);
////    }

//    // Read the matches
//    QJsonArray matches = json["matches"].toArray();
////    for(int x = 0; x < matches.size(); x++)
////    {
////        QJsonObject jobj = matches[x].toObject();
////        Match *match = new Match();
////        match->read(jobj, m_competitors);
////        m_matches.append(match);
////    }
//}

//void Tournament::write(QJsonObject &json) const
//{
//    json["name"] = m_name;
//    QString temp = m_date.toString("dd.MM.yyyy");
//    json["date"] = temp;
//    json["starttime"] = m_startTime.toString("HH.mm");
//    json["texasMatchCards"] = m_useTexasMatchCards;

////    // Clubs
////    QJsonArray clubArray;
////    foreach(const Club* club, m_clubs)
////    {
////        QJsonObject jobj;
////        club->write(jobj);
////        clubArray.append(jobj);
////    }

////    json["clubs"] = clubArray;

//    // Competitors
//    QJsonArray judokas;
////    foreach(Competitor *judoka, m_competitors)
////    {
////        qDebug() << "Saving Competitor: " << judoka->lastName() << ", " << judoka->firstName();
////        QJsonObject jobj;
////        judoka->write(jobj);
////        judokas.append(jobj);
////    }

//    qDebug() << "Total Competitors Saved: " << judokas.size();
//    json["competitors"] = judokas;

//    // Brackets
//    QJsonArray brackets;
////    foreach(Bracket *bracket, m_brackets)
////    {
////        QJsonObject jobj;
////        bracket->write(jobj);
////        brackets.append(jobj);
////    }

//    json["brackets"] = brackets;

//    //  Matches
//    QJsonArray matches;
////    foreach(Match *match, m_matches)
////    {
////        QJsonObject jobj;
////        match->write(jobj);
////        matches.append(jobj);
////    }
//    json["matches"] = matches;
//}

//void Tournament::write(QString dirname) const
//{
//    QDir outputDir(dirname);

//    QFile clubFile(outputDir.absoluteFilePath("Clubs.csv"));
//    clubFile.open(QIODevice::WriteOnly | QIODevice::Text);
//    QTextStream clubStream(&clubFile);

////    writeClubHeader(clubStream);
////    foreach(const Club* club, m_clubs)
////    {
////        club->write(clubStream);
////    }
////    clubFile.close();

//    QFile bracketFile(outputDir.absoluteFilePath("Brackets.csv"));
//    bracketFile.open(QIODevice::WriteOnly | QIODevice::Text);
//    QTextStream bracketStream(&bracketFile);
//    writeBracketHeader(bracketStream);

////    foreach(Bracket *bracket, m_brackets)
////    {
////        bracket->write(bracketStream);
////    }
//    bracketFile.close();

//    QFile bracketCompFile(outputDir.absoluteFilePath("BracketCompetitors.csv"));
//    bracketCompFile.open(QIODevice::WriteOnly | QIODevice::Text);
//    QTextStream bracketCompStream(&bracketCompFile);


//    writeBracketCompetitorHeader(bracketCompStream);

////    foreach(Bracket *bracket, m_brackets)
////    {
////        bracket->writeCompetitors(bracketCompStream);
////    }
//    bracketCompFile.close();

//    QFile bracketPlaceFile(outputDir.absoluteFilePath("BracketPlaces.csv"));
//    bracketPlaceFile.open(QIODevice::WriteOnly | QIODevice::Text);
//    QTextStream bracketPlaceStream(&bracketPlaceFile);
//    writeBracketPlaceHeader(bracketPlaceStream);

////    foreach(Bracket *bracket, m_brackets)
////    {
////        bracket->writePlaces(bracketPlaceStream);
////    }
//    bracketPlaceFile.close();


//    QFile competitorFile(outputDir.absoluteFilePath("Competitors.csv"));
//    competitorFile.open(QIODevice::WriteOnly | QIODevice::Text);
//    QTextStream competitorStream(&competitorFile);
//    writeCompetitorHeader(competitorStream);
////    foreach (Competitor *competitor, m_competitors)
////    {
////        competitor->write(competitorStream);
////    }
//    competitorFile.close();

//    QFile matchFile(outputDir.absoluteFilePath("Matches.csv"));
//    matchFile.open(QIODevice::WriteOnly | QIODevice::Text);
//    QTextStream matchStream(&matchFile);
//    writeMatchHeader(matchStream);
////    foreach(Match *match, m_matches)
////    {
////        match->write(matchStream);
////    }
//    matchFile.close();

//}

//Tournament &Tournament::operator =(const Tournament &src)
//{
//    TMBaseData::operator =(src);
//    setFileName(src.fileName());
//    setName(src.name());
//    setDate(src.date());
//    setStartTime(src.startTime());
//    setTexasMatchCards(src.useTexasMatchCards());

//    return *this;
//}

