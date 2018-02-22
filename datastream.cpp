#include "datastream.h"

#define DIS6_DEFAULT_BYTE_ORDER BigEndian

namespace DIS6
{

DataStream::DataStream() : m_errorState(false)
{
    m_endian = DIS6_DEFAULT_BYTE_ORDER;
}

DataStream::~DataStream()
{

}

DataStream::DataStream(const DataStream& copy)
{
    m_data = copy.data();
    m_endian = copy.endian();
    m_errorState = copy.errorState();
    m_error = copy.error();
}

Endian DataStream::endian() const
{
    return m_endian;
}

void DataStream::setEndian(const Endian &endian)
{
    m_endian = endian;
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
