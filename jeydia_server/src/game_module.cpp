#include <jeydia_server/game_module.hpp>
#include <jeydia_server/energy_entity.hpp>
#include <inis/inis.hpp>

namespace jeydia
{

void Game_module::init()
{
    create_grounds_();
    map_.set_program_tools(logger(), event_manager());
    read_map_from_file_();
    connect_events_();
    print_level_();
}

void Game_module::run_loop(appt::seconds dt)
{
}

Agent_id Game_module::generate_agent_id() const
{
    return syllabary_.random_name64(sizeof(Agent_id));
}

void Game_module::receive(Overlap_began_event& event)
{
    Physics_entity* first_entity = event.first_body().user_data<Physics_entity>();
    Physics_entity* second_entity = event.second_body().user_data<Physics_entity>();

    Agent* agent = dynamic_cast<Agent*>(first_entity);
    Energy_entity* energy = dynamic_cast<Energy_entity*>(second_entity);
    if (agent && energy)
        agent_absorbs_energy_(event, *agent, *energy);
    else
    {
        agent = dynamic_cast<Agent*>(second_entity);
        energy = dynamic_cast<Energy_entity*>(first_entity);
        if (agent && energy)
            agent_absorbs_energy_(event, *agent, *energy);
    }
}

void Game_module::receive(Overlap_ended_event &event)
{
}

void Game_module::agent_absorbs_energy_(Overlap_began_event& event, Agent& agent, Energy_entity& energy)
{
    agent.energy() += energy.count();
    map_.remove_body(energy.physics_body());
}

void Game_module::connect_events_()
{
    event_manager().connect<Overlap_began_event>(*this);
    event_manager().connect<Overlap_ended_event>(*this);
}

void Game_module::create_grounds_()
{
    plain_ground_ = Physics_body(false, true);
}

void Game_module::read_map_from_file_()
{
    const appt::program_args& args = app().args();

    std::filesystem::path map_file;
    if (args.argc >= 4)
        map_file = app().virtual_filesystem().real_path(args[3]);

    if (std::filesystem::exists(map_file))
    {
        if (!read_map_from_file_(map_file))
        {
            map_.clear();
        }
    }

    //    SPDLOG_LOGGER_INFO(logger(), map_);
}

bool Game_module::read_map_from_file_(const std::filesystem::path& file)
{
    inis::section settings;
    settings.read_from_file(file);

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

bool Game_module::read_ground_from_stream_(std::istream& stream)
{
    std::vector<std::string> lines;
    std::string line;
    while (stream && !stream.eof() && std::getline(stream, line))
    {
        if (!lines.empty() && lines.back().length() != line.length())
        {
            SPDLOG_LOGGER_ERROR(logger(), "The map has two rows with different widths.");
            return false;
        }
        lines.push_back(std::move(line));
    }

    map_.resize(lines.back().length(), lines.size());

    for (uint16_t j = 0; j < map_.height(); ++j)
    {
        for (uint16_t i = 0; i < map_.width(); ++i)
        {
            char ch = lines[j][i];
            Physics_body* ground = nullptr;
            switch (ch)
            {
            case '.':
                break;
            case '_':
                ground = &plain_ground_;
                break;
            default:
                SPDLOG_ERROR("Ground type is unkwnon '{}'. Plain ground is used by default.", ch);
                ground = &plain_ground_;
            }
            Physics_square& square = map_.get(i,j);
            square.set_ground(*ground);
        }
    }

    return !map_.empty();
}

bool Game_module::read_main_from_stream_(std::istream& stream)
{
    std::vector<std::string> lines;
    std::string line;
    while (stream && !stream.eof() && std::getline(stream, line))
    {
        if (line.length() != map_.width())
        {
            SPDLOG_ERROR("The surface layer row doesn't have the right number of squares.");
            return false;
        }
        lines.push_back(std::move(line));
    }
    if (lines.size() != map_.height())
    {
        SPDLOG_ERROR("The surface layer does not have the right number of rows.");
        return false;
    }

    for (uint16_t j = 0; j < map_.height(); ++j)
    {
        for (uint16_t i = 0; i < map_.width(); ++i)
        {
            char ch = lines[j][i];
            Physics_square& square = map_.get(i,j);
            switch (ch)
            {
            case '$':
            {
                std::unique_ptr energy_uptr = std::make_unique<Energy_entity>(app());
                Energy_entity& energy_ref = *energy_uptr;
                map_entities_.insert(std::move(energy_uptr));
                map_.place_body(energy_ref.physics_body(), Position(i,j));
                break;
            }
            case 'o':
                break;
            case '#':
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

void Game_module::print_level_() const
{
    std::ostringstream stream;

    for (uint16_t j = 0; j < map_.height(); ++j)
    {
        stream << '\n';
        for (uint16_t i = 0; i < map_.width(); ++i)
        {
            const Physics_square& square = map_.get(i,j);
            const Physics_body* body = square.ground_ptr();
            if (!body)
                stream << '.';
            else if (body == &plain_ground_)
                stream << '_';
        }
    }

    for (uint16_t j = 0; j < map_.height(); ++j)
    {
        stream << '\n';
        for (uint16_t i = 0; i < map_.width(); ++i)
        {
            const Physics_square& square = map_.get(i,j);
            const auto& bodies = square.traversable_bodies();
            if (bodies.empty())
                stream << '.';
            else if (dynamic_cast<const Energy_entity*>((*bodies.begin())->user_data<Physics_entity>()))
                stream << '$';
            else
                stream << '?';
        }
    }

    SPDLOG_LOGGER_INFO(logger(), stream.str());
}

}
