#include "Competitor.h"
#include "CompetitorData.h"
#include "JMUtil.h"

Competitor::Competitor()
{
    m_data = new CompetitorData;
}

Competitor::Competitor(int id)
{
    m_data = new CompetitorData;
    m_data->m_id = id;
}

Competitor::Competitor(const Competitor &src)
    : m_data(src.m_data)
{
}

Competitor::~Competitor()
{

}

int Competitor::id() const
{
    return m_data->m_id;
}

void Competitor::setId(int id)
{
    m_data->m_id = id;
}


QString Competitor::firstName() const
{
    return m_data->m_firstName;
}

void Competitor::setFirstName(QString name)
{
    m_data->m_firstName = name;
}

QString Competitor::lastName() const
{
    return m_data->m_lastName;
}

void Competitor::setLastName(QString name) {m_data->m_lastName = name;}

JM::Gender Competitor::gender() const {return m_data->m_gender;}

void Competitor::setGender(JM::Gender gender) {m_data->m_gender = gender;}

int Competitor::age() const {return m_data->m_age;}

void Competitor::setAge(int age) {m_data->m_age = age;}

double Competitor::weight() const {return m_data->m_weight;}

void Competitor::setWeight(double weight) {m_data->m_weight = weight;}

JM::Rank Competitor::rank() const {return m_data->m_rank;}

void Competitor::setRank(JM::Rank rank) {m_data->m_rank = rank;}

int Competitor::clubId() const {return m_data->m_clubId;}

void Competitor::setClubId(int id) {m_data->m_clubId = id;}

int Competitor::numBrackets() const {return m_data->m_numBrackets;}

void Competitor::setNumBrackets(int num) {m_data->m_numBrackets = num;}

QString Competitor::notes() const { return m_data->m_notes;}

void Competitor::setNotes(QString notes) {m_data->m_notes = notes;}

bool Competitor::isValid() const
{
    return m_data->m_id != -1;
}

bool Competitor::operator ==(const Competitor &src)
{
    return id() == src.id();
}

//Competitor &Competitor::operator =(const Competitor &src)
//{

//    setFirstName(src.firstName());
//    setLastName(src.lastName());
//    setGender(src.gender());
//    setAge(src.age());
//    setWeight(src.weight());
//    setRank(src.rank());
//    setClubId(src.clubId());
//    setNumBrackets(src.numBrackets());
//    setNotes(src.notes());

//    return *this;

//}

//void Competitor::read(const QJsonObject &json)
//{

//    m_firstName = json["fname"].toString();
//    m_lastName = json["lname"].toString();
//    m_gender = genderFromString(json["gender"].toString());
//    m_age = json["age"].toInt();
//    m_weight = json["weight"].toDouble();

//    m_rank = rankFromString(json["rank"].toString());
//    m_numBrackets = json["numBrackets"].toInt();
//    m_notes = json["notes"].toString();

//    m_clubId = json["clubid"].toInt();

//}

//void Competitor::write(QJsonObject &json) const
//{
//    json["fname"] = m_firstName;
//    json["lname"] = m_lastName;
//    json["gender"] = genderToString(m_gender);
//    json["age"] = m_age;
//    json["weight"] = m_weight;

//    json["rank"] = rankToString(m_rank);
//    json["numBrackets"] = m_numBrackets;
//    json["notes"] = m_notes;
//    json["clubid"] = m_clubId;

//}

void writeCompetitorHeader(QTextStream &stream)
{
    stream << "CompetitorId,FirstName,LastName,Gender,Age,Weight,Rank,NumBrackets,ClubId,Notes" << endl;
}

//void Competitor::write(QTextStream &stream) const
//{

//    stream << "," << m_firstName;
//    stream << "," << m_lastName;
//    stream << "," << genderToString(m_gender);
//    stream << "," << m_age;
//    stream << "," << m_weight;
//    stream << "," << rankToString(m_rank);
//    stream << "," << m_numBrackets;
//    stream << "," << m_clubId;

//    QString tmp(m_notes);
//    stream << "," << prepareStringForCSV(tmp);
//    stream << endl;
//}
