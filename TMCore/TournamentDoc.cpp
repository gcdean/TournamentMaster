#include "TournamentDoc.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>

#include <QDebug>       // DEBUG

#include "data/BracketData.h"
#include "data/Bracket.h"
#include "data/Club.h"
#include "data/Competitor.h"
#include "data/CompetitorData.h"
#include "data/Match.h"
#include "data/Tournament.h"

#include <math.h>

namespace
{
    static Match NO_MATCH(-1);
    static const Bracket NO_BRACKET(-1);

}

TournamentDoc::TournamentDoc()
    : m_tournament()
    , m_modified(false)
    , m_nextClubId(1)
    , m_nextCompetitorId(1)
    , m_nextMatchNum(1)
{

}

TournamentDoc::~TournamentDoc()
{
    qDebug() << "TournamentDoc being deleted.";
}

bool TournamentDoc::isModified()
{
    return m_modified;
}

const Tournament &TournamentDoc::tournament() const
{
    return m_tournament;
}


void TournamentDoc::updateTournament(const Tournament &tournament)
{
    m_tournament = tournament;
//    m_tournament.updateTournament(tournament);
    m_modified = true;
}

const QList<Club> TournamentDoc::clubs()
{
    return m_clubs;
}

const Club TournamentDoc::club(int id) const
{
    int index = m_clubs.indexOf(Club(id));
    if(index >= 0)
    {
        return m_clubs[index];
    }

    return Club();
}

bool TournamentDoc::addClub(Club club)
{
    bool successful = false;
    if(!m_clubs.contains(club))
    {
        m_clubs.append(club);
        successful = true;
        m_modified = true;
    }

    return successful;
}

Club TournamentDoc::addClub()
{
    Club club(m_nextClubId++);
    club.setClubName(QString("Club: %1").arg(club.id()));
    if(addClub(club))
        return club;

    return Club();
}

bool TournamentDoc::removeClub(int id)
{
    bool ret = false;
    int index = m_clubs.indexOf(Club(id));
    if(index >= 0)
    {
        m_clubs.removeAt(index);
        ret = true;
        m_modified = true;
    }
    return ret;
}

bool TournamentDoc::updateClub(const Club &src)
{
    int index = m_clubs.indexOf(src);
    if(index >= 0)
    {
        m_clubs[index] = src;
        return true;
    }

    return false;
}

const QList<Competitor> TournamentDoc::competitors() const
{
    return m_competitors;
}

const Competitor TournamentDoc::competitor(int id) const
{
    int index = m_competitors.indexOf(Competitor(id));
    if(index >= 0)
    {
        return m_competitors[index];
    }

    return Competitor();
}

bool TournamentDoc::addCompetitor(Competitor competitor)
{
    // Insure that the id is 'valid'
    if(!competitor.isValid() || m_competitors.contains(competitor))
    {
        competitor.setId(m_nextCompetitorId++);
    }

    if(!m_competitors.contains(competitor))
    {
        m_competitors.append(competitor);

        // Make sure we have a unique competitor id.
        if(competitor.id() > m_nextCompetitorId)
        {
            m_nextCompetitorId = competitor.id() + 1;
        }
        m_modified = true;
        return true;
    }

    return false;
}

Competitor TournamentDoc::addCompetitor()
{
    Competitor competitor(m_nextCompetitorId++);
    if(addCompetitor(competitor))
    {
        return competitor;
    }

    return Competitor();
}

bool TournamentDoc::removeCompetitor(int id)
{
    int index = m_competitors.indexOf(Competitor(id));
    if(index >= 0)
    {
        m_competitors.removeAt(index);
        m_modified = true;
        return true;
    }
    return false;
}

bool TournamentDoc::updateCompetitor(const Competitor &src)
{
    int index = m_competitors.indexOf(src);
    if(index >= 0)
    {
        m_competitors[index] = src;
        return true;
    }

    return false;
}

const QList<Bracket> TournamentDoc::brackets() const
{
    return m_brackets;
}

const Bracket &TournamentDoc::bracket(int id)
{
    int index = m_brackets.indexOf(Bracket(id));
    if(index >= 0)
    {
        return m_brackets[index];
    }

    return NO_BRACKET;
}

const QList<Competitor> TournamentDoc::bracketCompetitors(int bracketId)
{
    Bracket bracket = m_brackets.at(m_brackets.indexOf(bracketId));

    QList<Competitor> competitors;
    foreach(int id, bracket.competitorIds())
    {
        competitors.append(m_competitors.at(m_competitors.indexOf(id)));
    }

    return competitors;
}

bool TournamentDoc::addBracket(Bracket bracket)
{
    if(!m_brackets.contains(bracket))
    {
        m_brackets.append(bracket);
        m_modified = true;

        return true;
    }
    return false;
}

bool TournamentDoc::removeBracket(int id)
{
    int index = m_brackets.indexOf(Bracket(id));
    if(index >= 0)
    {
        m_brackets.removeAt(index);
        m_modified = true;
        return true;
    }
    return false;
}

bool TournamentDoc::updateBracket(const Bracket &src)
{
    int index = m_brackets.indexOf(src);
    if(index >= 0)
    {
        m_brackets[index] = src;
        m_modified = true;
        return true;
    }
    return false;
}

const QList<Match> TournamentDoc::matches(int bracketid) const
{
    return m_matches[bracketid];
}

const Match TournamentDoc::match(int id)
{
    return nonConstMatch(id);
}

bool TournamentDoc::addMatch(int bracketId, Match &match)
{
    // First, let's see if the match id is valid. If not, set a new one.
    if(match.id() == -1)
    {
        match.setId(m_nextMatchNum++);
    }
    QList<Match> matches;
    if(m_matches.contains(bracketId))
    {
        matches = m_matches[bracketId];
        if(!matches.contains(match.id()))
        {
            match.setBracketId(bracketId);
            matches.append(match);
            m_matches[bracketId] = matches;
            m_matchBrackets[match.id()] = bracketId;
            m_modified = true;
            return true;
        }
    }
    else
    {
        // There are no existing matches for the bracket.
        match.setBracketId(bracketId);
        matches.append(match);
        m_matches[bracketId] = matches;

        m_matchBrackets[match.id()] = bracketId;

        return true;

    }

    return false;
}

Match TournamentDoc::addMatch(int bracketId)
{
    Match match(m_nextMatchNum++);

    bool success = addMatch(bracketId, match);

    if(success)
    {
        return match;
    }

    return Match();
}

bool TournamentDoc::removeMatch(int id)
{
    // TODO - more work needed. need to find match by id.
    int bracketId = m_matchBrackets[id];
    QList<Match> matches = m_matches[bracketId];
    int index = matches.indexOf(id);
    if(index>= 0)
    {
        matches.removeAt(index);
        m_matches[bracketId] = matches;
        m_matchBrackets.remove(id);
        m_modified = true;
        return true;
    }
    return false;
}

bool TournamentDoc::updateMatch(const Match &src)
{

    int bracketId = m_matchBrackets[src.id()];
    if(m_matches.contains(bracketId))
    {
        QList<Match> matches = m_matches[bracketId];
        int index = matches.indexOf(Match(src.id()));
        if(index >= 0)
        {
           matches[index] = src;
           m_matches[bracketId] = matches;
           m_modified = true;
           return true;
        }
    }

    return false;
}


bool TournamentDoc::load(QString filename)
{
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly))
    {
        qWarning("Could not open file for reading");
        return false;
    }

    m_filename = filename;

    QByteArray saveData = file.readAll();

    qDebug() << "Data Size: " << saveData.size();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    m_filename = filename;
//    m_tournament.setFileName(filename);

    QJsonObject jobj = loadDoc.object();

    readTournament(jobj);
    readCompetitors(jobj);

    readBrackets(jobj);
    readClubs(jobj);
    readMatches(jobj);

    m_modified = false;

    return true;
}

QString TournamentDoc::name()
{
    return m_filename;
}

bool TournamentDoc::save()
{
    return save(m_filename);
}

bool TournamentDoc::save(QString filename)
{
    QFile saveFile(filename);

    if(!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Could not open file for writing");
        return false;
    }


    QJsonObject trnObj;
    writeTournament(trnObj);
    writeClubs(trnObj);
    writeBrackets(trnObj);
    writeCompetitors(trnObj);
    writeMatches(trnObj);

    QJsonDocument saveDoc(trnObj);
    if(-1 == saveFile.write(saveDoc.toJson()))
    {
        return false;
    }

    m_filename = filename;
    m_modified = false;

    return true;
}

void TournamentDoc::readTournament(const QJsonObject &jobj)
{
    // Read in the tournament info.

    Tournament trn(jobj["id"].toInt());

    trn.setName(jobj["name"].toString());
    trn.setDate(QDate::fromString(jobj["date"].toString(), "dd.MM.yyyy"));
    trn.setStartTime(QTime::fromString(jobj["starttime"].toString(), "HH.mm"));
    trn.setTexasMatchCards(jobj["texasmatchCards"].toBool());

    m_tournament = trn;
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
        m_nextClubId = std::max(m_nextClubId, club.id());
    }
    m_nextClubId++;

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
        m_nextCompetitorId = std::max(m_nextCompetitorId, competitor.id());
    }
    m_nextCompetitorId++;
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

        m_matches[match.bracketId()].append(match);
        m_matchBrackets[match.id()] = match.bracketId();

        m_nextMatchNum = std::max(m_nextMatchNum, match.id());

    }
    m_nextMatchNum++;
}

void TournamentDoc::writeTournament(QJsonObject &root) const
{
    root["id"] = m_tournament.id();
    root["name"] = m_tournament.name();
    QString temp = m_tournament.date().toString("dd.MM.yyyy");
    root["date"] = temp;
    root["starttime"] = m_tournament.startTime().toString("HH.mm");
    root["texasMatchCards"] = m_tournament.useTexasMatchCards();

}

void TournamentDoc::writeClubs(QJsonObject &root) const
{
    QJsonArray clubArray;
    foreach(const Club club, m_clubs)
    {
        QJsonObject jobj;
        jobj["id"] = club.id();
        jobj["clubname"] = club.clubName();
        jobj["coachname"] = club.coachName();
        jobj["address1"] = club.address1();
        jobj["address2"] = club.address2();
        jobj["country"] = club.country();
        jobj["city"] = club.city();
        jobj["state"] = club.state();
        jobj["zip"] = club.zip();

        clubArray.append(jobj);
    }
    root["clubs"] = clubArray;
}

void TournamentDoc::writeBrackets(QJsonObject &root) const
{
    QJsonArray brackets;
    foreach(Bracket bracket, m_brackets)
    {
        QJsonObject jobj;
        jobj["id"] = bracket.id();

        jobj["name"] = bracket.name();
        jobj["gender"] = genderToString(bracket.gender());
        jobj["weightType"] = Bracket::weightTypeToStr(bracket.weightType());
        jobj["minAge"] = bracket.minAge();
        jobj["maxAge"] = bracket.maxAge();
        jobj["time"] = bracket.time();
        jobj["maxWeight"] = bracket.maxWeight();
        jobj["chokesAllowed"] = bracket.chokesAllowed();
        jobj["armbarsAllowed"] = bracket.armbarsAllowed();
        jobj["matNumber"] = bracket.matNumber();
        jobj["firstPlace"] = bracket.firstPlace();
        jobj["secondPlace"] = bracket.secondPlace();
        jobj["thirdPlace1"] = bracket.thirdPlace1();
        jobj["thirdPlace2"] = bracket.thirdPlace2();

        // Write out the list of competitor ids.
        QJsonArray bracketMembers;
        foreach(const int cid, bracket.competitorIds())
        {
            QJsonValue id(cid);

            bracketMembers.append(id);
        }

        jobj["bracketMembers"] = bracketMembers;


        brackets.append(jobj);
    }

    root["brackets"] = brackets;

}

void TournamentDoc::writeCompetitors(QJsonObject &root) const
{

    QJsonArray judokas;
    foreach(Competitor judoka, m_competitors)
    {
//        qDebug() << "Saving Competitor: " << judoka.lastName() << ", " << judoka.firstName();
        QJsonObject jobj;

        jobj["id"] = judoka.id();
        jobj["fname"] = judoka.firstName();
        jobj["lname"] = judoka.lastName();
        jobj["gender"] = genderToString(judoka.gender());
        jobj["age"] = judoka.age();
        jobj["weight"] = judoka.weight();

        jobj["rank"] = rankToString(judoka.rank());
        jobj["numBrackets"] = judoka.numBrackets();
        jobj["notes"] = judoka.notes();
        jobj["clubid"] = judoka.clubId();

        judokas.append(jobj);
    }

    root["competitors"] = judokas;

}

void TournamentDoc::writeMatches(QJsonObject &root) const
{
    QJsonArray matches;
    QMapIterator <int, QList<Match>> i(m_matches);
    while(i.hasNext())
    {
        i.next();
//        int bracketId = i.key();
        QList<Match> matchList = i.value();

        foreach(Match match, matchList)
        {
            QJsonObject jobj;
            jobj["id"] = match.id();

            jobj["bracketId"] = match.bracketId();
            jobj["matchNumber"] = match.matchNum();

            jobj["competitor1"] = match.competitor1Id();
            jobj["competitor2"] = match.competitor2Id();

            jobj["winner"] = match.winnerId();
            jobj["score"] = match.score();
            jobj["notes"] = match.notes();

            matches.append(jobj);
        }
    }

    root["matches"] = matches;
}

Match TournamentDoc::nonConstMatch(int matchId)
{
    // Get the bracket id for the match
    int bracketId = m_matchBrackets[matchId];
    if(m_matches.contains(bracketId))
    {
        QList<Match> matches = m_matches[bracketId];
        int index = matches.indexOf(Match(matchId));
        if(index >= 0)
        {
           return matches[index];
        }
    }

    return NO_MATCH;

}
