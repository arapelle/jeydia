#pragma once

#include "map.hpp"
#include "module.hpp"

namespace jeydia
{

class Game_module : public Loop_module<Game_module>
{
private:
    using Base_ = Loop_module<Game_module>;

public:
    using Base_::Base_;
    virtual ~Game_module() override = default;

    virtual void init() override;
    void run_loop(appt::seconds dt);

private:
    Map map_;
};

}
