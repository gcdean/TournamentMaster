#pragma once


class BaseCommand
{
public:
    BaseCommand();
    ~BaseCommand();

    virtual bool run() = 0;
};

