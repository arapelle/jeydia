#pragma once

#include "physics_types.hpp"

namespace jeydia
{

class Physics_body
{
public:
    inline bool is_solid() const { return solid_; }
    inline bool is_pushable() const { return pushable_; }
    inline const Position& position() const { return position_; }
    inline bool is_placed() const { return position_ != bad_position; }

    void set_solid(bool solid);
    inline void set_pushable(bool pushable) { pushable_ = pushable; }

    template <class User_data_type = void>
    const User_data_type* user_data() const { return reinterpret_cast<const User_data_type*>(user_data_); }
    template <class User_data_type = void>
    User_data_type* user_data() { return reinterpret_cast<User_data_type*>(user_data_); }
    void set_user_data(void* user_data) { user_data_ = user_data; }

private:
    friend class Map;
    inline Position& mutable_position() { return position_; }

private:
    Position position_ = bad_position;
    bool solid_ : 1 = true;
    bool pushable_ : 1 = true;
    void* user_data_ = nullptr;
};

}
