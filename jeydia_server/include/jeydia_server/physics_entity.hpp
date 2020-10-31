#pragma once

#include "game_entity.hpp"
#include "physics_body.hpp"

namespace jeydia
{

class Physics_entity : public Game_entity
{
public:
    explicit Physics_entity(Application& app);
    virtual ~Physics_entity();
    inline const Physics_body& physics_body() const { return physics_body_; }
    inline Physics_body& physics_body() { return physics_body_; }
    inline const Position& position() const { return physics_body_.position(); }
    inline bool is_placed() const { return physics_body_.is_placed(); }

private:
    Physics_body physics_body_;
};

}
