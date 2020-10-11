#pragma once

#include "square.hpp"
#include <grid/grid.hpp>
#include <filesystem>
#include <spdlog/fmt/ostr.h>

namespace jeydia
{

class Map : public grid::grid<Square>
{
private:
    using base_ = ::grid::grid<Square>;

public:
    using base_::base_;

    bool read_from_file(const std::filesystem::path& filepath);

private:
    bool read_terrain_from_stream_(std::istream& stream);
    bool read_main_from_stream_(std::istream& stream);
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
