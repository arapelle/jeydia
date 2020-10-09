#pragma once

#include "user.hpp"
#include <appt/application/multi_task_application.hpp>
#include <appt/application/decorator/multi_user.hpp>
#include <appt/user/user.hpp>
#include <appt/application/decorator/logging.hpp>

namespace jeydia
{
class application_base
{
private:
    application_base() = delete;
    using logging_application_ = appt::adec::logging<appt::application_logger, appt::application>;
    using multi_user_application_ = appt::adec::multi_user<user, logging_application_>;
    using multi_task_application_ = appt::adec::multi_task<multi_user_application_>;

public:
    template <class app_type>
    using type = typename multi_task_application_::rebind_t<app_type>;
};

class application : public application_base::type<application>
{
private:
    using base_ = application_base::type<application>;

public:
    using base_::base_;
};

}
