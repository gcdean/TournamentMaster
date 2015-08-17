#pragma once

#include <QObject>

class BaseCommand : public QObject
{
    Q_OBJECT

public:
    BaseCommand(QObject* parent = 0);
    ~BaseCommand();

public slots:
    virtual bool run() = 0;

};

