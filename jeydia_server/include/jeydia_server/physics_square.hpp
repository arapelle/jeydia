#pragma once

#include "physics_body.hpp"
#include <strn/string64.hpp>
#include <unordered_set>
#include <memory>

namespace jeydia
{

using namespace strn::literals;

class Ground : public Physics_body
{
public:
    inline strn::string64 name() const { return name_; }
    inline void set_name(strn::string64 name) { name_ = name; }
    inline bool is_void() const { return void_; }
    inline void set_void(bool void_flag) { void_ = void_flag; }

private:
    strn::string64 name_;
    bool void_ = false;
};

class Physics_square
{
public:
    bool is_bad() const;
    bool is_free() const;
    inline const Ground* ground_ptr() const { return ground_; }
    inline void set_ground(Ground& ground) { ground_ = &ground; }
    inline void remove_ground() { ground_ = nullptr; }
    inline const Physics_body* solid_body_ptr() const { return solid_body_; }
    inline Physics_body* solid_body_ptr() { return solid_body_; }
    inline const auto& traversable_bodies() const { return traversable_bodies_; }
//    inline auto& traversable_bodies() { return traversable_bodies_; }

public:
    static strn::string64 ground_from_char(char ch);
    static char ground_to_char(strn::string64 ground);

public:
    inline void set_solid_body(Physics_body& solid_body) { solid_body_ = &solid_body; }
    inline void add_traversable_body(Physics_body& traversable_body) { traversable_bodies_.insert(&traversable_body); }
    inline void remove_solid_body() { solid_body_ = nullptr; }
    inline void remove_traversable_body(Physics_body& traversable_body) { traversable_bodies_.erase(&traversable_body); }
    inline auto traversable_bodies_begin() { return traversable_bodies_.begin(); }
    inline auto traversable_bodies_end() { return traversable_bodies_.begin(); }

private:
    Ground* ground_ = nullptr;
    Physics_body* solid_body_ = nullptr;
    std::unordered_set<Physics_body*> traversable_bodies_;
};

}
