#pragma once

#include <QObject>

class Competitor;
class CompetitorFilter;
class Tournament;
class JMDataObj;

class BaseController : public QObject
{
    Q_OBJECT
public:
    explicit BaseController(QObject *parent = 0);
//    void setTournament(std::unique_ptr<Tournament> &tournament);

    virtual int size() const;    // Size of all elements in the list
    virtual int size(int id) const;  // Size of all elements with given id or parent with id.

    virtual void add(int parentId); // Creates and adds a new object to the model
    virtual void remove(int id);    // Remove the object with the specified id
    virtual void removeIndex(int index);    // Remove item at given index.
    virtual int indexOf(int id);


    virtual const QList<Competitor > competitors(int parentId = -1) const;
    virtual const QList<Competitor> competitors(const CompetitorFilter& filter, int parentId = -1) const;

signals:
    void addedDataObj(JMDataObj *obj);
    void removedDataObj(JMDataObj *obj);

public slots:

protected:
    const Tournament tournament() const;

private:
    Tournament* m_tournament;
};

