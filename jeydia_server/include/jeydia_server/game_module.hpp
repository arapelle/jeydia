#pragma once

#include "map.hpp"
#include "module.hpp"
#include <evnt/event_listener.hpp>
#include <wgen/default_syllabary.hpp>

namespace jeydia
{

class Game_module : public Loop_module<Game_module>,
                    public evnt::event_listener<Moved_in_event, Moved_out_event>
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

public:
    void receive(Moved_in_event& event);
    void receive(Moved_out_event& event);

private:
    void agent_absorbs_energy_(Moved_in_event& event, Agent& agent, Energy_entity& energy);

private:
    void read_map_from_file_();

private:
    Map map_;
    wgen::default_syllabary syllabary_;
};

}
