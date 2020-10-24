#include <jeydia_server/square.hpp>

namespace jeydia
{

Square::Square(strn::string64 terrain)
    : terrain_(terrain)
{}

bool Square::is_bad() const
{
    return terrain_.empty();
}

bool Square::is_free() const
{
    return (terrain_ == PLAIN || terrain_ == VOID)
        && !solid_body_;
}

strn::string64 Square::terrain_from_char(char ch)
{
    switch (ch)
    {
    case '.':
        return VOID;
    case '_':
        return PLAIN;
    case '#':
        return BLOCK;
    default:
        ;
    }
    return BADVALUE;
}

char Square::terrain_to_char(strn::string64 terrain)
{
    switch (terrain.integer())
    {
    case VOID.integer():
        return '.';
    case PLAIN.integer():
        return '_';
    case BLOCK.integer():
        return '#';
    case BADVALUE.integer():
    default:
        ;
    }
    return '?';
}

}
