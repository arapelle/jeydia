#pragma once

#include "application.hpp"
#include <appt/application/module/loop_module.hpp>
#include <appt/application/module/decorator/logging.hpp>

namespace jeydia
{

template <typename module_type>
class loop_module : public appt::mdec::logging<appt::module_logger, appt::loop_module<module_type, application>>
{
private:
    using base_ = appt::mdec::logging<appt::module_logger, appt::loop_module<module_type, application>>;

public:
    using application_type = typename base_::application_type;

public:
    using base_::base_;
    virtual ~loop_module() override = default;

    virtual void init() override
    {
        this->logger()->set_level(spdlog::level::trace);
        base_::init();
    }
};

}
