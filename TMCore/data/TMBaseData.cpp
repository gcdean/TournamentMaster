#include "TMBaseData.h"

TMBaseData::TMBaseData()
    : m_id(-1)
{
}

TMBaseData::TMBaseData(int id)
    : m_id(id)
{

}

TMBaseData::TMBaseData(const TMBaseData &src)
{
    m_id = src.id();
}

TMBaseData::~TMBaseData()
{

}

int TMBaseData::id() const
{
    return m_id;
}

void TMBaseData::setId(int id)
{
    m_id = id;
}

bool TMBaseData::operator ==(const TMBaseData &src)
{
    return src.id() == id();
}

TMBaseData &TMBaseData::operator =(const TMBaseData &src)
{
    m_id = src.id();
    return *this;
}
