#include <jeydia_server/square.hpp>

namespace jeydia
{

Square::Square(strn::string64 terrain, strn::string64 main)
    : terrain_(terrain), main_(main)
{}

bool Square::is_bad() const
{
    return terrain_.empty();
}

bool Square::is_free() const
{
    return (terrain_ == PLAIN || terrain_ == VOID)
            && (main_.empty() || main_ == ENERGY);
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

strn::string64 Square::main_from_char(char ch)
{
    switch (ch)
    {
    case '$':
        return ENERGY;
    case 'o':
        return ROCK;
    case '.':
    case ' ':
        return EMPTY;
    default:
        ;
    }
    return BADVALUE;
}

char Square::main_to_char(strn::string64 main_entity)
{
    switch (main_entity.integer())
    {
    case ENERGY.integer():
        return '$';
    case ROCK.integer():
        return 'o';
    case EMPTY.integer():
        return '.';
    case BADVALUE.integer():
    default:
        ;
    }
    return '?';
}

}
