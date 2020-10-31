#pragma once

#include "physics_body.hpp"
#include <strn/string64.hpp>
#include <unordered_set>
#include <memory>

namespace jeydia
{

using namespace strn::literals;

class Physics_square
{
public:
    bool is_bad() const;
    bool is_free() const;
    inline const Physics_body* ground_ptr() const { return ground_; }
    inline Physics_body* ground_ptr() { return ground_; }
    inline void set_ground(Physics_body& ground) { ground_ = &ground; }
    inline void remove_ground() { ground_ = nullptr; }
    inline const Physics_body* solid_body_ptr() const { return solid_body_; }
    inline Physics_body* solid_body_ptr() { return solid_body_; }
    inline const auto& traversable_bodies() const { return traversable_bodies_; }
//    inline auto& traversable_bodies() { return traversable_bodies_; }

public:
    static strn::string64 ground_from_char(char ch);
    static char ground_to_char(strn::string64 ground);

private:
    friend class Map;
    inline void set_solid_body(Physics_body& solid_body) { solid_body_ = &solid_body; }
    inline void add_traversable_body(Physics_body& traversable_body) { traversable_bodies_.insert(&traversable_body); }
    inline void remove_solid_body() { solid_body_ = nullptr; }
    inline void remove_traversable_body(Physics_body& traversable_body) { traversable_bodies_.erase(&traversable_body); }
    inline auto traversable_bodies_begin() { return traversable_bodies_.begin(); }
    inline auto traversable_bodies_end() { return traversable_bodies_.begin(); }

private:
    Physics_body* ground_ = nullptr;
    Physics_body* solid_body_ = nullptr;
    std::unordered_set<Physics_body*> traversable_bodies_;
};

}
