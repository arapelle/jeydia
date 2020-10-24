#pragma once

namespace jeydia
{

class Game_module;

class Game_entity
{
public:
    explicit Game_entity(Game_module& module) : game_module_(&module) {}
    virtual ~Game_entity() = default;
    inline const Game_module& game_module() const { return *game_module_; }
    inline Game_module& game_module() { return *game_module_; }

private:
    Game_module* game_module_ = nullptr;
};

}
