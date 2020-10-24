#pragma once

#include "energy_entity.hpp"
#include "square.hpp"
#include "physics_events.hpp"
#include "physics_types.hpp"
#include <grid/grid.hpp>
#include <evnt/event_manager.hpp>
#include <spdlog/fmt/ostr.h>
#include <spdlog/logger.h>
#include <filesystem>
#include <unordered_set>

namespace jeydia
{

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
    bool read_ground_from_stream_(std::istream& stream);
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
    stream << "ground:\n";
    for (uint16_t j = 0; j < map.height(); ++j)
    {
        for (uint16_t i = 0; i < map.width(); ++i)
        {
            stream << Square::ground_to_char(map.get(i,j).ground());
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
