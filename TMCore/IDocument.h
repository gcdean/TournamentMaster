#pragma once

#include "data/Bracket.h"
#include "data/Club.h"
#include "data/Competitor.h"
#include "data/Match.h"
#include "data/Tournament.h"
#include "TMCore.h"


class TMCORE_DLLSPEC IDocument
{
public:

    // NOTE - Maybe all add methods should return the object, in case it's changed during the add.

    // Tournament methods
    virtual const Tournament& tournament() const = 0;
    virtual void updateTournament(const Tournament& tournament) = 0;

    // Club methods
    virtual const QList<Club> clubs() = 0;
    virtual const Club club(int id) const = 0;
    virtual bool addClub(Club club) = 0;
    virtual Club addClub() = 0;
    virtual bool removeClub(int id) = 0;
    virtual bool updateClub(const Club& src) = 0;

    // Competitor methods
    virtual const QList<Competitor> competitors() const = 0;
    virtual const Competitor competitor(int id) const = 0;
    virtual bool addCompetitor(Competitor competitor) = 0;
    virtual Competitor addCompetitor() = 0;
    virtual bool removeCompetitor(int id) = 0;
    virtual bool updateCompetitor(const Competitor& src) = 0;

    // Bracket methods
    virtual const QList<Bracket> brackets() const = 0;
    virtual const Bracket& bracket(int id) = 0;
    virtual const QList<Competitor> bracketCompetitors(int bracketId) = 0;
    virtual Bracket addBracket(Bracket bracket) = 0;
    virtual bool removeBracket(int id) = 0;
    virtual bool updateBracket(const Bracket& src) = 0;

    // Match methods
    virtual const QList<Match> matches(int bracketid) const = 0;
    virtual const Match match(int id) = 0;
    virtual bool addMatch(int bracketId, Match& match) = 0;
    virtual Match addMatch(int bracketId) = 0;
    virtual bool removeMatch(int id) = 0;
    virtual bool updateMatch(const Match& src) = 0;

    // Read/write methods
    virtual QString name() = 0;
    virtual bool load(QString filename) = 0;
    virtual bool save() = 0;
    virtual bool save(QString filename) = 0;

    virtual bool isModified() = 0;

};

