#pragma once

#include "dis6_global.h"

#include "pdu.h"
#include "entityid.h"
#include "entitytype.h"

namespace DIS6
{

//todo - imcomplete
enum ForceId : uint8_t {
    Other = 0,
    Friendly = 1,
    Opposing = 2,
    Neutral = 3
};

class DIS6_EXPORT EntityStatePdu : public Pdu
{
public:
    EntityStatePdu();
    virtual ~EntityStatePdu();

private:
    EntityId m_entityId;
    ForceId m_forceId;
    uint8_t m_numArticulationParamaters;
    EntityType m_entityType;
    EntityType m_alternativeEntityType;

};

}

