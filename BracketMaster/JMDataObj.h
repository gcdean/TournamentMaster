#pragma once

#include <QTextStream>

#include "data/TMBaseData.h"

class QJsonObject;

/**
 * @brief Base class for data objects
 */
class JMDataObj : public TMBaseData
{
public:
    JMDataObj(int id);
    JMDataObj(const JMDataObj& src);
    JMDataObj(const QJsonObject& json);
    virtual ~JMDataObj() = default;

//    int id() const;

    virtual bool operator ==(const JMDataObj& src);
    JMDataObj& operator =(const JMDataObj& src);

    virtual void read(const QJsonObject &json);
    virtual void write(QJsonObject &json) const;
    virtual void write(QTextStream &stream) const;

//private:
//    int m_id;   // Unique id of the data object.
};

