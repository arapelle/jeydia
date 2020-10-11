#pragma once

#include "square.hpp"
#include "map_types.hpp"
#include <grid/grid.hpp>
#include <filesystem>
#include <spdlog/fmt/ostr.h>

namespace jeydia
{

class Game_module;
class Agent;

class Map : public grid::grid<Square>
{
private:
    using Base_ = ::grid::grid<Square>;

public:
    using Base_::Base_;

    void set_game_module(Game_module& module);
    bool place_agent(Agent& agent, Position position);
    bool read_from_file(const std::filesystem::path& filepath);

private:
    bool read_terrain_from_stream_(std::istream& stream);
    bool read_main_from_stream_(std::istream& stream);

private:
    Game_module* game_module_ = nullptr;
};

template <class Output_stream>
Output_stream& operator<<(Output_stream& stream, const Map& map)
{
    stream << map.width() << 'x' << map.height() << std::endl;
    stream << "terrain:\n";
    for (uint16_t j = 0; j < map.height(); ++j)
    {
        for (uint16_t i = 0; i < map.width(); ++i)
        {
            stream << Square::terrain_to_char(map.get(i,j).terrain());
        }
        stream << '\n';
    }
    stream << "main:\n";
    for (uint16_t j = 0; j < map.height(); ++j)
    {
        for (uint16_t i = 0; i < map.width(); ++i)
        {
            stream << Square::main_to_char(map.get(i,j).main());
        }
        stream << '\n';
    }
    return stream;
}

}
