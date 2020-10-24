#pragma once

#include "energy_entity.hpp"
#include "square.hpp"
#include "physics_types.hpp"
#include <grid/grid.hpp>
#include <evnt/event_manager.hpp>
#include <spdlog/fmt/ostr.h>
#include <spdlog/logger.h>
#include <filesystem>
#include <unordered_set>

namespace jeydia
{

class Game_module;
class Agent;
class Map;

class Move_event
{
public:
    Move_event(Map& map, Physics_entity& first_body, Physics_entity& second_body,
               Position source_position, Position target_position,
               Direction move_dir);
    Move_event(Map& map, Physics_entity& first_body, std::nullptr_t,
               Position source_position, Position target_position,
               Direction move_dir);
    inline const Map& map() const { return *map_; }
    inline Map& map() { return *map_; }
    inline const Physics_entity& first_body() const { return *first_body_; }
    inline Physics_entity& first_body() { return *first_body_; }
    inline const Physics_entity& second_body() const { return *second_body_; }
    inline Physics_entity& second_body() { return *second_body_; }
    inline void set_second_body(Physics_entity& body) { second_body_ = &body; }
    inline Position source_position() { return source_position_; }
    inline Position target_position() { return target_position_; }
    inline Direction move_dir() const { return move_dir_; }
    inline bool is_valid() const { return valid_; }
    inline void invalidate() { valid_ = false; }

private:
    Map* map_ = nullptr;
    Physics_entity* first_body_;
    Physics_entity* second_body_;
    Position source_position_;
    Position target_position_;
    Direction move_dir_;
    bool valid_ = false;
};

class Moved_in_event : public Move_event
{
public:
    using Move_event::Move_event;
};

class Moved_out_event : public Move_event
{
public:
    using Move_event::Move_event;
};

class Map : public grid::grid<Square>
{
private:
    using Base_ = ::grid::grid<Square>;

public:
    using Base_::Base_;

    void set_program_tools(std::shared_ptr<spdlog::logger> logger, evnt::event_manager& event_manager);
    inline bool are_program_tools_set() const { return logger_ && event_manager_; }
    bool place_entity(Physics_entity& entity, Position position);
    bool move_entity(Physics_entity& entity, Direction dir);
    void remove_entity(Physics_entity& entity);

    bool read_from_file(const std::filesystem::path& filepath);

private:
    bool read_terrain_from_stream_(std::istream& stream);
    bool read_main_from_stream_(std::istream& stream);

private:
    void moved_in_(Physics_entity& moving_body, Position source_position, Position target_position, Direction move_dir);
    void moved_out_(Physics_entity& moving_body, Position source_position, Position target_position, Direction move_dir);

private:
    std::shared_ptr<spdlog::logger> logger_;
    evnt::event_manager* event_manager_ = nullptr;
    std::unordered_set<std::unique_ptr<Energy_entity>> energies_;
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
    stream << "physics bodies:\n";
    for (uint16_t j = 0; j < map.height(); ++j)
    {
        for (uint16_t i = 0; i < map.width(); ++i)
        {
            const Square& sq = map.get(i,j);
            if (sq.solid_body_ptr())
                stream << '@';
            else if (!sq.traversable_bodies().empty())
                stream << '~';
            else
                stream << '.';
        }
        stream << '\n';
    }
    return stream;
}

}
