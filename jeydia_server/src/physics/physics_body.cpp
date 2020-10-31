#include <jeydia_server/physics/physics_body.hpp>

namespace jeydia
{

Physics_body::Physics_body(void *user_data)
    : user_data_(user_data)
{}

Physics_body::Physics_body(bool dynamic, bool solid, void* user_data)
    : dynamic_(dynamic), solid_(solid), user_data_(user_data)
{}

void Physics_body::set_dynamic(bool dynamic)
{
    if (!is_placed()) [[likely]]
        dynamic_ = dynamic;
    else
        throw std::runtime_error("You cannot modify directly the dynamic field of a Physics_body once it is placed in the map.");
}

void Physics_body::set_solid(bool solid)
{
    if (!is_placed()) [[likely]]
        solid_ = solid;
    else
        throw std::runtime_error("You cannot modify directly the solid field of a Physics_body once it is placed in the map.");
}

}
