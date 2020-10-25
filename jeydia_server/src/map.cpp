#include <jeydia_server/map.hpp>
#include <jeydia_server/agent.hpp>
#include <jeydia_server/energy_entity.hpp>
#include <jeydia_server/game_module.hpp>
#include <inis/inis.hpp>
#include <dirn/neighbourhood.hpp>
#include <spdlog/spdlog.h>
#include <iostream>
#include <cassert>

namespace jeydia
{

void Map::set_program_tools(std::shared_ptr<spdlog::logger> logger, evnt::event_manager& event_manager)
{
    logger_ = std::move(logger);
    event_manager_ = &event_manager;
}

bool Map::place_body(Physics_body &body, Position position)
{
    if (!are_program_tools_set())
        throw std::runtime_error("Program tools must be set.");
    if (body.position() != bad_position)
    {
        SPDLOG_LOGGER_ERROR(logger_, "The agent has already a position.");
        return false;
    }

    if (contains(position))
    {
        Physics_square& square = get(position);
        if (body.is_solid())
        {
            if (square.is_free())
            {
                square.set_solid_body(body);
                body.mutable_position() = position;
                moved_in_(body, bad_position, position, Cartographic_directions::bad_direction);
                return true;
            }
        }
        else
        {
            square.add_traversable_body(body);
            body.mutable_position() = position;
            moved_in_(body, bad_position, position, Cartographic_directions::bad_direction);
            return true;
        }
    }

    return false;
}

bool Map::move_body(Physics_body &body, Direction dir)
{
    if (!are_program_tools_set())
        throw std::runtime_error("Program tools must be set.");
    if (body.position() == bad_position)
    {
        SPDLOG_LOGGER_ERROR(logger_, "The agent is not placed on this map.");
        return false;
    }

    if (dir.is_valid())
    {
        Position pos = body.position();
        Position npos = dirn::neighbour(pos, dir, bad_position);
        if (contains(npos))
        {
            Physics_square& nsquare = get(npos);
            if (body.is_solid())
            {
                if (nsquare.is_free())
                {
                    Physics_square& square = get(pos);
                    square.remove_solid_body();
                    moved_out_(body, pos, npos, dir);
                    nsquare.set_solid_body(body);
                    moved_in_(body, pos, npos, dir);
                    return true;
                }
            }
            else
            {
                Physics_square& square = get(pos);
                nsquare.add_traversable_body(body);
                square.remove_traversable_body(body);
            }
        }
    }

    return false;
}

void Map::remove_body(Physics_body &body)
{
    Position pos = body.position();
    Physics_square& square = get(pos);
    if (body.is_solid())
    {
        assert(square.solid_body_ptr() == &body);
        square.remove_solid_body();
    }
    else
        square.remove_traversable_body(body);
    moved_out_(body, pos, bad_position, Cartographic_directions::bad_direction);
}

bool Map::read_from_file(const std::filesystem::path& filepath)
{
    inis::section settings;
    settings.read_from_file(filepath);

    const inis::section* ground = settings.subsection_ptr("map.ground");
    if (ground)
    {
        std::istringstream stream(ground->setting<std::string>("layer"));
        if (!read_ground_from_stream_(stream))
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

bool Map::read_ground_from_stream_(std::istream& stream)
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
//            char ch = lines[j][i];
//            Physics_square square(Physics_square::ground_from_char(ch));
//            if (square.is_bad())
//            {
//                SPDLOG_ERROR("Square cannot be read: unkwnon character '{}'.", ch);
//                return false;
//            }
//            get(i,j) = std::move(square);
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
            Physics_square& square = get(i,j);
            switch (ch)
            {
            case '$':
            {
//                std::unique_ptr energy_uptr = std::make_unique<Energy_entity>(*game_module_);
//                Energy_entity& energy_ref = *energy_uptr;
//                energies_.insert(std::move(energy_uptr));
//                square.add_traversable_body(energy_ref);
                break;
            }
            case 'o':
                break;
            case '.':
            case ' ':
                break;
            default:
                SPDLOG_ERROR("Square cannot be read: unkwnon character '{}'.", ch);
                return false;
            }
        }
    }

    return true;
}

void Map::moved_in_(Physics_body &moving_body, Position source_position, Position target_position, Direction move_dir)
{
    Physics_square& target_square = get(target_position);
    Moved_in_event event(*this, moving_body, nullptr, source_position, target_position, move_dir);
    if (!moving_body.is_solid() && target_square.solid_body_ptr())
    {
        event.set_second_body(*target_square.solid_body_ptr());
        event_manager_->emit<Moved_in_event>(event);
        for (auto iter = target_square.traversable_bodies_begin();
             event.is_valid() && iter != target_square.traversable_bodies_end();)
        {
            event.set_second_body(**(iter++));
            event_manager_->emit<Moved_in_event>(event);
        }
    }
    else
    {
        for (auto iter = target_square.traversable_bodies_begin();
             event.is_valid() && iter != target_square.traversable_bodies_end();)
        {
            Physics_body* second_body_ptr = *(iter++);
            if (second_body_ptr != &moving_body)
            {
                event.set_second_body(*second_body_ptr);
                event_manager_->emit<Moved_in_event>(event);
            }
        }
    }
}

void Map::moved_out_(Physics_body &moving_body, Position source_position, Position target_position, Direction move_dir)
{
    Physics_square& source_square = get(source_position);
    Moved_out_event event(*this, moving_body, nullptr, source_position, target_position, move_dir);
    if (!moving_body.is_solid() && source_square.solid_body_ptr())
    {
        event.set_second_body(*source_square.solid_body_ptr());
        event_manager_->emit<Moved_out_event>(event);
        for (auto iter = source_square.traversable_bodies_begin();
             event.is_valid() && iter != source_square.traversable_bodies_end();)
        {
            event.set_second_body(**(iter++));
            event_manager_->emit<Moved_out_event>(event);
        }
    }
    else
    {
        for (auto iter = source_square.traversable_bodies_begin();
             event.is_valid() && iter != source_square.traversable_bodies_end();)
        {
            Physics_body* second_body_ptr = *(iter++);
            if (second_body_ptr != &moving_body)
            {
                event.set_second_body(*second_body_ptr);
                event_manager_->emit<Moved_out_event>(event);
            }
        }
    }
}

}
