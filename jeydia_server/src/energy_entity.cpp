#include <jeydia_server/energy_entity.hpp>

namespace jeydia
{

Energy_entity::Energy_entity(Application& app)
    : Physics_entity(app)
{
    physics_body().set_solid(false);
    physics_body().set_levitating(true);
}

}
