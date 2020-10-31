#pragma once

#include "physics_entity.hpp"

namespace jeydia
{
class Map;

class Move_event
{
public:
    Move_event(Map& map, Physics_body& first_body, Physics_body& second_body,
               Position source_position, Position target_position,
               Direction move_dir);
    Move_event(Map& map, Physics_body& first_body, std::nullptr_t,
               Position source_position, Position target_position,
               Direction move_dir);
    inline const Map& map() const { return *map_; }
    inline Map& map() { return *map_; }
    inline const Physics_body& first_body() const { return *first_body_; }
    inline Physics_body& first_body() { return *first_body_; }
    inline const Physics_body& second_body() const { return *second_body_; }
    inline Physics_body& second_body() { return *second_body_; }
    inline void set_second_body(Physics_body& body) { second_body_ = &body; }
    inline Position source_position() { return source_position_; }
    inline Position target_position() { return target_position_; }
    inline Direction move_dir() const { return move_dir_; }
    inline bool is_valid() const { return valid_; }
    inline void invalidate() { valid_ = false; }

private:
    Map* map_ = nullptr;
    Physics_body* first_body_;
    Physics_body* second_body_;
    Position source_position_;
    Position target_position_;
    Direction move_dir_;
    bool valid_ = false;
};

class Overlap_began_event : public Move_event
{
public:
    using Move_event::Move_event;
};

class Overlap_ended_event : public Move_event
{
public:
    using Move_event::Move_event;
};

}
