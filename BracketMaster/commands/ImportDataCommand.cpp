#include "ImportDataCommand.h"

#include "data/Club.h"
#include "data/Competitor.h"
#include "JMUtil.h"
#include "JudoMasterApplication.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

ImportDataCommand::ImportDataCommand(QObject *parent)
    : BaseCommand(parent)
    , m_importedCompetitors()
    , m_skippedCompetitors()
{
}

ImportDataCommand::~ImportDataCommand()
{
    m_skippedCompetitors.clear();
    m_importedCompetitors.clear();
}

const QList<Competitor> ImportDataCommand::importedCompetitors() const
{
    return m_importedCompetitors;
}

const QList<Competitor> ImportDataCommand::skippedCompetitors() const
{
    return m_skippedCompetitors;
}


bool ImportDataCommand::run(IDocument *const doc)
{
    QString openFileName = QFileDialog::getOpenFileName(dynamic_cast<QWidget *>(parent()), "Import CSV File", JMApp()->lastSaveDir().absolutePath(), "CSV Files (*.csv)");

    if(openFileName.isEmpty())
    {
        return done(false);
    }

    QFile file(openFileName);

    if(file.open(QFile::ReadOnly))
    {
        QTextStream fileStream(&file);
        QString line = fileStream.readLine();
        QStringList headers = line.split(',');

//        qDebug() << "Printing CSV Headers";
        QHash<QString, int> colMap;
        int index = 0;
        foreach(QString header, headers)
        {
            colMap[header] = index;
//            qDebug() << "Column: " << header << " Has index " << index;
            index++;
        }

        do
        {
            line = fileStream.readLine();
            if(!line.isNull())
            {
                // TODO - Need to store column names in a user configurable table.

                QStringList columns = line.split(',');
                QString lname = columns.at(colMap["Last Name"]);
                QString fname = columns.at(colMap["First Name"]);
                QString gender = columns.at(colMap["Gender"]);
                QString age = columns.at(colMap["Age"]);
                QString weight = columns.at(colMap["Weight (Lbs)"]);
                QString belt = columns.at(colMap["Rank"]);
                QString clubName = columns.at(colMap["Club Name"]);
                QString div0 = colMap.contains("Division") ? columns.at(colMap["Division"]) : "";
                QString div1 = colMap.contains("Division 1") ? columns.at(colMap["Division 1"]) : "";
                QString div2 = colMap.contains("Division 2") ? columns.at(colMap["Division 2"]) : "";
                QString div3 = colMap.contains("Division 3") ? columns.at(colMap["Division 3"]) : "";
                QString kata = colMap.contains("Kata") ? columns.at(colMap["Kata"]) : "";

                int numDivs = 0;

                numDivs += div0.isEmpty() ? 0 : 1;
                numDivs += div1.isEmpty() ? 0 : 1;
                numDivs += div2.isEmpty() ? 0 : 1;
                numDivs += div3.isEmpty() ? 0 : 1;

                QString notes = QString("div0: (%1), div1: (%2), div2: (%3), div3: (%4)").arg(div0).arg(div1).arg(div2).arg(div3);
                if(!kata.isEmpty())
                {
                    notes.append(QString(" Kata: %1").arg(kata));
                }
//                qDebug() << "First: " << fname << ", Last: " << lname << ", Gender: " << gender << ", Age: " << age << ", Weight: " << weight
//                         << ", belt: " << belt << ", club: " << clubName << ", num Divs: " << numDivs;

                // Let's find the club.
                Club club = JMApp()->clubController()->findClubByName(clubName);
                if(!club.isValid())
                {
  //                  qDebug() << "Creating New Club for name " << clubName;
                    club = JMApp()->clubController()->createClub();
                    club.setClubName(clubName);
                    JMApp()->clubController()->updateClub(club);
                }

                // Now add the competitor.
                JM::Rank rank = rankFromString(belt);
                if(rank == JM::Unknown)
                {
                    notes += QString("belt: %1").arg(belt);
                }
                auto mf = genderFromString(gender);

                // See if the competitor is already added (from previous import)
                Competitor competitor = JMApp()->competitorController()->findByName(fname, lname);

                if(!competitor.isValid())
                {
                    // Competitor not found, so add.
                    competitor = JMApp()->competitorController()->createCompetitor(fname,lname, mf, age.toInt(), weight.toDouble(), rank, club.id(), numDivs, notes);

                    m_importedCompetitors.append(competitor);
                }
                else
                {
                    m_skippedCompetitors.append(competitor);
                }
            }
        } while (!line.isNull());
        file.close();
    }
    else
    {
        return done(false);
    }

    // Compare the # imported with the total # we have.
    int total = JMApp()->competitorController()->competitors().size();
    int numImported = m_importedCompetitors.size();
    qDebug() << "Total Competitors: " << total << ", Total Imported: " << numImported;

    return done(true);
}
