#include "TournamentDoc.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>

#include <QDebug>       // DEBUG

#include "data/Bracket.h"
#include "data/Club.h"
#include "data/Competitor.h"
#include "data/Match.h"
#include "data/Tournament.h"

namespace
{
    static Match NO_MATCH(-1);
    static const Bracket NO_BRACKET(-1);

}

TournamentDoc::TournamentDoc()
    : m_tournament()
    , m_modified(false)
{

}

TournamentDoc::~TournamentDoc()
{

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
    m_tournament.updateTournament(tournament);
    m_modified = true;
}

const QList<Club> TournamentDoc::clubs()
{
    return m_clubs;
}

const Club* TournamentDoc::club(int id) const
{
    int index = m_clubs.indexOf(Club(id));
    if(index >= 0)
    {
        return &m_clubs[index];
    }

    return nullptr;
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

bool TournamentDoc::addCompetitor(Competitor competitor)
{
    if(!m_competitors.contains(competitor))
    {
        m_competitors.append(competitor);
        m_modified = true;
        return true;
    }

    return false;
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

const Match &TournamentDoc::match(int id)
{
    return nonConstMatch(id);
}

bool TournamentDoc::addMatch(int bracketId, Match match)
{
    QList<Match> matches;
    if(m_matches.contains(bracketId))
    {
        matches = m_matches[bracketId];
        if(!matches.contains(match.id()))
        {
            matches.append(match);
            m_matchBrackets[match.id()] = bracketId;
            m_modified = true;
            return true;
        }
    }

    return false;
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
        m_matchBrackets.remove(id);
        m_modified = true;
        return true;
    }
    return false;
}

bool TournamentDoc::updateMatch(const Match &src)
{
    Match& orig = nonConstMatch(src.id());
    if(orig.id() != -1)
    {
        orig = src; // Does this 'persist' the match in the list (due to ref)?
        m_modified = true;
        return true;
    }

    return false;
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

    m_modified = false;
}

void TournamentDoc::save(QString filename)
{
    QFile saveFile(filename);

    if(!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Could not open file for writing");
        return;
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
        return;
    }

    m_modified = false;

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

        m_matches[match.bracketId()].append(match);
        m_matchBrackets[match.id()] = match.bracketId();
    }
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
        qDebug() << "Saving Competitor: " << judoka.lastName() << ", " << judoka.firstName();
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

Match &TournamentDoc::nonConstMatch(int id)
{
    // Get the bracket id for the match
    int bracketId = m_matchBrackets[id];
    if(m_matches.contains(bracketId))
    {
        QList<Match> matches = m_matches[bracketId];
        int index = matches.indexOf(Match(id));
        if(index >= 0)
        {
           return matches[index];
        }
    }

    return NO_MATCH;

}
