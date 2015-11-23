#pragma once

#include "TMCore.h"

class TMCORE_DLLSPEC TMBaseData
{
public:
    TMBaseData();
    TMBaseData(int id);
    TMBaseData(const TMBaseData& src);
    TMBaseData(const QJsonObject& json);
    virtual ~TMBaseData();

    int id() const;

    virtual bool operator ==(const TMBaseData& src);
    virtual TMBaseData& operator =(const TMBaseData& src);

    bool isValid();

protected:
    void setId(int id);

private:
    int m_id;   // Unique id of the data object.

};


