#pragma once

#include "user.hpp"
#include <appt/application/multi_task_application.hpp>
#include <appt/application/decorator/multi_user.hpp>
#include <appt/user/user.hpp>
#include <appt/application/decorator/logging.hpp>

namespace jeydia
{

class application : public appt::adec::logging<appt::application_logger,
                                               appt::adec::multi_user<user,
                                                                      appt::multi_task_application<application>>>
{
private:
    using base_ = appt::adec::logging<appt::application_logger,
                                      appt::adec::multi_user<user,
                                                             appt::multi_task_application<application>>>;
public:
    using base_::base_;

    void init()
    {
        logger()->set_level(spdlog::level::trace);
        base_::init();
    }
};

}
