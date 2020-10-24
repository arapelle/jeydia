#include <jeydia_server/square.hpp>

namespace jeydia
{

Square::Square(strn::string64 ground)
    : ground_(ground)
{}

bool Square::is_bad() const
{
    return ground_.empty();
}

bool Square::is_free() const
{
    return (ground_ == PLAIN || ground_ == VOID)
        && !solid_body_;
}

strn::string64 Square::ground_from_char(char ch)
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

char Square::ground_to_char(strn::string64 ground)
{
    switch (ground.integer())
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
