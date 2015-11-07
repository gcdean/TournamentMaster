#include "JMDataObj.h"

#include <QJsonObject>
#include <QTextStream>

JMDataObj::JMDataObj(int id)
//    : m_id(id)
    : TMBaseData (id)
{
}

JMDataObj::JMDataObj(const JMDataObj& src)
    : TMBaseData(src)
{
//    m_id = src.id();
}

JMDataObj::JMDataObj(const QJsonObject &json)
{
    read(json);
}

//int JMDataObj::id() const
//{
//    return m_id;
//}

bool JMDataObj::operator ==(const JMDataObj &src)
{
    return TMBaseData::operator ==(src);
}

JMDataObj &JMDataObj::operator =(const JMDataObj &src)
{
    TMBaseData::operator =(src);
 //   m_id = src.id();
    return *this;
}



void JMDataObj::read(const QJsonObject &json)
{
    setId(json["id"].toInt());
//    m_id = json["id"].toInt();
}

void JMDataObj::write(QJsonObject &json) const
{
    json["id"] = id();
}

void JMDataObj::write(QTextStream &stream) const
{
    stream << id();
}
