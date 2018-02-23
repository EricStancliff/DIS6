#include "header.h"

#include "datastream.h"

#define DIS6_1998_VERSION 6

//TODO - Build the header
namespace DIS6
{

Header::Header() : m_version(0),
    m_exercise(0),
    m_type(0),
    m_family(0),
    m_timestamp(0),
    m_length(0),
    m_padding(0)
{
    //m_version = DIS6_1998_VERSION;
}

Header::~Header()
{

}

Header::Header(const Header& header)
{
    m_version = header.version();
    m_exercise = header.exercise();
    m_type = header.type();
    m_family = header.family();
    m_timestamp = header.timestamp();  //this might be wrong.
    m_length = header.length();
    m_padding = header.padding();
}

void Header::pack(DataStream& data) const
{
    data.append(m_version);
    data.append(m_exercise);
    data.append(m_type);
    data.append(m_family);
    data.append(m_timestamp);
    data.append(m_length);
    data.append(m_padding);
}

void Header::unpack(DataStream& data)
{
    data.read(m_version);
    data.read(m_exercise);
    data.read(m_type);
    data.read(m_family);
    data.read(m_timestamp);
    data.read(m_length);
    data.read(m_padding);
}

uint8_t Header::version() const
{
    return m_version;
}

void Header::setVersion(const uint8_t &version)
{
    m_version = version;
}

uint8_t Header::exercise() const
{
    return m_exercise;
}

void Header::setExercise(const uint8_t &exercise)
{
    m_exercise = exercise;
}

uint8_t Header::type() const
{
    return m_type;
}

void Header::setType(const uint8_t &type)
{
    m_type = type;
}

uint8_t Header::family() const
{
    return m_family;
}

void Header::setFamily(const uint8_t &family)
{
    m_family = family;
}

uint32_t Header::timestamp() const
{
    return m_timestamp;
}

void Header::setTimestamp(const uint32_t &timestamp)
{
    m_timestamp = timestamp;
}

uint16_t Header::length() const
{
    return m_length;
}

void Header::setLength(const uint16_t &length)
{
    m_length = length;
}

uint16_t Header::padding() const
{
    return m_padding;
}

void Header::setPadding(const uint16_t &padding)
{
    m_padding = padding;
}

}
