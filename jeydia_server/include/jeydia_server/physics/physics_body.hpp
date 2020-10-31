#pragma once

#include "physics_types.hpp"

namespace jeydia
{

class Physics_body
{
public:
    Physics_body(void* user_data = nullptr);
    Physics_body(bool dynamic, bool solid, void* user_data = nullptr);
    inline const Position& position() const { return position_; }
    inline bool is_static() const { return !dynamic_; }
    inline bool is_dynamic() const { return dynamic_; }
    inline bool is_solid() const { return solid_; }
    inline bool is_traversable() const { return !solid_; }
    inline bool is_levitating() const { return levitating_; }
    inline bool is_placed() const { return placed_in_world_counter > 0; }
    void set_dynamic(bool dynamic);
    void set_solid(bool solid);
    inline void set_levitating(bool levitating) { levitating_ = levitating; }

    inline uint8_t force() const { return force_; }
    inline uint8_t& force() { return force_; }
    inline uint8_t resistance() const { return resistance_; }
    inline uint8_t& resistance() { return resistance_; }

    template <class User_data_type = void>
    const User_data_type* user_data() const { return reinterpret_cast<const User_data_type*>(user_data_); }
    template <class User_data_type = void>
    User_data_type* user_data() { return reinterpret_cast<User_data_type*>(user_data_); }
    void set_user_data(void* user_data) { user_data_ = user_data; }

private:
    friend class Map;
    inline Position& mutable_position() { return position_; }
    inline void inc_placed_in_world_counter() { ++placed_in_world_counter; }
    inline void dec_placed_in_world_counter() { --placed_in_world_counter; }

private:
    Position position_ = bad_position;
    bool dynamic_ : 1 = true;
    bool solid_ : 1 = true;
    bool levitating_ : 1 = false;
    uint8_t force_ = 0;
    uint8_t resistance_ = 1;
    void* user_data_ = nullptr;
    uint32_t placed_in_world_counter = 0;
};

}
