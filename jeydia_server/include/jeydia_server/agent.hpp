#pragma once

#include "map_types.hpp"
#include <strn/string64.hpp>
#include <dirn/cartographic_directions4.hpp>

namespace jeydia
{

class Game_module;
class User;

using Agent_id = strn::string64;

class Agent
{
public:
    Agent(Agent_id name, User& user, Game_module& game_module, int16_t energy = 0);
    inline const Agent_id& name() const { return name_; }
    inline void set_name(Agent_id name) { name_ = name; }
    inline const User& user() const { return *user_; }
    inline User& user() { return *user_; }
    inline const Game_module& game_module() const { return *game_module_; }
    inline Game_module& game_module() { return *game_module_; }
    inline const Position& position() const { return position_; }
    inline Position& position() { return position_; }
    inline const int16_t& energy() const { return energy_; }
    inline int16_t& energy() { return energy_; }
    inline void set_energy(int16_t energy) { energy_ = energy; }
    inline bool is_active() const { return energy_ >= 0; }

private:
    Agent_id name_;
    User* user_ = nullptr;
    Game_module* game_module_ = nullptr;
    Position position_ = bad_position;
    int16_t energy_ = 0;
};

class Move_action
{
public:
    static constexpr uint16_t cost = 0;

public:
    dirn::direction4 dir = dirn::cartographic_directions4::bad_direction;

    bool is_executable(const Agent& agent) const;
    bool execute(Agent& agent) const;
};

class Split_action
{
public:
    static constexpr uint16_t cost = 2;

public:
    dirn::direction4 dir = dirn::cartographic_directions4::bad_direction;
    uint16_t energy = 0;

    bool is_executable(const Agent& agent) const;
    bool execute(Agent& agent) const;
};

}
