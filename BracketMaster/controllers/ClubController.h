#pragma once

#include "BaseController.h"
#include <QObject>

class Club;

/**
 * @brief Manages clubs
 */
class ClubController : public BaseController
{
    Q_OBJECT
public:
    explicit ClubController(QObject *parent = 0);

    Club createClub();

    void updateClub(Club& club);
    void removeClub(int clubId);
    const QList<Club> clubs() const;

    Club findClubByName(QString name);

    // BaseController interface
    void add(int parentId) override;
    int size() const /*override*/;
    int size(int id) const /*override*/;
    void remove(int id);
    void removeIndex(int index);
    int indexOf(int id);
    virtual Club find(int id) const;
    virtual const QList<Competitor> competitors(int parentId = -1) const override;

signals:
    void clubAdded(Club* club);
    void clubUpdated(Club* club);
    void clubRemoved(Club* club);

public slots:

private:
//    Club* findClub(int id);

};

