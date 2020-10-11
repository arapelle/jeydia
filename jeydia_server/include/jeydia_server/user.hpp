#pragma once

#include "agent.hpp"
#include <appt/user/user.hpp>
#include <unordered_set>
#include <string>
#include <memory>

namespace jeydia
{

class Application;
class Game_module;

class User : public appt::user
{
public:
    User(std::string name, Application& app);
    inline const std::string& name() const { return name_; }
    inline void set_name(std::string name) { name_ = std::move(name); }
    inline const Application& app() const { return *app_; }
    inline Application& app() { return *app_; }
    inline const auto& agents() const { return agents_; }
    std::shared_ptr<Agent> create_agent(strn::string64 name, Game_module& game_module);

private:
    std::string name_;
    Application* app_ = nullptr;
    std::unordered_set<std::shared_ptr<Agent>> agents_;
};

}
