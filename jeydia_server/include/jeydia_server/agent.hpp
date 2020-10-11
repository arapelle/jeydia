#pragma once

#include <strn/string64.hpp>

namespace jeydia
{

class Game_module;
class User;

class Agent
{
public:
    Agent(strn::string64 name, User& user, Game_module& game_module);
    inline const strn::string64& name() const { return name_; }
    inline void set_name(strn::string64 name) { name_ = name; }
    inline const User& user() const { return *user_; }
    inline User& user() { return *user_; }
    inline const Game_module& game_module() const { return *game_module_; }
    inline Game_module& game_module() { return *game_module_; }

private:
    strn::string64 name_;
    User* user_ = nullptr;
    Game_module* game_module_ = nullptr;
};

}
