#pragma once

#include <strn/string64.hpp>

namespace jeydia
{

using namespace strn::literals;

class Square
{
public:
    inline constexpr static strn::string64 VOID = "VOID"_s64;
    inline constexpr static strn::string64 PLAIN = "PLAIN"_s64;
    inline constexpr static strn::string64 BLOCK = "BLOCK"_s64;

    inline constexpr static strn::string64 ENERGY = "ENERGY"_s64;
    inline constexpr static strn::string64 ROCK = "ROCK"_s64;
    inline constexpr static strn::string64 EMPTY = "EMPTY"_s64;

    inline constexpr static strn::string64 BADVALUE = "BADVALUE"_s64;

public:
    Square(strn::string64 terrain = PLAIN, strn::string64 main = "");
    bool is_bad() const;
    bool is_free() const;
    inline const strn::string64& terrain() const { return terrain_; }
    inline const strn::string64& main() const { return main_; }
    inline void set_terrain(strn::string64 terrain) { terrain_ = terrain; }
    inline void set_main(strn::string64 main) { main_ = main; }

public:
    static strn::string64 terrain_from_char(char ch);
    static char terrain_to_char(strn::string64 terrain);
    static strn::string64 main_from_char(char ch);
    static char main_to_char(strn::string64 main_entity);

private:
    strn::string64 terrain_;
    strn::string64 main_;
};

}
