#include <jeydia_server/user.hpp>
#include <stdexcept>

namespace jeydia
{

User::User(std::string name, Application& app)
    : name_(std::move(name)), app_(&app)
{}

std::shared_ptr<Agent> User::create_agent(strn::string64 name, Game_module& game_module)
{
    std::shared_ptr agent_sptr = std::make_shared<Agent>(name, *this, game_module);
    agents_.insert(agent_sptr);
    return agent_sptr;
}

}
