#pragma once

//This Object represents a DIS v6 header

#include <cstdint>

namespace DIS6
{

class DataStream;

class Header
{
public:
    Header();
    virtual ~Header();
    Header(const Header& header);

    //Take data from Header and put into ByteArray
    virtual void pack(DataStream& data) const;

    //Take data from ByteArray and put into Header
    virtual void unpack(DataStream& data);

    uint8_t version() const;
    void setVersion(const uint8_t &version);

    uint8_t exercise() const;
    void setExercise(const uint8_t &exercise);

    uint8_t type() const;
    void setType(const uint8_t &type);

    uint8_t family() const;
    void setFamily(const uint8_t &family);

    uint32_t timestamp() const;
    void setTimestamp(const uint32_t &timestamp);

    uint16_t length() const;
    void setLength(const uint16_t &length);

    uint16_t padding() const;
    void setPadding(const uint16_t &padding);

protected:

    uint8_t m_version;  //defaults to DIS6
    uint8_t m_exercise;
    uint8_t m_type;
    uint8_t m_family;
    uint32_t m_timestamp;
    uint16_t m_length;
    uint16_t m_padding;

};

}
