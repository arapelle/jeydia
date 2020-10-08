#ifndef NDEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif
#include <jeydia_server/loop_module.hpp>
#include <jeydia_server/application.hpp>

namespace jeydia
{
class times_up_module : public appt::module<application>
{
public:
    virtual ~times_up_module() override = default;

    virtual void run() override
    {
        SPDLOG_LOGGER_INFO(app().logger(), "start!");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        app().stop_side_modules();
        SPDLOG_LOGGER_CRITICAL(app().logger(), "end!");
    }
};

class first_module : public loop_module<first_module>
{
private:
    using base_ = loop_module<first_module>;

public:
    first_module() : base_("first_module") {}
    virtual ~first_module() override = default;

    void run_loop(appt::seconds dt)
    {
        SPDLOG_LOGGER_INFO(logger(), dt);
    }

    virtual void finish() override
    {
        SPDLOG_LOGGER_TRACE(logger(), "finish");
    }
};

class second_module : public loop_module<second_module>
{
private:
    using base_ = loop_module<second_module>;

public:
    second_module() : base_("second_module") {}
    virtual ~second_module() override = default;

    virtual void init() override
    {
        logger()->set_level(spdlog::level::trace);
    }

    void run_loop(appt::seconds dt)
    {
        SPDLOG_LOGGER_INFO(logger(), dt);
    }

    virtual void finish() override
    {
        SPDLOG_LOGGER_TRACE(logger(), "finish");
    }
};

}

int main(int argc, char** argv)
{
    jeydia::application app(argc, argv);
    app.create_main_module<jeydia::times_up_module>();
    app.create_module<jeydia::first_module>().set_frequency(2);
    app.create_module<jeydia::second_module>().set_frequency(3);
    app.init();
    app.run();

    SPDLOG_LOGGER_INFO(app.logger(), "EXIT SUCCESS");
    return EXIT_SUCCESS;
}
