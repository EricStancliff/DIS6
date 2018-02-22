#include "pdu.h"

namespace DIS6
{

Pdu::Pdu()
{

}

Pdu::~Pdu()
{

}

void Pdu::pack(DataStream& data) const
{
    m_header.pack(data);
}

void Pdu::unpack(DataStream& data)
{
    m_header.unpack(data);
}

Header& Pdu::header()
{
    return m_header;
}

void Pdu::setHeader(const Header& header)
{
    m_header = header;
}

}
