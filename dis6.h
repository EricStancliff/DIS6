#pragma once

#include <cstdint>
#include <shared_mutex>

#include "dis6_global.h"

namespace DIS6
{

//simple class to represent an IP address
class DIS6_EXPORT IPAddress
{
public:
    IPAddress(): octet1(0), octet2(0), octet3(0), octet4(0) {}
    virtual ~IPAddress(){}
    IPAddress(const IPAddress& rhs) : octet1(rhs.octet1), octet2(rhs.octet2), octet3(rhs.octet3), octet4(rhs.octet4) {}

protected:
    uint8_t octet1;
    uint8_t octet2;
    uint8_t octet3;
    uint8_t octet4;
};

//Designed to be run in a new thread
class Interface
{
public:
    Interface();
    virtual ~Interface();

    void operator()();
    void setDone(bool done);

    bool connectToExercise(const IPAddress& ip, const uint16_t& port, const uint16_t& exercise);
    void disconnectFromExercise();

protected:
    void run();

    //we don't bother protecting m_done because it's impossible to tear a bool
    bool m_done;

    struct config_s {
        uint16_t m_port;
        uint16_t m_exercise;
        IPAddress m_ip;
        mutable std::shared_mutex m_mutex;
    };
    config_s m_config;

    mutable std::shared_mutex m_eventMutex;
};

}



