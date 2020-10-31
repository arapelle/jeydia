#ifndef NDEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif
#include <jeydia_server/game_module.hpp>
#include <jeydia_server/application.hpp>

namespace jeydia
{
class Times_up_module : public Module
{
public:
    virtual ~Times_up_module() override = default;

    virtual void run() override
    {
        SPDLOG_LOGGER_INFO(app().logger(), "start!");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        app().stop_side_modules();
        SPDLOG_LOGGER_CRITICAL(app().logger(), "end!");
    }
};

class First_module : public Loop_module<First_module>
{
private:
    using base_ = Loop_module<First_module>;

public:
    First_module() : base_("first_module") {}
    virtual ~First_module() override = default;

    void run_loop(appt::seconds dt)
    {
        SPDLOG_LOGGER_INFO(logger(), dt);
    }

    virtual void finish() override
    {
        SPDLOG_LOGGER_TRACE(logger(), "finish");
    }
};

class Second_module : public Loop_module<Second_module>
{
private:
    using base_ = Loop_module<Second_module>;

public:
    Second_module() : base_("second_module") {}
    virtual ~Second_module() override = default;

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
    spdlog::set_level(spdlog::level::trace);
    jeydia::Application app(argc, argv);
    app.create_main_module<jeydia::Times_up_module>();
    app.create_module<jeydia::First_module>().set_frequency(2);
    app.create_module<jeydia::Second_module>().set_frequency(3);
    app.init();
    app.run();

    SPDLOG_LOGGER_INFO(app.logger(), "EXIT SUCCESS");
    return EXIT_SUCCESS;
}
