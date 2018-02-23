#pragma once

#include <cinttypes>

#include "dis6_global.h"
#include "datastream.h"

namespace DIS6
{

class DIS6_EXPORT EntityId
{
public:
    EntityId();
    EntityId(const EntityId& entityId);
    EntityId(EntityId&& entityId) noexcept;
    EntityId(const uint16_t& site, const uint16_t& app, const uint16_t& entity);
    ~EntityId();

    EntityId& operator=(const EntityId& other);
    EntityId& operator=(const EntityId&& other);

    inline bool operator< (const EntityId& rhs) const
    {
        //check site, then app, then entity
        if(m_site < rhs.site())
            return true;
        if(m_app < rhs.app())
            return true;
        if(m_entity < rhs.entity())
            return true;
        return false;
    }
    inline bool operator> (const EntityId& rhs) const
    {
        return (rhs < *this);
    }
    inline bool operator<=(const EntityId& rhs) const
    {
        return !(*this > rhs);
    }
    inline bool operator>=(const EntityId& rhs) const
    {
        return !(*this < rhs);
    }
    inline bool operator==(const EntityId& rhs) const
    {
        return m_site == rhs.site() && m_app == rhs.app() && m_entity == rhs.entity();
    }
    inline bool operator!=(const EntityId& rhs) const
    {
        return !(*this == rhs);
    }


    uint16_t site() const;
    void setSite(const uint16_t &site);

    uint16_t app() const;
    void setApp(const uint16_t &app);

    uint16_t entity() const;
    void setEntity(const uint16_t &entity);

protected:

    uint16_t m_site;
    uint16_t m_app;
    uint16_t m_entity;
};


DIS6_EXPORT bool operator<<(EntityId& lhs, DataStream& rhs);
DIS6_EXPORT bool operator>>(const EntityId& lhs, DataStream& rhs);

}
