#include "dis6.h"

namespace DIS6
{

Interface::Interface() : m_done(false)
{
    //initialize config
    m_config.m_port = 0;
    m_config.m_exercise = 0;
}

Interface::~Interface()
{

}

void Interface::operator()()
{
    run();
}

bool Interface::connectToExercise(const IPAddress& ip, const uint16_t& port, const uint16_t& exercise)
{
    bool connected = false;
    std::shared_lock lock(m_config.m_mutex);
    m_config.m_ip = ip;
    m_config.m_port = port;
    m_config.m_exercise = exercise;

    //connect socket

    return connected;
}

void Interface::disconnectFromExercise()
{

}

void Interface::setDone(bool done)
{
    m_done = done;
}

void Interface::run()
{
    while(!m_done)
    {

    }
}

}
