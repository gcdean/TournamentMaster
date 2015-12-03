#pragma once

#include "TMCore.h"
#include "ClubData.h"
#include <QSharedData>

//void writeClubHeader(QTextStream &stream);

class ClubData;

/**
 * @brief Represents all the data for a Judo club
 */
class TMCORE_DLLSPEC Club
{

public:
    Club(); // Not sure if we need this
    Club(int id);
    explicit Club(int id, QString clubName, QString coachName, QString addr1 = QString(), QString addr2 = QString(), QString country = QString(), QString city = QString(), QString state = QString(), QString zip = QString());
    Club(const Club& src);
    virtual ~Club();

    int id() const;
    void setId(int id);
    QString clubName() const;
    void setClubName(QString name);
    QString coachName() const;
    void setCoachName(QString name);
    QString address1() const;
    void setAddress1(QString address1);
    QString address2() const;
    void setAddress2(QString address2);
    QString country() const;
    void setCountry(QString country);
    QString city() const;
    void setCity(QString city);
    QString state() const;
    void setState(QString state);
    QString zip() const;
    void setZip(QString zip);

    bool isValid();

    virtual bool operator == (const Club& src);

private:
    QSharedDataPointer<ClubData> m_data;


};

