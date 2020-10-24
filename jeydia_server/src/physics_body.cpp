#include <jeydia_server/physics_body.hpp>
#include <stdexcept>

namespace jeydia
{

void Physics_body::set_solid(bool solid)
{
    if (!is_placed()) [[likely]]
        solid_ = solid;
    else
        throw std::runtime_error("You cannot modify directly the solid field of a Physics_body once it is placed in the map.");
}

}
