#include <jeydia_server/physics_events.hpp>

namespace jeydia
{

Move_event::Move_event(Map& map, Physics_body &first_body, Physics_body &second_body,
                       Position source_position, Position target_position,
                       Direction move_dir)
    : map_(&map), first_body_(&first_body), second_body_(&second_body), source_position_(source_position),
      target_position_(target_position), move_dir_(move_dir)
{}

Move_event::Move_event(Map &map, Physics_body &first_body, std::nullptr_t,
                       Position source_position, Position target_position,
                       Direction move_dir)
    : map_(&map), first_body_(&first_body), second_body_(nullptr), source_position_(source_position),
      target_position_(target_position), move_dir_(move_dir)
{}

Out_of_physics_world_event::Out_of_physics_world_event(Map& map, Physics_body& body, Position out_position)
    : map_(&map), body_(&body), out_position_(out_position)
{}

//------

}
