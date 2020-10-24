#include <jeydia_server/game_module.hpp>
#include <iostream>

namespace jeydia
{

void Game_module::init()
{
    read_map_from_file_();
    map_.set_program_tools(logger(), event_manager());

    event_manager().connect<Moved_in_event>(*this);
    event_manager().connect<Moved_out_event>(*this);
}

void Game_module::run_loop(appt::seconds dt)
{
}

Agent_id Game_module::generate_agent_id() const
{
    return syllabary_.random_name64(sizeof(Agent_id));
}

void Game_module::receive(Moved_in_event& event)
{
    Agent* agent = dynamic_cast<Agent*>(&event.first_body());
    Energy_entity* energy = dynamic_cast<Energy_entity*>(&event.second_body());
    if (agent && energy)
        agent_absorbs_energy_(event, *agent, *energy);
    else
    {
        agent = dynamic_cast<Agent*>(&event.second_body());
        energy = dynamic_cast<Energy_entity*>(&event.first_body());
        if (agent && energy)
            agent_absorbs_energy_(event, *agent, *energy);
    }
}

void Game_module::receive(Moved_out_event& event)
{
}

void Game_module::agent_absorbs_energy_(Moved_in_event& event, Agent& agent, Energy_entity& energy)
{
    agent.energy() += energy.count();
    map_.remove_entity(energy);
}

void Game_module::read_map_from_file_()
{
    const appt::program_args& args = app().args();

    std::filesystem::path map_file;
    if (args.argc >= 4)
        map_file = app().virtual_filesystem().real_path(args[3]);

    if (std::filesystem::exists(map_file))
        if (!map_.read_from_file(map_file))
            map_.clear();

    SPDLOG_LOGGER_INFO(logger(), map_);
}

}
