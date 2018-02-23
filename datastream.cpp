#include "datastream.h"

#include <iterator>

#define DIS6_DEFAULT_BYTE_ORDER BigEndian

namespace DIS6
{

DataStream::DataStream() : m_errorState(false)
{
    m_byteOrder = DIS6_DEFAULT_BYTE_ORDER;
    m_pos = m_data.begin();
}

DataStream::DataStream(const std::vector<unsigned char>& data)
{
    m_data = data;
}

DataStream::DataStream(unsigned char* data, size_t size)
{
    for(size_t pos = 0; pos < size; ++pos)
    {
        m_data.push_back((*data));
        ++data;
    }
}

DataStream::DataStream(const DataStream& copy)
{
    m_data = copy.data();
    m_byteOrder = copy.byteOrder();
    m_errorState = copy.errorState();
    m_error = copy.error();
    setPosition(copy.position());
}

DataStream::~DataStream()
{

}

void DataStream::setData(const std::vector<unsigned char>& data)
{
    m_data = data;
    resetPosition();
}

void DataStream::setData(unsigned char* data, size_t size)
{
    for(size_t pos = 0; pos < size; ++pos)
    {
        m_data.push_back((*data));
        ++data;
    }
    resetPosition();
}

void DataStream::resetPosition()
{
    m_pos = m_data.begin();
}

bool DataStream::setPosition(size_t pos)
{
    if(pos >= m_data.size())
    {
        //error
        return false;
    }
    m_pos = m_data.begin() + pos;
    return true;
}

size_t DataStream::position() const
{
    return std::distance(m_data.begin(), (std::vector<unsigned char>::const_iterator)m_pos);
}

ByteOrder DataStream::byteOrder() const
{
    return m_byteOrder;
}

void DataStream::setByteOrder(const ByteOrder &byteOrder)
{
    m_byteOrder = byteOrder;
}

bool DataStream::errorState() const
{
    return m_errorState;
}

std::string DataStream::error() const
{
    return m_error;
}

size_t DataStream::size() const
{
    return m_data.size();
}

std::vector<unsigned char> DataStream::data() const
{
    return m_data;
}

}
