#include <jeydia_server/agent.hpp>

namespace jeydia
{

Agent::Agent(strn::string64 name, User& user, Game_module& game_module)
    : name_(name), user_(&user), game_module_(&game_module)
{}

}
