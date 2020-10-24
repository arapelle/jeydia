#pragma once

#include "physics_types.hpp"
#include "game_entity.hpp"

namespace jeydia
{

class Map;

class Physics_body : public Game_entity
{
public:
    using Game_entity::Game_entity;
    virtual ~Physics_body() = default;
    inline bool is_solid() const { return solid_; }
    inline bool is_pushable() const { return pushable_; }
    inline const Position& position() const { return position_; }
    inline bool is_placed() { return position_ != bad_position; }

    void set_solid(bool solid);
    inline void set_pushable(bool pushable) { pushable_ = pushable; }

private:
    friend class Map;
    inline Position& mutable_position() { return position_; }

private:
    Position position_ = bad_position;
    bool solid_ : 1 = true;
    bool pushable_ : 1 = true;
};

}
