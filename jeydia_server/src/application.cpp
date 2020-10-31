#include <jeydia_server/application.hpp>
#include <jeydia_server/game_module.hpp>
#include <spdlog/spdlog.h>

namespace jeydia
{

using namespace strn::literals;

void Application::init()
{
    create_modules_();

    spdlog::set_default_logger(logger());
    vlfs::virtual_filesystem& vlfs = virtual_filesystem();
    vlfs.set_virtual_root("RSC"_s64, args().program_dir()/"rsc");

    Base_::init();
}

void Application::create_modules_()
{
    game_module_ = &create_module<Game_module>();
    game_module_->set_frequency(3);
}

}
