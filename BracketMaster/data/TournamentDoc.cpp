#include "TournamentDoc.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>

#include <QDebug>       // DEBUG

#include "Bracket.h"
#include "Club.h"
#include "Competitor.h"
#include "Match.h"
#include "Tournament.h"

TournamentDoc::TournamentDoc()
    : m_tournament()
{

}

TournamentDoc::~TournamentDoc()
{

}

void TournamentDoc::load(QString filename)
{
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly))
    {
        qWarning("Could not open file for reading");
        return;
    }

    QByteArray saveData = file.readAll();

    qDebug() << "Data Size: " << saveData.size();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    m_tournament.setFileName(filename);

    QJsonObject jobj = loadDoc.object();

    readTournament(jobj);
    readCompetitors(jobj);

    readBrackets(jobj);
    readClubs(jobj);
    readMatches(jobj);

}

void TournamentDoc::save(QString filename) const
{
    QFile saveFile(filename);

    if(!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Could not open file for writing");
        return;
    }

    QJsonObject trnObj;
    writeTournament(trnObj);
//    writeClubs(trnObj);
//    writeBrackets(trnObj);
//    writeCompetitors(trnObj);
//    writeMatches(trnObj);

    QJsonDocument saveDoc(trnObj);
    if(-1 == saveFile.write(saveDoc.toJson()))
    {
        return;
    }

}

void TournamentDoc::readTournament(const QJsonObject &jobj)
{
    // Read in the tournament info.

    m_tournament.setName(jobj["name"].toString());
    m_tournament.setDate(QDate::fromString(jobj["date"].toString(), "dd.MM.yyyy"));
    m_tournament.setStartTime(QTime::fromString(jobj["starttime"].toString(), "HH.mm"));
    m_tournament.setTexasMatchCards(jobj["texasmatchCards"].toBool());

    qDebug() << "Tourn Name: " << m_tournament.name();

}

void TournamentDoc::readBrackets(const QJsonObject &root)
{
    QJsonArray brackets = root["brackets"].toArray();
    for(int x = 0; x < brackets.size(); x++)
    {
        QJsonObject jobj = brackets[x].toObject();

        Bracket bracket (jobj["id"].toInt());

        bracket.setName(jobj["name"].toString());
        bracket.setGender(genderFromString(jobj["gender"].toString()));
        bracket.setWeightType(Bracket::weightTypeFromStr(jobj["weightType"].toString()));
        bracket.setMinAge(jobj["minAge"].toInt());
        bracket.setMaxAge(jobj["maxAge"].toInt());
        int time = jobj["time"].toInt();
        if(time == 0)
        {
            time = 3;
        }
        bracket.setTime(time);
        bracket.setMaxWeight(jobj["maxWeight"].toDouble());
        bracket.setChokesAllowed(jobj["chokesAllowed"].toBool());
        bracket.setArmbarsAllowed(jobj["armbarsAllowed"].toBool());
        bracket.setMatNumber(jobj["matNumber"].toInt());
        bracket.setFirstPlace(jobj["firstPlace"].toInt());
        bracket.setSecondPlace(jobj["secondPlace"].toInt());
        bracket.setThirdPlace1(jobj["thirdPlace1"].toInt());
        bracket.setThirdPlace2(jobj["thirdPlace2"].toInt());

        QJsonArray bracketMembers = jobj["bracketMembers"].toArray();

        for(int x = 0; x < bracketMembers.size(); x++)
        {
            int id = bracketMembers[x].toInt();
            bracket.addCompetitor(id);
        }

        m_brackets.append(bracket);
    }

}

void TournamentDoc::readClubs(const QJsonObject &root)
{
    QJsonArray clubs = root["clubs"].toArray();
    for(int x = 0; x < clubs.size(); x++)
    {
        QJsonObject jobj = clubs[x].toObject();

        Club club(jobj["id"].toInt());
        club.setClubName(jobj["clubname"].toString());
        club.setCoachName(jobj["coachname"].toString());
        club.setAddress1(jobj["address1"].toString());
        club.setAddress2(jobj["address2"].toString());
        club.setCountry(jobj["coutnry"].toString());
        club.setCity(jobj["city"].toString());
        club.setState(jobj["state"].toString());
        club.setZip(jobj["zip"].toString());

        m_clubs.append(club);
    }

}

void TournamentDoc::readCompetitors(const QJsonObject &root)
{
    m_competitors.size();
    QJsonArray competitors = root["competitors"].toArray();
    for(int x = 0; x < competitors.size(); x++)
    {
        QJsonObject jobj = competitors[x].toObject();

        Competitor  competitor(jobj["id"].toInt());

        competitor.setFirstName(jobj["fname"].toString());
        competitor.setLastName(jobj["lname"].toString());
        competitor.setGender(genderFromString(jobj["gender"].toString()));
        competitor.setAge(jobj["age"].toInt());
        competitor.setWeight(jobj["weight"].toDouble());
        competitor.setRank(rankFromString(jobj["rank"].toString()));
        competitor.setNumBrackets(jobj["numBrackets"].toInt());
        competitor.setNotes(jobj["notes"].toString());
        competitor.setClubId(jobj["clubid"].toInt());

        m_competitors.append(competitor);

    }
    qDebug() << "Total Competitors Read In: " << m_competitors.size();

}

void TournamentDoc::readMatches(const QJsonObject &root)
{
    QJsonArray matches = root["matches"].toArray();
    for(int x = 0; x < matches.size(); x++)
    {
        QJsonObject jobj = matches[x].toObject();
        Match match(jobj["id"].toInt());

        match.setBracketId(jobj["bracketId"].toInt());
        match.setMatchNum(jobj["matchNumber"].toInt());
        match.setCompetitor1Id(jobj["competitor1"].toInt());
        match.setCompetitor2Id(jobj["competitor2"].toInt());
        match.setWinnerId(jobj["winner"].toInt());
        match.setScore(jobj["score"].toInt());
        match.setNotes(jobj["notes"].toString());

        m_matches[match.bracketId()] = match;
    }
}

void TournamentDoc::writeTournament(QJsonObject &root) const
{
    root["name"] = m_tournament.name();
    QString temp = m_tournament.date().toString("dd.MM.yyyy");
    root["date"] = temp;
    root["starttime"] = m_tournament.startTime().toString("HH.mm");
    root["texasMatchCards"] = m_tournament.useTexasMatchCards();

}

void TournamentDoc::writeClubs(QJsonObject &root) const
{
    Q_UNUSED(root)

}

void TournamentDoc::writeBrackets(QJsonObject &root) const
{
    Q_UNUSED(root)

}

void TournamentDoc::writeCompetitors(QJsonObject &root) const
{
    Q_UNUSED(root)

}

void TournamentDoc::writeMatches(QJsonObject &root) const
{
    Q_UNUSED(root)
}
