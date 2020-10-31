#include <jeydia_server/physics/physics_body.hpp>

namespace jeydia
{

Physics_body::Physics_body(void *user_data)
    : user_data_(user_data)
{}

Physics_body::Physics_body(bool dynamic, bool solid, void* user_data)
    : dynamic_(dynamic), solid_(solid), user_data_(user_data)
{}

}
