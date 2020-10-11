#include <jeydia_server/agent.hpp>

namespace jeydia
{

Agent::Agent(Agent_id name, User& user, Game_module& game_module, int16_t energy)
    : name_(name), user_(&user), game_module_(&game_module), energy_(energy)
{}

}
