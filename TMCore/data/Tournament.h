#pragma once

#include "TMCore.h"
#include "TournamentData.h"

//#include <QDate>
//#include <QJsonObject>
//#include <QList>
//#include <QObject>
//#include <QString>
//#include <QTime>

//#include "JMDataObj.h"

//class Bracket;
//class Club;
//class Competitor;
//class Match;

//class Bracket;

class Tournament
{
public:
    explicit Tournament(int id = -1);
    Tournament(const Tournament& src);

//    void updateTournament(const Tournament &src);

    int id() const;
    void setId(int id);
    QString name() const;
    void setName(QString name);
    QDate date() const;
    void setDate(QDate date);
    QTime startTime() const;
    void setStartTime(QTime startTime);
    bool useTexasMatchCards() const;
    void setTexasMatchCards(bool use);

//    QList<Club *>& clubs() {return m_clubs;}
//    QList<Competitor *>& competitors() {return m_competitors;}
//    QList<Bracket *>& brackets() {return m_brackets;}
//    QList<Match *>& matches() {return m_matches;}

//    void read(QJsonObject &json);
//    void write(QJsonObject& json) const;
//    //void write(QTextStream &stream) const;
//    void write (QString dirname) const;

//    Tournament& operator =(const Tournament& src);
    bool operator ==(const Tournament& src);

private:
    QSharedDataPointer<TournamentData> m_data;

};

