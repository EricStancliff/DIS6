#include "entityid.h"

#include <utility>

namespace DIS6
{

EntityId::EntityId() : m_site(0), m_app(0), m_entity(0)
{

}

EntityId::EntityId(const EntityId& entityId) : m_site(entityId.site()), m_app(entityId.app()), m_entity(entityId.entity())
{

}

EntityId::EntityId(EntityId&& entityId) noexcept
{
    m_site = std::move(entityId.site());
    m_app = std::move(entityId.app());
    m_entity = std::move(entityId.entity());
}

EntityId::EntityId(const uint16_t& site, const uint16_t& app, const uint16_t& entity) : m_site(site), m_app(app), m_entity(entity)
{

}

EntityId::~EntityId()
{

}

EntityId& EntityId::operator=(const EntityId& other)
{
    m_site = other.site();
    m_app = other.app();
    m_entity = other.entity();
    return (*this);
}

EntityId& EntityId::operator=(const EntityId&& other)
{
    m_site = std::move(other.site());
    m_app = std::move(other.app());
    m_entity = std::move(other.entity());
    return (*this);
}

uint16_t EntityId::site() const
{
    return m_site;
}

void EntityId::setSite(const uint16_t &site)
{
    m_site = site;
}

uint16_t EntityId::app() const
{
    return m_app;
}

void EntityId::setApp(const uint16_t &app)
{
    m_app = app;
}

uint16_t EntityId::entity() const
{
    return m_entity;
}

void EntityId::setEntity(const uint16_t &entity)
{
    m_entity = entity;
}

}
