#include "Bracket.h"

#include "JMUtil.h"

#include "data/BracketData.h"
#include "data/Competitor.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonValue>
#include <QString>
#include <QTextStream>


namespace bracket
{
    const QString AbsoluteStr("IJF");
    const QString LightStr("Light");
    const QString MediumStr("Medium");
    const QString HeavyStr("Heavy");
    const QString SuperHeavyStr("Super Heavy");
    const QString UnknownWeightType("Unknown");
}

using namespace bracket;

Bracket::Bracket()
{
    m_data = new BracketData;
}

Bracket::Bracket(int id)
{
    m_data = new BracketData;
    setId(id);
}

Bracket::Bracket(const Bracket &src)
    : m_data(src.m_data)
{
}

Bracket::~Bracket()
{

}

//void Bracket::read(const QJsonObject &json)
//{
//    read(json, QList<Competitor *>());
//}

//void Bracket::read(const QJsonObject &json, const QList<Competitor *>competitors)
//{
//    m_name = json["name"].toString();
//    m_gender = genderFromString(json["gender"].toString());
//    m_weightType = weightTypeFromStr(json["weightType"].toString());
//    m_minAge = json["minAge"].toInt();
//    m_maxAge = json["maxAge"].toInt();
//    m_time = json["time"].toInt();
//    if(m_time == 0)     // Default to 3 min.
//        m_time = 3;
//    m_maxWeight = json["maxWeight"].toDouble();
//    m_chokesAllowed = json["chokesAllowed"].toBool();
//    m_armbarsAllowed = json["armbarsAllowed"].toBool();
//    m_matNumber = json["matNumber"].toInt();
//    m_firstPlace = json["firstPlace"].toInt();
//    m_secondPlace = json["secondPlace"].toInt();
//    m_thirdPlace_1 = json["thirdPlace1"].toInt();
//    m_thirdPlace_2 = json["thirdPlace2"].toInt();

//    QJsonArray bracketMembers = json["bracketMembers"].toArray();

//    for(int x = 0; x < bracketMembers.size(); x++)
//    {
//        int id = bracketMembers[x].toInt();
//        // Now, find the competitor with the specified id.
//        foreach(Competitor *competitor, competitors)
//        {
//            if(id == competitor->id())
//            {
//                addCompetitor(competitor);
//                break;
//            }
//        }

//    }
//}

//void Bracket::write(QJsonObject &json) const
//{
//    json["name"] = m_name;
//    json["gender"] = genderToString(m_gender);
//    json["weightType"] = weightTypeToStr(m_weightType);
//    json["minAge"] = m_minAge;
//    json["maxAge"] = m_maxAge;
//    json["time"] = m_time;
//    json["maxWeight"] = m_maxWeight;
//    json["chokesAllowed"] = m_chokesAllowed;
//    json["armbarsAllowed"] = m_armbarsAllowed;
//    json["matNumber"] = m_matNumber;
//    json["firstPlace"] = m_firstPlace;
//    json["secondPlace"] = m_secondPlace;
//    json["thirdPlace1"] = m_thirdPlace_1;
//    json["thirdPlace2"] = m_thirdPlace_2;

//    // Write out the list of competitor ids.
//    QJsonArray bracketMembers;
//    foreach(const Competitor* competitor, m_competitors)
//    {
//        QJsonValue id(competitor->id());

//        bracketMembers.append(id);
//    }

//    json["bracketMembers"] = bracketMembers;


//}

void writeBracketHeader(QTextStream &stream)
{
    stream << "BracketId,Name,Gender,WeightType,MinAge,MaxAge,MaxWeight,MatchLength,Chokes,Armbars,MatNumber,FirstPlace,SecondPlace,ThirdPlace" << endl;
}

//void Bracket::write(QTextStream &stream) const
//{

//    stream << "," << m_name;
//    stream << "," << genderToString(m_gender);
//    stream << "," << weightTypeToStr(m_weightType);
//    stream << "," << m_minAge;
//    stream << "," << m_maxAge;
//    stream << "," << m_maxWeight;
//    stream << "," << m_time;
//    stream << "," << m_chokesAllowed;
//    stream << "," << m_armbarsAllowed;
//    stream << "," << m_matNumber;
//    stream << "," << m_firstPlace;
//    stream << "," << m_secondPlace;
//    stream << "," << m_thirdPlace_1;
//    stream << endl;

//}

void writeBracketCompetitorHeader(QTextStream &stream)
{
    stream << "BracketId,CompetitorId" << endl;
}

//void Bracket::writeCompetitors(QTextStream &stream) const
//{
//    foreach(Competitor *competitor, m_competitors)
//    {
//        stream << "," << competitor->id() << endl;
//    }
//}

void writeBracketPlaceHeader(QTextStream &stream)
{
    stream << "BracketId,Place,CompetitorId" << endl;
}

//void Bracket::writePlaces(QTextStream &stream) const
//{
//    stream << "," << "1" << "," << m_firstPlace << endl;
//    stream << "," << "2" << "," << m_secondPlace << endl;
//    stream << "," << "3" << "," << m_thirdPlace_1 << endl;
//}

int Bracket::id() const
{
    return m_data->m_id;
}

void Bracket::setId(int id)
{
    m_data->m_id = id;
}

void Bracket::setName(QString name)
{
    m_data->m_name = name;
}

QString Bracket::name() const
{
    return m_data->m_name;
}

void Bracket::setGender(JM::Gender gender)
{
    m_data->m_gender = gender;
}

JM::Gender Bracket::gender() const
{
    return m_data->m_gender;
}

void Bracket::setWeightType(JM::WeightType weightType)
{
    m_data->m_weightType = weightType;
}

JM::WeightType Bracket::weightType() const
{
    return m_data->m_weightType;
}

void Bracket::setMinAge(int minAge)
{
    m_data->m_minAge = minAge;
}

int Bracket::minAge() const
{
    return m_data->m_minAge;
}

void Bracket::setMaxAge(int maxAge)
{
    m_data->m_maxAge = maxAge;
}

int Bracket::maxAge() const
{
    return m_data->m_maxAge;
}

int Bracket::time() const
{
    return m_data->m_time;
}

void Bracket::setTime(int time)
{
    m_data->m_time = time;
}

void Bracket::setMaxWeight(double maxWeight)
{
    m_data->m_maxWeight = maxWeight;
}

double Bracket::maxWeight() const
{
    return m_data->m_maxWeight;
}

void Bracket::setChokesAllowed(bool allowed)
{
    m_data->m_chokesAllowed = allowed;
}

bool Bracket::chokesAllowed() const
{
    return m_data->m_chokesAllowed;
}

void Bracket::setArmbarsAllowed(bool allowed)
{
    m_data->m_armbarsAllowed = allowed;
}

bool Bracket::armbarsAllowed() const
{
    return m_data->m_armbarsAllowed;
}

void Bracket::setMatNumber(int number)
{
    m_data->m_matNumber = number;
}

int Bracket::matNumber() const
{
    return m_data->m_matNumber;
}

void Bracket::setFirstPlace(const int firstPlace)
{
    m_data->m_firstPlace = firstPlace;
}

int Bracket::firstPlace() const
{
    return m_data->m_firstPlace;
}

void Bracket::setSecondPlace(const int place)
{
    m_data->m_secondPlace = place;
}

int Bracket::secondPlace() const
{
    return m_data->m_secondPlace;
}

void Bracket::setThirdPlace1(const int place)
{
    m_data->m_thirdPlace_1 = place;
}

int Bracket::thirdPlace1() const
{
    return m_data->m_thirdPlace_1;
}

void Bracket::setThirdPlace2(const int place)
{
    m_data->m_thirdPlace_2 = place;
}

int Bracket::thirdPlace2() const
{
    return m_data->m_thirdPlace_2;
}

bool Bracket::isValid()
{
    return m_data->m_id != -1;
}

/**
 * @brief Bracket::addCompetitor - Add a competitor to the bracket
 * @param id - The id of the competitor to add
 * @return
 */
bool Bracket::addCompetitor(int id)
{
    if(id < 0 || m_data->m_competitorIds.contains(id))
        return false;

   m_data->m_competitorIds.append(id);

   return true;
}

void Bracket::removeCompetitor(int id)
{
    int index = m_data->m_competitorIds.indexOf(id);
    if(index >= 0)
    {
        m_data->m_competitorIds.removeAt(index);
    }
}

//void Bracket::removeCompetitor(int index)
//{
//    if(index < 0 || index >= m_competitors.size())
//        return;

//    m_competitors.removeAt(index);
//}

//void Bracket::moveCompetitor(int srcRow, int destRow)
//{
//    m_competitors.move(srcRow, destRow);
//}

//bool Bracket::addCompetitor(int id, int location)
//{
//    bool ret = false;
//    if(m_competitorIds.indexOf(id) < 0)
//    {
//        if(location == -1 | location > m_competitorIds.size())
//        {
//            m_competitorIds.append(id);
//        }
//        else
//        {
//            m_competitorIds.insert(location, id);
//        }
//        ret = true;
//    }

//    return ret;
//}


const QList<int> Bracket::competitorIds() const
{
    return m_data->m_competitorIds;
}

void Bracket::setCompetitorIds(QList<int> ids)
{
    m_data->m_competitorIds = ids;
}

//int Bracket::numberOfMatches()
//{
//    // Round Robin Brackets
//    // 2 Competitors is 3 matches
//    // 3 Competitors is 3 matches
//    // 4 Competitors is 6 matches

//    // Modified Double Elimination Brackets
//    // 5 Competitors is 8 matches
//    // 6 Competitors is 9 matches
//    // 7 Competitors is 11 matches
//    // 8 Competitors is 13 matches

//    int numMatches = -1;
//    switch(competitors().size())
//    {
//        case 0:
//        case 1:
//            numMatches = 0;
//            break;
//        case 2:
//        case 3:
//            numMatches = 3;
//            break;
//        case 4:
//            numMatches = 6;
//            break;
//        case 5:
//            numMatches = 8;
//            break;
//        case 6:
//            numMatches = 9;
//            break;
//        case 7:
//            numMatches = 11;
//            break;
//        case 8:
//            numMatches = 13;
//            break;
//    }

//    return numMatches;
//}

bool Bracket::operator ==(const Bracket &src)
{
    return this->id() == src.id();
}

//Bracket &Bracket::operator =(const Bracket &src)
//{
//    this->m_data = new BracketData(src.m_data);

//    return *this;
//}

QString Bracket::weightTypeToStr(JM::WeightType type)
{

    switch(type)
    {
        case JM::Light:
            return LightStr;
            break;
        case JM::Medium:
            return MediumStr;
            break;
        case JM::Heavy:
            return HeavyStr;
            break;
        case JM::SuperHeavy:
            return SuperHeavyStr;
            break;
        case JM::IJF:
            return AbsoluteStr;
            break;

    default:
        return UnknownWeightType;
    }
}


JM::WeightType Bracket::weightTypeFromStr(QString typeStr)
{
    if(typeStr.compare(LightStr, Qt::CaseInsensitive) == 0)
        return JM::Light;
    if(typeStr.compare(MediumStr, Qt::CaseInsensitive) == 0)
        return JM::Medium;
    if(typeStr.compare(HeavyStr, Qt::CaseInsensitive) == 0)
        return JM::Heavy;
    if(typeStr.compare(SuperHeavyStr, Qt::CaseInsensitive) == 0)
        return JM::SuperHeavy;
    if(typeStr.compare(AbsoluteStr, Qt::CaseInsensitive) == 0)
        return JM::IJF;

    qDebug() << "WARNING!!! Unknown Weight Type Specified: [" << typeStr << "]";

    return JM::Light;
}
