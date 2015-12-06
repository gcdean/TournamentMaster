#pragma once

#include "TMCore.h"
#include "BracketData.h"
#include "JMUtil.h"


#include <QList>
#include <QSharedData>

class BracketData;
class Competitor;

void writeBracketHeader(QTextStream &stream);
void writeBracketCompetitorHeader(QTextStream &stream);
void writeBracketPlaceHeader(QTextStream &stream);


/**
 * @brief The Bracket class
 *
 * Brackets are either age and weight based or simply weight based. Additionally,
 * weight brackets can be absolule weight or a weight type (Light, Medium, Heavy)
 */
class TMCORE_DLLSPEC Bracket
{
public:
    Bracket();
    Bracket(int id);
    Bracket(const Bracket& src);
    virtual ~Bracket();


//    void read(const QJsonObject &json ) override;
//    void read(const QJsonObject& json, const QList<Competitor *> competitors);

//    void write(QJsonObject& json) const override;
//    void write(QTextStream &stream) const override;
//    void writeCompetitors(QTextStream &stream) const;
//    void writePlaces(QTextStream &stream) const;

    int id() const;
    void setId(int id);
    void setName(QString name);
    QString name() const;
    void setGender(JM::Gender gender);
    JM::Gender gender() const;
    void setWeightType(JM::WeightType weightType);
    JM::WeightType weightType() const;
    void setMinAge(int minAge);
    int minAge() const;
    void setMaxAge(int maxAge);
    int maxAge() const;
    int time() const;
    void setTime(int time);
    void setMaxWeight(double maxWeight);
    double maxWeight() const;
    void setChokesAllowed(bool allowed);
    bool chokesAllowed() const;
    void setArmbarsAllowed(bool allowed);
    bool armbarsAllowed() const;
    void setMatNumber(int number);
    int matNumber() const;
    void setFirstPlace(const int firstPlace);
    int firstPlace() const;
    void setSecondPlace(const int place);
    int secondPlace() const;
    void setThirdPlace1(const int place);
    int thirdPlace1() const;
    void setThirdPlace2(const int place);
    int thirdPlace2() const;

    bool isValid();

    bool addCompetitor(int id);
    void removeCompetitor(int id);

//    bool addCompetitor(int id, int location = -1);
    const QList<int> competitorIds() const;

//    int numberOfMatches();

    // Operator methods
    bool operator ==(const Bracket& src);
//    Bracket &operator =(const Bracket& src);

    static QString weightTypeToStr(JM::WeightType type);
    static JM::WeightType weightTypeFromStr(QString typeStr);

private:
    QSharedDataPointer<BracketData> m_data;

};

namespace bracket
{
    QString weightTypeToStr(JM::WeightType type);
    JM::WeightType weightTypeFromStr(QString typeStr);
}

