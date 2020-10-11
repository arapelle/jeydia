#include <jeydia_server/map.hpp>
#include <inis/inis.hpp>
#include <spdlog/spdlog.h>
#include <iostream>

namespace jeydia
{

bool Map::read_from_file(const std::filesystem::path& filepath)
{
    inis::section settings;
    settings.read_from_file(filepath);

    const inis::section* terrain = settings.subsection_ptr("map.terrain");
    if (terrain)
    {
        std::istringstream stream(terrain->setting<std::string>("layer"));
        if (!read_terrain_from_stream_(stream))
            return false;
    }

    const inis::section* main = settings.subsection_ptr("map.main");
    if (main)
    {
        std::istringstream stream(main->setting<std::string>("layer"));
        if (!read_main_from_stream_(stream))
            return false;
    }

    return true;
}

bool Map::read_terrain_from_stream_(std::istream& stream)
{
    std::vector<std::string> lines;
    std::string line;
    while (stream && !stream.eof() && std::getline(stream, line))
    {
        if (!lines.empty() && lines.back().length() != line.length())
        {
            SPDLOG_ERROR("The map has two rows with different widths.");
            return false;
        }
        lines.push_back(std::move(line));
    }

    resize(lines.back().length(), lines.size());

    for (uint16_t j = 0; j < height(); ++j)
    {
        for (uint16_t i = 0; i < width(); ++i)
        {
            char ch = lines[j][i];
            Square square(Square::terrain_from_char(ch));
            if (square.is_bad())
            {
                SPDLOG_ERROR("Square cannot be read: unkwnon character '{}'.", ch);
                return false;
            }
            get(i,j) = std::move(square);
        }
    }

    return !empty();
}

bool Map::read_main_from_stream_(std::istream& stream)
{
    std::vector<std::string> lines;
    std::string line;
    while (stream && !stream.eof() && std::getline(stream, line))
    {
        if (line.length() != width())
        {
            SPDLOG_ERROR("The surface layer row doesn't have the right number of squares.");
            return false;
        }
        lines.push_back(std::move(line));
    }
    if (lines.size() != height())
    {
        SPDLOG_ERROR("The surface layer does not have the right number of rows.");
        return false;
    }

    for (uint16_t j = 0; j < height(); ++j)
    {
        for (uint16_t i = 0; i < width(); ++i)
        {
            char ch = lines[j][i];
            Square& square = get(i,j);
            square.set_main(Square::main_from_char(ch));
            if (square.is_bad())
            {
                SPDLOG_ERROR("Square cannot be read: unkwnon character '{}'.", ch);
                return false;
            }
        }
    }

    return true;
}

}
