#pragma once

#include <QObject>
#include <QString>

class Club;

namespace JM
{

/**
 * @brief The Rank enum - Used for Competitor's rank
 */
enum Rank
{
    White,
    Yellow,
    Orange,
    Green,
    Blue,
    Purple,
    Brown,
    Black,
    Unknown
};


/**
 * @brief The Gender enum - Used for both competiors and brackets.
 */
enum Gender
{
    Female,
    Male,
    NotApplicable
};

enum WeightType
{
    Light,
    Medium,
    Heavy,
    SuperHeavy,
    IJF
};



}

Q_DECLARE_METATYPE(JM::Rank)
Q_DECLARE_METATYPE(JM::Gender)
Q_DECLARE_METATYPE(JM::WeightType)

QString rankToString(JM::Rank rank);
JM::Rank rankFromString(QString rankStr);

QString genderToString(JM::Gender gender);
JM::Gender genderFromString(QString genderStr);

QString prepareStringForCSV(QString str);

bool compareClubNames(Club* club1, Club* club2);
