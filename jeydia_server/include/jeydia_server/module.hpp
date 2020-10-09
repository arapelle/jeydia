#pragma once

#include "application.hpp"
#include <appt/application/module/loop_module.hpp>
#include <appt/application/module/decorator/logging.hpp>

namespace jeydia
{

using Module = appt::module<Application>;

using Logging_module = appt::mdec::logging<appt::module_logger, Module>;

template <typename module_type>
using Loop_module = appt::mdec::loop<Logging_module, module_type>;

}
