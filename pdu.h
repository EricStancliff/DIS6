#pragma once

#include "dis6_global.h"

#include "datastream.h"
#include "header.h"

namespace DIS6
{

class DIS6_EXPORT Pdu
{
public:
    Pdu();
    virtual ~Pdu();

    //these functions will write to your data vector

    //Take data from Pdu and put into ByteArray
    virtual void pack(DataStream& data) const;

    //Take data from ByteArray and put into Pdu
    virtual void unpack(DataStream& data);

    virtual Header& header();
    virtual void setHeader(const Header& header);

protected:
    DataStream m_data;
    Header m_header;
};

}
