#include <jeydia_server/agent.hpp>
#include <jeydia_server/game_module.hpp>
#include <jeydia_server/user.hpp>
#include <dirn/neighbourhood.hpp>

namespace jeydia
{

Agent::Agent(Agent_id name, User& user, Game_module& game_module, int16_t energy)
    : name_(name), user_(&user), game_module_(&game_module), energy_(energy)
{}

bool Split_action::is_executable(const Agent& agent) const
{
    return agent.is_active()
            && dir.is_valid()
            && agent.energy() >= (energy + cost);
}

bool Split_action::execute(Agent& agent) const
{
    if (is_executable(agent))
    {
        Game_module& game_module = agent.game_module();
        Map& map = game_module.map();
        User& user = agent.user();
        Position npos = dirn::neighbour(agent.position(), dir, bad_position);
        std::shared_ptr agent_sptr = user.create_agent(game_module);
        if (map.place_agent(*agent_sptr, npos))
        {
            agent.energy() -= energy + cost;
            agent_sptr->energy() = energy;
            return true;
        }
    }

    return false;
}

}
