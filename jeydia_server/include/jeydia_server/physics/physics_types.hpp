#pragma once

#include <grid/grid_types.hpp>
#include <dirn/cartographic_directions4.hpp>

namespace jeydia
{

using Position = grid::grid_position;
constexpr Position bad_position = Position(-1,-1);
using Direction = dirn::direction4;
using Cartographic_directions = dirn::cartographic_directions4;

}
