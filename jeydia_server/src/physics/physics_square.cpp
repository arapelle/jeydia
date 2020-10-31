#include <jeydia_server/physics/physics_square.hpp>

namespace jeydia
{

bool Physics_square::is_bad() const
{
    return !ground_;
}

bool Physics_square::is_free() const
{
    return !solid_body_;
}

strn::string64 Physics_square::ground_from_char(char ch)
{
//    switch (ch)
//    {
//    case '.':
//        return VOID;
//    case '_':
//        return PLAIN;
//    case '#':
//        return BLOCK;
//    default:
//        ;
//    }
    return "";
}

char Physics_square::ground_to_char(strn::string64 ground)
{
//    switch (ground.integer())
//    {
//    case VOID.integer():
//        return '.';
//    case PLAIN.integer():
//        return '_';
//    case BLOCK.integer():
//        return '#';
//    case BADVALUE.integer():
//    default:
//        ;
//    }
    return '?';
}

}
