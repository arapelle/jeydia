#pragma once

#include "physics_body.hpp"
#include <cstdint>

namespace jeydia
{

class Energy_entity : public Physics_body
{
public:
    using Physics_body::Physics_body;
    inline uint8_t count() const { return count_; }
    inline void add_count(uint8_t count) { count_ = count; }

private:
    uint8_t count_ = 1;
};

}
