#include <jeydia_server/application.hpp>
#include <spdlog/spdlog.h>

namespace jeydia
{

using namespace strn::literals;

void Application::init()
{
    spdlog::set_default_logger(logger());
    vlfs::virtual_filesystem& vlfs = virtual_filesystem();
    vlfs.set_virtual_root("RSC"_s64, args().program_dir()/"rsc");

    Base_::init();
}

}
