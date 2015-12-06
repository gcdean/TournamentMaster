#include "Club.h"

#include "ClubData.h"

#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QString>

Club::Club()
{
    m_data = new ClubData;
}

Club::Club(int id)
{
    m_data = new ClubData;
    setId(id);
}

Club::Club(int id, QString clubName, QString coachName, QString addr1, QString addr2, QString country, QString city, QString state, QString zip)
{
    m_data = new ClubData;
    setId(id);
    setClubName(clubName);
    setCoachName(coachName);
    setAddress1(addr1);
    setAddress2(addr2);
    setCountry(country);
    setCity(city);
    setState(state);
    setZip(zip);
}

/*
 * Copy Constructor
 */
Club::Club(const Club &src)
    : m_data(src.m_data)
{
}

Club::~Club()
{

}

int Club::id() const
{
    return m_data->m_id;
}

void Club::setId(int id)
{
    m_data->m_id = id;
}

QString Club::clubName() const {return m_data->m_clubName;}

void Club::setClubName(QString name) {m_data->m_clubName = name;}

QString Club::coachName() const {return m_data->m_coachName;}

void Club::setCoachName(QString name) {m_data->m_coachName = name;}

QString Club::address1() const {return m_data->m_address1;}

void Club::setAddress1(QString address1) {m_data->m_address1 = address1;}

QString Club::address2() const {return m_data->m_address2;}

void Club::setAddress2(QString address2) {m_data->m_address2 = address2;}

QString Club::country() const {return m_data->m_country;}

void Club::setCountry(QString country) {m_data->m_country = country;}

QString Club::city() const {return m_data->m_city;}

void Club::setCity(QString city) {m_data->m_city = city;}

QString Club::state() const {return m_data->m_state;}

void Club::setState(QString state) {m_data->m_state = state;}

QString Club::zip() const {return m_data->m_zip;}

void Club::setZip(QString zip) {m_data->m_zip = zip;}

bool Club::isValid()
{
    return m_data->m_id != -1;
}

bool Club::operator ==(const Club &src)
{
    return this->id() == src.id();
}


//void writeClubHeader(QTextStream &stream)
//{
//    stream << "ClubId,ClubName,CoachName,Address1,Address2,City,State,Zip,Country" << endl;
//}

//void Club::write(QTextStream &stream) const
//{
//    stream << "," << m_clubName;
//    stream << "," << m_coachName;
//    stream << "," << m_address1;
//    stream << "," << m_address2;
//    stream << "," << m_city;
//    stream << "," << m_state;
//    stream << "," << m_zip;
//    stream << "," << m_country;

//    stream << endl;
//}
