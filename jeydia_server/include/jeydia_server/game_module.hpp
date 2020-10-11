#pragma once

#include "map.hpp"
#include "module.hpp"
#include <wgen/default_syllabary.hpp>

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

    inline const Map& map() const { return map_; }
    inline Map& map() { return map_; }
    Agent_id generate_agent_id() const;

private:
    Map map_;
    wgen::default_syllabary syllabary_;
};

}
