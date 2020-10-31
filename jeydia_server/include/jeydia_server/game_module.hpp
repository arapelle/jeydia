#pragma once

#include "map.hpp"
#include "module.hpp"
#include <evnt/event_listener.hpp>
#include <wgen/default_syllabary.hpp>

namespace jeydia
{

class Game_module : public Loop_module<Game_module>,
                    public evnt::event_listener<Overlap_began_event, Overlap_ended_event>
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
    void receive(Overlap_began_event& event);
    void receive(Overlap_ended_event& event);

private:
    void agent_absorbs_energy_(Overlap_began_event& event, Agent& agent, Energy_entity& energy);

private:
    void read_map_from_file_();

private:
    Map map_;
    wgen::default_syllabary syllabary_;
};

}
