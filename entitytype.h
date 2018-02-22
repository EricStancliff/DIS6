#pragma once

#include <cinttypes>

namespace DIS6
{

struct EntityType {
    uint8_t kind;
    uint8_t domain;
    uint16_t country;
    uint8_t category;
    uint8_t subcategory;
    uint8_t specific;
    uint8_t extra;
};

}
