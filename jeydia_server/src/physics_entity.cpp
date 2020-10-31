#include <jeydia_server/physics_entity.hpp>
#include <jeydia_server/game_module.hpp>
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

//------

Physics_entity::Physics_entity(Application& app)
    : Game_entity(app)
{
    physics_body_.set_user_data(this);
}

Physics_entity::~Physics_entity()
{
    if (is_placed())
        game_module().map().remove_body(physics_body_);
}

}
