#pragma once

#include "physics_body.hpp"
#include <strn/string64.hpp>
#include <unordered_set>
#include <memory>

namespace jeydia
{

using namespace strn::literals;

class Square
{
public:
    inline constexpr static strn::string64 VOID = "VOID"_s64;
    inline constexpr static strn::string64 PLAIN = "PLAIN"_s64;
    inline constexpr static strn::string64 BLOCK = "BLOCK"_s64;

    inline constexpr static strn::string64 BADVALUE = "BADVALUE"_s64;

public:
    Square(strn::string64 terrain = PLAIN);
    bool is_bad() const;
    bool is_free() const;
    inline const strn::string64& terrain() const { return terrain_; }
    inline void set_terrain(strn::string64 terrain) { terrain_ = terrain; }
    inline const Physics_entity* solid_body_ptr() const { return solid_body_; }
    inline Physics_entity* solid_body_ptr() { return solid_body_; }
    inline const auto& traversable_bodies() const { return traversable_bodies_; }
//    inline auto& traversable_bodies() { return traversable_bodies_; }

public:
    static strn::string64 terrain_from_char(char ch);
    static char terrain_to_char(strn::string64 terrain);

public:
    inline void set_solid_body(Physics_entity& solid_body) { solid_body_ = &solid_body; }
    inline void add_traversable_body(Physics_entity& traversable_body) { traversable_bodies_.insert(&traversable_body); }
    inline void remove_solid_body() { solid_body_ = nullptr; }
    inline void remove_traversable_body(Physics_entity& traversable_body) { traversable_bodies_.erase(&traversable_body); }
    inline auto traversable_bodies_begin() { return traversable_bodies_.begin(); }
    inline auto traversable_bodies_end() { return traversable_bodies_.begin(); }

private:
    strn::string64 terrain_;
    Physics_entity* solid_body_ = nullptr;
    std::unordered_set<Physics_entity*> traversable_bodies_;
};

}
