#include <jeydia_server/user.hpp>
#include <jeydia_server/game_module.hpp>
#include <stdexcept>

namespace jeydia
{

User::User(std::string name, Application& app)
    : name_(std::move(name)), app_(&app)
{}

std::shared_ptr<Agent> User::create_agent(Game_module& game_module)
{
    std::shared_ptr agent_sptr = std::make_shared<Agent>(game_module.generate_agent_id(), *this, game_module);
    agents_.insert(agent_sptr);
    return agent_sptr;
}

}
