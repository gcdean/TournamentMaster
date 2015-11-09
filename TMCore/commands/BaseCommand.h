#pragma once

#include <QObject>

class BaseCommand : public QObject
{
    Q_OBJECT

public:
    BaseCommand(QObject* parent = 0);
    ~BaseCommand();

signals:
    void commandComplete(); // Emitted whenenver the command is done, regardless of the result
    void commandSuccessful();    // Emitted when the command is successful
    void commandFailed();       // Emitted when command fails.
public slots:
    virtual bool run() = 0;

protected:
    bool done(bool success);

};

