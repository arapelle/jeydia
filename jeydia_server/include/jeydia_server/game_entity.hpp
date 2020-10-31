#pragma once

namespace jeydia
{

class Application;
class Game_module;

class Game_entity
{
public:
    explicit Game_entity(Application& app) : app_(&app) {}
    virtual ~Game_entity() = default;
    inline const Application& app() const { return *app_; }
    inline Application& app() { return *app_; }
    const Game_module& game_module() const;
    Game_module& game_module();

private:
    Application* app_ = nullptr;
};

}
