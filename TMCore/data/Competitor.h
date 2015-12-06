#pragma once

#include "TMCore.h"

#include <QSharedDataPointer>


#include "data/CompetitorData.h"
#include "JMUtil.h"

namespace competitor
{
    enum CompetitorProperties
    {
        FirstName,
        LastName,
        Gender,
        Age,
        Weight,
        Rank,
        NumDivs,
        Notes,
        MAX_COMPETITOR_ITEM
    };

}

void writeCompetitorHeader(QTextStream &stream);

class CompetitorData;

class TMCORE_DLLSPEC Competitor
{

public:

    Competitor();
    Competitor(int id);
    Competitor(const Competitor& src);
    virtual ~Competitor();

    int id() const;
    void setId(int id);
    QString firstName() const;
    void setFirstName(QString name);
    QString lastName() const;
    void setLastName(QString name);
    JM::Gender gender() const;
    void setGender(JM::Gender gender);
    int age() const;
    void setAge(int age);
    double weight() const;
    void setWeight(double weight);
    JM::Rank rank() const;
    void setRank(JM::Rank rank);
    int clubId() const;
    void setClubId(int id);
    int numBrackets() const;
    void setNumBrackets(int num);
    QString notes() const;
    void setNotes(QString notes);

    bool isValid() const;
    virtual bool operator == (const Competitor& src);


private:
    QSharedDataPointer<CompetitorData> m_data;

};


