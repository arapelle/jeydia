#include <jeydia_server/game_entity.hpp>
#include <jeydia_server/application.hpp>

namespace jeydia
{

const Game_module& Game_entity::game_module() const
{
    return app_->game_module();
}

Game_module& Game_entity::game_module()
{
    return app_->game_module();
}

}
