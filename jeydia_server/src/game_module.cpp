#include <jeydia_server/game_module.hpp>
#include <iostream>

namespace jeydia
{

void Game_module::init()
{
    std::filesystem::path map_file;

    appt::program_args args = app().args();
    if (args.argc >= 4)
        map_file = app().virtual_filesystem().real_path(args[3]);
    if (std::filesystem::exists(map_file))
        if (!map_.read_from_file(map_file))
            map_.clear();
    SPDLOG_LOGGER_INFO(logger(), map_);
}

void Game_module::run_loop(appt::seconds dt)
{
}

}
