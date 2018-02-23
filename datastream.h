#pragma once

#include <sstream>
#include <climits>
#include <vector>
#include <assert.h>
#include <type_traits>

#ifdef __GNUC__
#include <byteswap.h>
#endif

#ifdef MSVC
#include <stdlib.h>
#endif

namespace DIS6
{

enum ByteOrder {
    BigEndian,
    LittleEndian
};

constexpr ByteOrder systemByteOrder()
{
    //todo
    return LittleEndian;
}

//makes a copy of the data you give it and stores it in a string buffer
class DataStream
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

    template <typename T>
    void append(const T& data)
    {
        auto copyData = data;
        swapByteOrder(copyData);
        writeData(copyData);
    }

    template <typename T>
    void read(T& data)
    {
        readData(data);
        swapByteOrder(data);
    }

    template <typename T>
    T read()
    {
        T data;
        readData(data);
        swapByteOrder(data);
        return data;
    }

    template <typename T>
    void operator<<(const T& data)
    {
        auto copyData = data;
        swapByteOrder(copyData);
        writeData(copyData);
    }

    template <typename T>
    void operator>>(T& data)
    {
        readData(data);
        swapByteOrder(data);
    }


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

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif
    template <typename T, std::enable_if_t<std::is_same<int8_t, T>::value || std::is_same<uint8_t, T>::value || std::is_same<bool, T>::value>* = nullptr>
    void swapByteOrder(T& data) const
    {
        //do nothing
    }
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif
    //default for other classes
    template <typename T, std::enable_if_t<!std::is_arithmetic<T>::value>* = nullptr>
    void swapByteOrder(T& data) const
    {
        //for now
        static_assert(!std::is_arithmetic<T>::value, "DataStream doesn't handle that type yet!  Try a primative type.");
    }
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

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

