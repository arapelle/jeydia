#pragma once

#include "physics_entity.hpp"
#include <cstdint>

namespace jeydia
{

class Energy_entity : public Physics_entity
{
public:
    using Physics_entity::Physics_entity;
    inline uint8_t count() const { return count_; }
    inline void add_count(uint8_t count) { count_ = count; }

private:
    uint8_t count_ = 1;
};

}
