#pragma once

#include <sstream>
#include <climits>
#include <vector>
#include <assert.h>
#include <type_traits>
#include <cstdarg>

#ifdef __GNUC__
#include <byteswap.h>
#endif

#ifdef MSVC
#include <stdlib.h>
#endif

#include "dis6_global.h"

namespace DIS6
{

enum ByteOrder {
    BigEndian,
    LittleEndian
};

constexpr ByteOrder systemByteOrder()
{
    union {
        uint16_t shortData;
        uint8_t byteData;
    } num {1};
    return num.byteData ? LittleEndian : BigEndian;
}

class DIS6_EXPORT DataStream
{
public:
    DataStream();
    DataStream(const std::vector<unsigned char>& data);
    DataStream(unsigned char* data, size_t size);
    ~DataStream();

    void resetPosition();
    bool setPosition(size_t pos);
    size_t position() const;

    size_t size() const;
    std::vector<unsigned char> data() const;
    void setData(const std::vector<unsigned char>& data);
    void setData(unsigned char* data, size_t size);

    template <typename T, std::enable_if_t<std::is_arithmetic<T>::value>* = nullptr>
    bool append(const T& data)
    {
        auto copyData = data;
        swapByteOrder(copyData);
        writeData(copyData);
        return m_errorState;
    }

    template <typename T, std::enable_if_t<std::is_arithmetic<T>::value>* = nullptr>
    bool read(T& data)
    {
        readData(data);
        swapByteOrder(data);
        return m_errorState;
    }

    template <typename T, std::enable_if_t<std::is_arithmetic<T>::value>* = nullptr>
    bool operator<<(const T& data)
    {
        auto copyData = data;
        swapByteOrder(copyData);
        writeData(copyData);
        return m_errorState;
    }

    template <typename T, std::enable_if_t<std::is_arithmetic<T>::value>* = nullptr>
    bool operator>>(T& data)
    {
        readData(data);
        swapByteOrder(data);
        return m_errorState;
    }

    //for custom implementations
    //req:  Custom types must impelement << and >> operators with RHS being DataStream
    //, LHS being T, and return type being bool
    //example: bool operator>>(const EntityId& lhs, DataStream& rhs);
    template <typename T>
    auto append(const T& data) -> decltype(data >> *this)
    {
        return data >> *this;
    }

    template <typename T>
    auto read(T& data) -> decltype(data << *this)
    {
        return data << *this;
    }

    template <typename T>
    auto operator<<(const T& data) -> decltype(data >> *this)
    {
        return data >> *this;
    }

    template <typename T>
    auto operator>>(T& data) -> decltype(data << *this)
    {
        return data << *this;
    }

    //catch all with error message.
    //this would be nice if I could find a way to get the static assert to only check if someone actually calls
//    void append(...)
//    {
//        //force evaluatoin and make always false.
//        static_assert(false, "This type hasn't been impelmented by DataStream yet!");
//    }

    ByteOrder byteOrder() const;
    void setByteOrder(const ByteOrder &byteOrder);


    bool errorState() const;

    std::string error() const;

private:
    //private for now - this might be stupid
    DataStream(const DataStream& copy);

    template <typename T, std::enable_if_t<std::is_same<int16_t, T>::value || std::is_same<uint16_t, T>::value>* = nullptr>
    void swapByteOrder(T& data) const
    {
        if(systemByteOrder() == m_byteOrder)
            return;
#ifdef __GNUC__
        data = bswap_16(data);
#elif MSVC
        data = _byteswap_ushort(data);
#endif
    }

    template <typename T, std::enable_if_t<std::is_same<int32_t, T>::value || std::is_same<uint32_t, T>::value || std::is_same<float, T>::value>* = nullptr>
    void swapByteOrder(T& data) const
    {
        if(systemByteOrder() == m_byteOrder)
            return;
#ifdef __GNUC__
        data = bswap_32(data);
#elif MSVC
        data = _byteswap_ulong(data);
#endif
    }

    template <typename T, std::enable_if_t<std::is_same<int64_t, T>::value || std::is_same<uint64_t, T>::value || std::is_same<double, T>::value>* = nullptr>
    void swapByteOrder(T& data) const
    {
        if(systemByteOrder() == m_byteOrder)
            return;
#ifdef __GNUC__
        data = bswap_64(data);
#elif MSVC
        data = _byteswap_uint64(data);
#endif
    }

    void swapByteOrder(...) const
    {
        //do nothing
    }

    template <typename T>
    void writeData(const T& data)
    {
        //access data in same memory address in two different ways.
        auto dataAddress = reinterpret_cast<const unsigned char*>( (&data) );
        for(size_t i = 0; i < sizeof(T); ++i)
        {
            m_pos = m_data.insert(m_pos, (*dataAddress));
            ++dataAddress;
            ++m_pos;
        }
    }

    template <typename T>
    void readData(T& data)
    {
        auto dataAddress = reinterpret_cast<unsigned char*>( (&data) );
        for(size_t i = 0; i < sizeof(T); ++i)
        {
            assert(m_pos != m_data.end());
            if(m_pos == m_data.end())
            {
                //ERROR Overrun
                m_error = "DataStream buffer overrun.";
                m_errorState = true;
            }
           (*dataAddress) = (*m_pos);
            ++dataAddress;
            ++m_pos;
        }
    }

    std::vector<unsigned char> m_data;
    std::vector<unsigned char>::iterator m_pos;
    ByteOrder m_byteOrder;  //Default BigEndian
    bool m_doSwap;
    bool m_errorState;
    std::string m_error;
};

}

