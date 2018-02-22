#pragma once

#include <sstream>
#include <climits>
#include <vector>
#include <assert.h>

namespace DIS6
{

enum Endian {
    BigEndian,
    LitleEndian
};

//makes a copy of the data you give it and stores it in a string buffer
class DataStream
{
public:
    DataStream();
    ~DataStream();

    size_t size() const;
    std::vector<unsigned char> data() const;

    template <typename T>
    void append(const T& data)
    {
        auto copyData = data;
        swapEndian(copyData);
        writeData(copyData);
    }

    template <typename T>
    void read(T& data)
    {
        readData(data);
        swapEndian(data);
    }

    template <typename T>
    T read()
    {
        T data;
        readData(data);
        swapEndian(data);
        return data;
    }

    template <typename T>
    void operator<<(const T& data)
    {
        auto copyData = data;
        swapEndian(copyData);
        writeData(copyData);
    }

    template <typename T>
    void operator>>(T& data)
    {
        readData(data);
        swapEndian(data);
    }


    Endian endian() const;
    void setEndian(const Endian &endian);


    bool errorState() const;

    std::string error() const;

private:
    //private for now - this might be stupid
    DataStream(const DataStream& copy);

    template <typename T>
    void swapEndian(T& data) const
    {
        //right now just for signed/unsigned char/short/int/long types.  I think this will work as is for doubles/floats as well.
        //it would be faster to call the system calls based on my compiler, but that gets less generic.
        static_assert(sizeof(T) == 1 || sizeof(T) == 2|| sizeof(T) == 4 || sizeof(T) == 8, "This method is intended for primitives");

        //Assume that if we're working in LittleEndian, data is already in correct byte order.  This could be wrong.
        if(m_endian == LitleEndian)
            return;

        if(sizeof(T) < 2)
            return;

        //access data in same memory in two different ways.
        union {
            T data;
            unsigned char bytes[sizeof(T)];
        } inData, outData;

        inData.data = data;

        for(size_t i = 0; i < sizeof(T); ++i)
        {
            outData.bytes[i] = inData.bytes[(sizeof(T) - 1) - i];
        }
        data = outData.data;
    }

    template <typename T>
    void writeData(const T& data)
    {
        //access data in same memory in two different ways.
        union {
            T data;
            unsigned char bytes[sizeof(T)];
        } dataUnion;
        dataUnion.data = data;

        for(auto oneByte : dataUnion.bytes)
        {
            m_data.push_back(oneByte);
        }
    }

    //Some people don't like "type punning" with unions
    //This is a possible implementation using raw pointers instead.
//    template <typename T>
//    void writeData(const T& data)
//    {
//        //access data in same memory address in two different ways.
//        auto dataAddress = reinterpret_cast<unsigned char*>(data);
//        for(size_t i = 0; i < sizeof(T); ++i)
//        {
//            m_data.push_back((*dataAddress));
//            ++dataAddress;
//        }
//    }

    template <typename T>
    void readData(T& data)
    {
        //access data in same memory in two different ways.
        union {
            T data;
            unsigned char bytes[sizeof(T)];
        } dataUnion;
        dataUnion.data = data;

        auto itr = m_data.begin();
        for(size_t i = 0; i < sizeof(T); ++i)
        {
            assert(itr != m_data.end());
            if(itr == m_data.end())
            {
                //ERROR Overrun
                m_error = "DataStream buffer overrun.";
                m_errorState = true;
            }
            dataUnion.bytes[i] = (*itr);
            itr = m_data.erase(itr);
        }
        data = dataUnion.data;
    }

    //Some people don't like "type punning" with unions
    //This is a possible implementation using raw pointers instead.
//    template <typename T>
//    void readData(T& data)
//    {
//        auto dataAddress = reinterpret_cast<unsigned char*>(data);

//        auto itr = m_data.begin();
//        for(size_t i = 0; i < sizeof(T); ++i)
//        {
//            assert(itr != m_data.end());
//            if(itr == m_data.end())
//            {
//                //ERROR Overrun
//                m_error = "DataStream buffer overrun.";
//                m_errorState = true;
//            }
//           (*dataAddress) = (*itr);
//            ++dataAddress;
//            itr = m_data.erase(itr);
//        }
//    }

    std::vector<unsigned char> m_data;
    Endian m_endian;  //Default BigEndian
    bool m_errorState;
    std::string m_error;
};

}

