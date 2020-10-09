#pragma once

#include "application.hpp"
#include <appt/application/module/loop_module.hpp>
#include <appt/application/module/decorator/logging.hpp>

namespace jeydia
{

using module = appt::module<application>;

using logging_module = appt::mdec::logging<appt::module_logger, module>;

template <typename module_type>
using loop_module = appt::mdec::loop<logging_module, module_type>;

}
