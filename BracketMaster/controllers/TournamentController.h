#pragma once

#include "BaseController.h"

class TournamentController : public BaseController
{
public:
    TournamentController();
    ~TournamentController();

    // BaseController interface
public:
    void add(int parentId) override;
    void remove(int id) override;
    void removeIndex(int index) override;
    JMDataObj *find(int id) const override;
    int indexOf(int id) override;

protected:
    int findNextId();
};

